package main

import (
	"bufio"
	"bytes"
	"database/sql"
	"encoding/base64"
	"encoding/json"
	"fmt"
	"image/jpeg"
	"image/png"
	"io"
	"log"
	"mime/multipart"
	"net/http"
	"os"
	"strings"
	"time"

	"github.com/google/uuid"
	_ "github.com/google/uuid"
	_ "github.com/lib/pq"
)

var connStr = "host=localhost port=5432 user=postgres dbname=smartnotes sslmode=disable"

func checkRequestDetails(r *http.Request) string {
	// Create return string
	var request []string
	// Add the request string
	url := fmt.Sprintf("%v %v %v", r.Method, r.URL, r.Proto)
	request = append(request, url)
	// Add the host
	request = append(request, fmt.Sprintf("Host: %v", r.Host))
	// Loop through headers
	for name, headers := range r.Header {
		name = strings.ToLower(name)
		for _, h := range headers {
			request = append(request, fmt.Sprintf("%v: %v", name, h))
		}
	}

	// If this is a POST, add post data
	if r.Method == "POST" {
		r.ParseForm()
		request = append(request, "\n")
		request = append(request, r.Form.Encode())
	}
	// Return the request as a string
	return strings.Join(request, "\n")
}

func signIn(w http.ResponseWriter, r *http.Request) {

	result := r.URL.String()

	usernameIndex := strings.Index(result, "username")
	passwordIndex := strings.Index(result, "password")
	username := result[usernameIndex+len("username")+1 : passwordIndex-1]
	password := result[passwordIndex+len("password")+1:]

	db, error := sql.Open("postgres", connStr)
	if error != nil {
		panic(error)
	}
	defer db.Close()

	sqlStatement := "SELECT user_id FROM account WHERE username = $1 AND password = CRYPT($2,password);"
	rows, err := db.Query(sqlStatement, username, password)
	if err != nil {
		panic(err)
	}
	defer rows.Close()

	var user_id uuid.UUID
	for rows.Next() {
		switch err := rows.Scan(&user_id); err {
		case sql.ErrNoRows:
			fmt.Fprintf(w, "No Rows")
		case nil:
			sqlStatement = "Update account Set last_sign_in = $4 Where user_id = $1 and username = $2 and password = CRYPT($3,password);"
			_, err = db.Exec(sqlStatement, user_id, username, password, time.Now())
			if err != nil {
				panic(err)
			}
			fmt.Fprintf(w, "Welcome, "+user_id.String())
			return
		default:
			panic(err)
		}
	}

	fmt.Fprintf(w, "Invalid Input")
	return

}

func registration(w http.ResponseWriter, r *http.Request) {

	result := r.URL.String()

	usernameIndex := strings.Index(result, "username")
	passwordIndex := strings.Index(result, "password")
	emailIndex := strings.Index(result, "email")
	username := result[usernameIndex+len("username")+1 : passwordIndex-1]
	password := result[passwordIndex+len("password")+1 : emailIndex-1]
	email := result[emailIndex+len("email")+1:]

	if len(username) < 5 {
		fmt.Fprintf(w, "Too short username")
		return
	}
	if len(password) < 5 {
		fmt.Fprintf(w, "Too short password")
		return
	}
	if len(email) < 6 {
		fmt.Fprintf(w, "Too short email")
		return
	}

	db, error := sql.Open("postgres", connStr)
	if error != nil {
		panic(error)
	}
	defer db.Close()

	sqlStatement := "Select * from account where username = $1;"
	rows, err := db.Query(sqlStatement, username)
	if err != nil {
		panic(err)
	}

	var check_username string
	for rows.Next() {
		err := rows.Scan(&check_username)
		if err != nil {
			fmt.Fprintf(w, "This username already exists ")
			return
		}
	}

	sqlStatement = "Select * from account where email = $1;"
	rows, err = db.Query(sqlStatement, email)
	if err != nil {
		panic(err)
	}

	var check_email string
	for rows.Next() {
		err := rows.Scan(&check_email)
		if err != nil {
			fmt.Fprintf(w, "This email already exists")
			return
		}
	}
	defer rows.Close()

	user_id := uuid.New()

	sqlStatement = "INSERT INTO user_data (user_id) VALUES ($1);"
	_, err = db.Exec(sqlStatement, user_id)
	if err != nil {
		panic(err)
	}

	account_id := uuid.New()

	sqlStatement = "INSERT INTO account (username,password,email,created_on,user_id,account_id) SELECT CAST($1 AS VARCHAR),CRYPT($2,GEN_SALT('md5')),CAST($3 AS VARCHAR),$4,$5,$6 WHERE NOT EXISTS (SELECT * FROM account WHERE username = $1 or email = $3);"
	_, err = db.Exec(sqlStatement, username, password, email, time.Now(), user_id, account_id)
	if err != nil {
		panic(err)
	}

	fmt.Fprintf(w, "Registration completed")

}

func upload(w http.ResponseWriter, r *http.Request, folder string, sql_folder string) {

	var (
		status int
		err    error
	)
	defer func() {
		if nil != err {
			log.Println(err.Error(), status)
		}
	}()

	if err = r.ParseMultipartForm(240 << 20); nil != err {
		status = http.StatusInternalServerError
		return
	}
	// No memory problem

	for _, fheaders := range r.MultipartForm.File {
		for _, hdr := range fheaders {
			// open uploaded
			var infile multipart.File
			if infile, err = hdr.Open(); nil != err {
				status = http.StatusInternalServerError
				return
			}
			// open destination
			var outfile *os.File
			if outfile, err = os.Create("./" + folder + "/" + hdr.Filename); nil != err {
				status = http.StatusInternalServerError
				return
			}
			// 32K buffer copy
			if _, err = io.Copy(outfile, infile); nil != err {
				status = http.StatusInternalServerError
				return
			}
			//log.Println([]byte("uploaded file:" + hdr.Filename + ";length:" + strconv.Itoa(int(written))))

			type Vidos struct {
				Link string `json:"link"`
			}
			js, err := json.Marshal(Vidos{Link: ("http://localhost:8080/" + folder + "/" + hdr.Filename)})
			if err != nil {
				http.Error(w, err.Error(), http.StatusInternalServerError)
				return
			}

			db, error := sql.Open("postgres", connStr)
			if error != nil {
				panic(error)
			}
			defer db.Close()

			sqlStatement := "INSERT INTO " + sql_folder + " (url,name,size,inserted_on," + sql_folder + "_id) SELECT CAST($1 AS VARCHAR),CAST($2 AS VARCHAR),$3,$4,$5 WHERE NOT EXISTS (SELECT * FROM " + sql_folder + " WHERE name = $2);"
			_, err = db.Exec(sqlStatement, "http://localhost:8080/"+folder+"/"+hdr.Filename, hdr.Filename, hdr.Size, time.Now(), uuid.New())
			if err != nil {
				panic(err)
			}

			w.Header().Set("Content-Type", "application/json")
			w.Write(js)
		}
	}

}

func uploadText(w http.ResponseWriter, r *http.Request) {

}

func uploadImage(w http.ResponseWriter, r *http.Request) {
	upload(w, r, "User_Image", "image")
}

func uploadVideo(w http.ResponseWriter, r *http.Request) {
	upload(w, r, "User_Video", "video")
}

func uploadFile(w http.ResponseWriter, r *http.Request) {
	upload(w, r, "User_File", "file")
}

func newNote(w http.ResponseWriter, r *http.Request) {

	result := r.URL.String()

	user_idIndex := strings.Index(result, "user_id")
	user_id := result[user_idIndex+len("user_id")+1:]

	db, error := sql.Open("postgres", connStr)
	if error != nil {
		panic(error)
	}
	defer db.Close()

	note_id := uuid.New()

	sqlStatement := "INSERT INTO note (note_id,created_on) VALUES ($1,$2);"
	_, err := db.Exec(sqlStatement, note_id, time.Now())
	if err != nil {
		panic(err)
	}

	user := uuid.MustParse(user_id)

	sqlStatement = "INSERT INTO user_and_note (user_id, note_id, status) VALUES ($1, $2, 'owner');"
	_, err = db.Exec(sqlStatement, user, note_id)
	if err != nil {
		panic(err)
	}

	fmt.Fprintf(w, (note_id).String())

}

type current_note struct {
	Html     string `json:"html"`
	Name     string `json:"name"`
	Category string `json:"category"`
	Note_id  string `json:"note_id"`
}

func sendCurrentNote(w http.ResponseWriter, r *http.Request) {

	decoder := json.NewDecoder(r.Body)
	var note current_note
	err := decoder.Decode(&note)
	if err != nil {
		panic(err)
	}

	note_id := uuid.MustParse(note.Note_id)

	db, error := sql.Open("postgres", connStr)
	if error != nil {
		panic(error)
	}
	defer db.Close()

	sqlStatement := "UPDATE note SET content = $1, name = $2, category = $3, lastupdated = $4 WHERE note_id = $5;"
	_, err = db.Exec(sqlStatement, note.Html, note.Name, note.Category, time.Now(), note_id)
	if err != nil {
		panic(err)
	}

	var tmp_html string
	tmp_html = note.Html

	for imageIndex := strings.Index(tmp_html, "http://localhost:8080/User_Image/"); imageIndex != -1; imageIndex = strings.Index(tmp_html, "http://localhost:8080/User_Image/") {
		var image string
		for tmp_html[imageIndex] != '"' {
			image += string(tmp_html[imageIndex])
			imageIndex++
		}
		tmp_html = tmp_html[imageIndex:]

		sqlStatement := "INSERT INTO note_and_image (note_id, image_id) SELECT $1, (SELECT image_id FROM image WHERE url = $2) WHERE NOT EXISTS (SELECT * FROM note_and_image WHERE note_id = $1 AND image_id = (SELECT image_id FROM image WHERE url = $2));"
		_, err = db.Exec(sqlStatement, note_id, string(image))
		if err != nil {
			panic(err)
		}
	}

	tmp_html = note.Html

	for videoIndex := strings.Index(tmp_html, "http://localhost:8080/User_Video/"); videoIndex != -1; videoIndex = strings.Index(tmp_html, "http://localhost:8080/User_Video/") {
		var video string
		for tmp_html[videoIndex] != '"' {
			video += string(tmp_html[videoIndex])
			videoIndex++
		}
		tmp_html = tmp_html[videoIndex:]

		sqlStatement := "INSERT INTO note_and_video (note_id, video_id) SELECT $1, (SELECT video_id FROM video WHERE url = $2) WHERE NOT EXISTS (SELECT * FROM note_and_video WHERE note_id = $1 AND video_id = (SELECT video_id FROM video WHERE url = $2));"
		_, err = db.Exec(sqlStatement, note_id, string(video))
		if err != nil {
			panic(err)
		}
	}

	tmp_html = note.Html

	for fileIndex := strings.Index(tmp_html, "http://localhost:8080/User_File/"); fileIndex != -1; fileIndex = strings.Index(tmp_html, "http://localhost:8080/User_File/") {
		var file string
		for tmp_html[fileIndex] != '"' {
			file += string(tmp_html[fileIndex])
			fileIndex++
		}
		tmp_html = tmp_html[fileIndex:]

		sqlStatement := "INSERT INTO note_and_file (note_id, file_id) SELECT $1, (SELECT file_id FROM file WHERE url = $2) WHERE NOT EXISTS (SELECT * FROM note_and_file WHERE note_id = $1 AND file_id = (SELECT file_id FROM file WHERE url = $2));"
		_, err = db.Exec(sqlStatement, note_id, string(file))
		if err != nil {
			panic(err)
		}
	}

}

type all_notes_for_user struct {
	User_id string `json:"user_id"`
}

type all_notes struct {
	Note_id        uuid.UUID `json:"note_id" sql:",type:uuid"`
	Name           string    `json:"name"`
	Category       string    `json:"category"`
	Category_color string    `json:"category_color"`
	Text_color     string    `json:"text_color"`
}

type notes []all_notes

func getUserNotes(w http.ResponseWriter, r *http.Request) {

	decoder := json.NewDecoder(r.Body)
	var user all_notes_for_user
	err := decoder.Decode(&user)
	if err != nil {
		panic(err)
	}

	user_id := uuid.MustParse(user.User_id)

	//user_id, err := strconv.ParseInt(user.User_id, 10, 64)

	db, error := sql.Open("postgres", connStr)
	if error != nil {
		panic(error)
	}
	defer db.Close()

	sqlStatement := "SELECT note.note_id, note.name, note.category FROM user_and_note INNER JOIN note ON user_and_note.note_id = note.note_id WHERE user_and_note.user_id = $1;"
	rows, err := db.Query(sqlStatement, user_id)
	if err != nil {
		panic(err)
	}

	var got = notes{}

	for rows.Next() {
		var tmp_r all_notes
		err = rows.Scan(&tmp_r.Note_id, &tmp_r.Name, &tmp_r.Category)
		if err != nil {
			panic(err)
		}
		if tmp_r.Category != "Нет категории" {
			sqlStatement = "SELECT category_color, text_color FROM category WHERE user_id = $1 and category = $2;"
			sub_rows, err := db.Query(sqlStatement, user_id, tmp_r.Category)
			if err != nil {
				panic(err)
			}
			for sub_rows.Next() {
				err = sub_rows.Scan(&tmp_r.Category_color, &tmp_r.Text_color)
				if err != nil {
					panic(err)
				}
			}
		} else {
			tmp_r.Category_color = "white"
			tmp_r.Text_color = "black"
		}
		got = append(got, tmp_r)
	}

	final_all_notes, err := json.Marshal(got)
	if err != nil {
		log.Fatal("Cannot encode to JSON ", err)
	}

	w.Header().Set("Content-Type", "application/json")
	w.Write(final_all_notes)

}

type current_note_for_user struct {
	Note_id string `json:"note_id"`
}

type get_current_note struct {
	Name     string `json:"name"`
	Category string `json:"category"`
	Content  string `json:"content"`
	Image    string `json:"image"`
}

type c_note []get_current_note

func getCurrentNote(w http.ResponseWriter, r *http.Request) {

	decoder := json.NewDecoder(r.Body)
	var note current_note_for_user
	err := decoder.Decode(&note)
	if err != nil {
		panic(err)
	}

	note_id := uuid.MustParse(note.Note_id)

	db, error := sql.Open("postgres", connStr)
	if error != nil {
		panic(error)
	}
	defer db.Close()

	var user_id uuid.UUID

	sqlStatement := "SELECT user_id FROM user_and_note INNER JOIN note ON user_and_note.note_id = note.note_id WHERE status = 'owner' AND note.note_id = $1;"
	rows, err := db.Query(sqlStatement, note_id)
	if err != nil {
		panic(err)
	}

	for rows.Next() {
		err = rows.Scan(&user_id)
		if err != nil {
			panic(err)
		}
	}

	sqlStatement = "SELECT name, category, content FROM note WHERE note_id = $1;"
	rows, err = db.Query(sqlStatement, note_id)
	if err != nil {
		panic(err)
	}

	var got = c_note{}

	for rows.Next() {
		var tmp_r get_current_note
		err = rows.Scan(&tmp_r.Name, &tmp_r.Category, &tmp_r.Content)
		if err != nil {
			panic(err)
		}

		tmp_r.Image = ""

		sqlStatement := "SELECT url FROM image INNER JOIN category ON image.image_id = category.backgroundimage_id WHERE user_id = $1 and category = $2;"
		sub_rows, err := db.Query(sqlStatement, user_id, tmp_r.Category)
		if err != nil {
			panic(err)
		}

		for sub_rows.Next() {

			var url string
			err = sub_rows.Scan(&url)
			if err != nil {
				panic(err)
			}

			imgFile, err := os.Open(url)
			if err != nil {
				panic(err)
			}
			defer imgFile.Close()

			fInfo, _ := imgFile.Stat()
			var size int64 = fInfo.Size()
			buf := make([]byte, size)

			fReader := bufio.NewReader(imgFile)
			fReader.Read(buf)

			imgBase64Str := base64.StdEncoding.EncodeToString(buf)

			tmp_r.Image = imgBase64Str
		}

		got = append(got, tmp_r)
	}

	final_all_notes, err := json.Marshal(got)
	if err != nil {
		log.Fatal("Cannot encode to JSON ", err)
	}

	w.Header().Set("Content-Type", "application/json")
	w.Write(final_all_notes)

}

func deleteCurrentNote(w http.ResponseWriter, r *http.Request) {

	decoder := json.NewDecoder(r.Body)
	var note current_note_for_user
	err := decoder.Decode(&note)
	if err != nil {
		panic(err)
	}

	note_id := uuid.MustParse(note.Note_id)

	db, error := sql.Open("postgres", connStr)
	if error != nil {
		panic(error)
	}
	defer db.Close()

	sqlStatement := "DELETE FROM note_and_video WHERE note_id = $1;"
	_, err = db.Exec(sqlStatement, note_id)
	if err != nil {
		panic(err)
	}

	sqlStatement = "DELETE FROM note_and_image WHERE note_id = $1;"
	_, err = db.Exec(sqlStatement, note_id)
	if err != nil {
		panic(err)
	}

	sqlStatement = "DELETE FROM note_and_file WHERE note_id = $1;"
	_, err = db.Exec(sqlStatement, note_id)
	if err != nil {
		panic(err)
	}

	current_path, err := os.Getwd()

	sqlStatement = "SELECT url FROM image WHERE image_id NOT IN (SELECT image_id FROM note_and_image WHERE image_id IS NOT NULL) AND image_id NOT IN (SELECT backgroundimage_id from category WHERE backgroundimage_id IS NOT NULL) AND image_id NOT IN (SELECT profileimage_id FROM settings WHERE profileimage_id IS NOT NULL) AND image_id NOT IN (SELECT themeimage_id FROM settings WHERE themeimage_id IS NOT NULL);"
	rows, err := db.Query(sqlStatement)
	if err != nil {
		panic(err)
	}

	for rows.Next() {
		var file_url string
		err = rows.Scan(&file_url)
		if err != nil {
			panic(err)
		}
		sqlStatement = "DELETE FROM image WHERE url = $1;"
		_, err = db.Exec(sqlStatement, file_url)
		if err != nil {
			panic(err)
		}
		file_url = strings.Replace(file_url, "http://localhost:8080", current_path, -1)
		err = os.Remove(file_url)
		if err != nil {
			panic(err)
		}
	}

	sqlStatement = "SELECT url FROM video WHERE video_id not in (SELECT video_id FROM note_and_video);"
	rows, err = db.Query(sqlStatement)
	if err != nil {
		panic(err)
	}

	for rows.Next() {
		var file_url string
		err = rows.Scan(&file_url)
		if err != nil {
			panic(err)
		}
		sqlStatement = "DELETE FROM video WHERE url = $1;"
		_, err = db.Exec(sqlStatement, file_url)
		if err != nil {
			panic(err)
		}
		file_url = strings.Replace(file_url, "http://localhost:8080", current_path, -1)
		err = os.Remove(file_url)
		if err != nil {
			panic(err)
		}
	}

	sqlStatement = "SELECT url FROM file WHERE file_id not in (SELECT file_id FROM note_and_file);"
	rows, err = db.Query(sqlStatement)
	if err != nil {
		panic(err)
	}

	for rows.Next() {
		var file_url string
		err = rows.Scan(&file_url)
		if err != nil {
			panic(err)
		}
		sqlStatement = "DELETE FROM file WHERE url = $1;"
		_, err = db.Exec(sqlStatement, file_url)
		if err != nil {
			panic(err)
		}
		file_url = strings.Replace(file_url, "http://localhost:8080", current_path, -1)
		err = os.Remove(file_url)
		if err != nil {
			panic(err)
		}
	}

	sqlStatement = "DELETE FROM note_versions WHERE note_id = $1;"
	_, err = db.Exec(sqlStatement, note_id)
	if err != nil {
		panic(err)
	}

	sqlStatement = "DELETE FROM user_and_note WHERE note_id = $1;"
	_, err = db.Exec(sqlStatement, note_id)
	if err != nil {
		panic(err)
	}

	sqlStatement = "DELETE FROM note WHERE note_id = $1;"
	_, err = db.Exec(sqlStatement, note_id)
	if err != nil {
		panic(err)
	}

}

type personal_info struct {
	User_id      string `json:"user_id"`
	Image        string `json:"image"`
	Firstname    string `json:"firstname"`
	Lastname     string `json:"lastname"`
	Phone_number string `json:"phone_number"`
	Email        string `json:"email"`
	About_me     string `json:"about_me"`
}

func setPersonalInfo(w http.ResponseWriter, r *http.Request) {

	decoder := json.NewDecoder(r.Body)
	var personal_data personal_info
	err := decoder.Decode(&personal_data)
	if err != nil {
		panic(err)
	}

	if len(personal_data.Email) < 6 {
		fmt.Fprintf(w, "Too short email")
		return
	}

	user_id := uuid.MustParse(personal_data.User_id)

	db, error := sql.Open("postgres", connStr)
	if error != nil {
		panic(error)
	}
	defer db.Close()

	sqlStatement := "UPDATE user_data SET firstname = $1, lastname = $2, phone = $3, about_me = $4 WHERE user_id = $5;"
	_, err = db.Exec(sqlStatement, personal_data.Firstname, personal_data.Lastname, personal_data.Phone_number, personal_data.About_me, user_id)
	if err != nil {
		panic(err)
	}

	sqlStatement = "UPDATE account SET email = $1 WHERE user_id = $2;"
	_, err = db.Exec(sqlStatement, personal_data.Email, user_id)
	if err != nil {
		panic(err)
	}

	if len(personal_data.Image) >= 1 {

		unbased, _ := base64.StdEncoding.DecodeString(personal_data.Image)
		pngI, _ := png.Decode(bytes.NewReader(unbased))
		path, _ := os.Getwd()
		image_uid := uuid.New()
		f, _ := os.OpenFile(path+"/Other_Image/"+image_uid.String()+".png", os.O_WRONLY|os.O_CREATE, 0777)
		png.Encode(f, pngI)

		personal_image_id := uuid.New()

		sqlStatement = "INSERT INTO image (image_id, url, inserted_on) SELECT $1, CAST($2 AS VARCHAR), $3 WHERE NOT EXISTS (SELECT * FROM image WHERE url = $2);"
		_, err = db.Exec(sqlStatement, personal_image_id, path+"/Other_Image/"+image_uid.String()+".png", time.Now())
		if err != nil {
			panic(err)
		}

		sqlStatement = "SELECT settings.settings_id from account inner join settings on account.settings_id = settings.settings_id where user_id = $1;"
		rows, err := db.Query(sqlStatement, user_id)
		if err != nil {
			panic(err)
		}

		var settings_id uuid.UUID

		for rows.Next() {
			err = rows.Scan(&settings_id)
			if err != nil {
				panic(err)
			}
			sqlStatement = "UPDATE settings SET profileimage_id = $1 WHERE settings_id = $2;"
			_, err = db.Exec(sqlStatement, personal_image_id, settings_id)
			if err != nil {
				panic(err)
			}
			return
		}

		settings_id = uuid.New()

		sqlStatement = "INSERT INTO settings (settings_id, profileimage_id) VALUES ($1,$2);"
		_, err = db.Exec(sqlStatement, settings_id, personal_image_id)
		if err != nil {
			panic(err)
		}

		sqlStatement = "UPDATE account SET settings_id = $1 WHERE user_id = $2;"
		_, err = db.Exec(sqlStatement, settings_id, user_id)
		if err != nil {
			panic(err)
		}

	}

}

func getPersonalInfo(w http.ResponseWriter, r *http.Request) {

	decoder := json.NewDecoder(r.Body)
	var personal_data personal_info
	err := decoder.Decode(&personal_data)
	if err != nil {
		panic(err)
	}

	var infomation personal_info
	infomation.User_id = personal_data.User_id
	infomation.About_me = ""
	infomation.Email = ""
	infomation.Firstname = ""
	infomation.Image = ""
	infomation.Lastname = ""
	infomation.Phone_number = ""

	user_id := uuid.MustParse(personal_data.User_id)

	db, error := sql.Open("postgres", connStr)
	if error != nil {
		panic(error)
	}
	defer db.Close()

	sqlStatement := "SELECT firstname, lastname, phone, about_me FROM user_data WHERE user_id = $1;"
	rows, err := db.Query(sqlStatement, user_id)
	if err != nil {
		panic(err)
	}

	for rows.Next() {
		err = rows.Scan(&infomation.Firstname, &infomation.Lastname, &infomation.Phone_number, &infomation.About_me)
		if err != nil {
			panic(err)
		}
	}

	sqlStatement = "SELECT email FROM account WHERE user_id = $1;"
	rows, err = db.Query(sqlStatement, user_id)
	if err != nil {
		panic(err)
	}

	for rows.Next() {
		err = rows.Scan(&infomation.Email)
		if err != nil {
			panic(err)
		}
	}

	sqlStatement = "SELECT url FROM account INNER JOIN settings ON account.settings_id = settings.settings_id INNER JOIN image ON settings.profileimage_id = image.image_id WHERE user_id = $1;"
	rows, err = db.Query(sqlStatement, user_id)
	if err != nil {
		panic(err)
	}

	for rows.Next() {
		var url string
		err = rows.Scan(&url)
		if err != nil {
			panic(err)
		}

		imgFile, err := os.Open(url)
		if err != nil {
			panic(err)
		}
		defer imgFile.Close()

		fInfo, _ := imgFile.Stat()
		var size int64 = fInfo.Size()
		buf := make([]byte, size)

		fReader := bufio.NewReader(imgFile)
		fReader.Read(buf)

		imgBase64Str := base64.StdEncoding.EncodeToString(buf)

		infomation.Image = imgBase64Str
	}

	final_all_notes, err := json.Marshal(infomation)
	if err != nil {
		log.Fatal("Cannot encode to JSON ", err)
	}

	w.Header().Set("Content-Type", "application/json")
	w.Write(final_all_notes)

}

type personal_image struct {
	Image string `json:"image"`
}

func getPersonalImage(w http.ResponseWriter, r *http.Request) {

	decoder := json.NewDecoder(r.Body)
	var personal_data personal_info
	err := decoder.Decode(&personal_data)
	if err != nil {
		panic(err)
	}

	var infomation personal_image
	infomation.Image = ""

	user_id := uuid.MustParse(personal_data.User_id)

	db, error := sql.Open("postgres", connStr)
	if error != nil {
		panic(error)
	}
	defer db.Close()

	sqlStatement := "SELECT url FROM account INNER JOIN settings ON account.settings_id = settings.settings_id INNER JOIN image ON settings.profileimage_id = image.image_id WHERE user_id = $1;"
	rows, err := db.Query(sqlStatement, user_id)
	if err != nil {
		panic(err)
	}

	for rows.Next() {
		var url string
		err = rows.Scan(&url)
		if err != nil {
			panic(err)
		}

		imgFile, err := os.Open(url)
		if err != nil {
			panic(err)
		}
		defer imgFile.Close()

		fInfo, _ := imgFile.Stat()
		var size int64 = fInfo.Size()
		buf := make([]byte, size)

		fReader := bufio.NewReader(imgFile)
		fReader.Read(buf)

		imgBase64Str := base64.StdEncoding.EncodeToString(buf)

		infomation.Image = imgBase64Str
	}

	final_all_notes, err := json.Marshal(infomation)
	if err != nil {
		log.Fatal("Cannot encode to JSON ", err)
	}

	w.Header().Set("Content-Type", "application/json")
	w.Write(final_all_notes)

}

type another_version_note_for_user struct {
	Note_id string `json:"note_id"`
	Version string `json:"version"`
}

type get_another_version_note struct {
	Content string `json:"content"`
}

func setVersion(w http.ResponseWriter, r *http.Request) {

	decoder := json.NewDecoder(r.Body)
	var note another_version_note_for_user
	err := decoder.Decode(&note)
	if err != nil {
		panic(err)
	}

	note_id := uuid.MustParse(note.Note_id)

	db, error := sql.Open("postgres", connStr)
	if error != nil {
		panic(error)
	}
	defer db.Close()

	var content get_another_version_note

	if note.Version == "Current" {

		sqlStatement := "SELECT content FROM note WHERE note_id = $1"
		rows, err := db.Query(sqlStatement, note_id)
		if err != nil {
			panic(err)
		}

		for rows.Next() {
			err = rows.Scan(&content.Content)
			if err != nil {
				panic(err)
			}
		}

	} else {

		layout := "2006-01-02T15:04:05.000000Z"
		str := note.Version
		updated_on, err := time.Parse(layout, str)

		if err != nil {
			panic(err)
		}

		sqlStatement := "SELECT content FROM note_versions WHERE note_id = $1 and updated_on = $2;"
		rows, err := db.Query(sqlStatement, note_id, updated_on)
		if err != nil {
			panic(err)
		}

		for rows.Next() {
			err = rows.Scan(&content.Content)
			if err != nil {
				panic(err)
			}
		}
	}

	final_all_notes, err := json.Marshal(content)
	if err != nil {
		log.Fatal("Cannot encode to JSON ", err)
	}

	w.Header().Set("Content-Type", "application/json")
	w.Write(final_all_notes)

}

type get_current_note_versions struct {
	Version time.Time `json:"version"`
}

type note_versions []get_current_note_versions

func getVersions(w http.ResponseWriter, r *http.Request) {

	decoder := json.NewDecoder(r.Body)
	var note current_note_for_user
	err := decoder.Decode(&note)
	if err != nil {
		panic(err)
	}

	note_id := uuid.MustParse(note.Note_id)

	db, error := sql.Open("postgres", connStr)
	if error != nil {
		panic(error)
	}
	defer db.Close()

	sqlStatement := "SELECT updated_on FROM note_versions WHERE updated_on not in (SELECT lastupdated FROM note where note_id = $1) and note_id = $1;"
	rows, err := db.Query(sqlStatement, note_id)
	if err != nil {
		panic(err)
	}

	var got = note_versions{}

	for rows.Next() {
		var tmp_r get_current_note_versions
		err = rows.Scan(&tmp_r.Version)
		if err != nil {
			panic(err)
		}
		got = append(got, tmp_r)
	}

	final_all_notes, err := json.Marshal(got)
	if err != nil {
		log.Fatal("Cannot encode to JSON ", err)
	}

	w.Header().Set("Content-Type", "application/json")
	w.Write(final_all_notes)

}

type category_info struct {
	User_id     string `json:"user_id"`
	Image       string `json:"image"`
	Category    string `json:"category"`
	Name        string `json:"name"`
	Text_color  string `json:"text_color"`
	Back_color  string `json:"back_color"`
	Description string `json:"description"`
}

func createCategory(w http.ResponseWriter, r *http.Request) {

	decoder := json.NewDecoder(r.Body)
	var category_data category_info
	err := decoder.Decode(&category_data)
	if err != nil {
		panic(err)
	}

	if len(category_data.Name) < 3 {
		fmt.Fprintf(w, "Too short category new name")
		return
	}

	user_id := uuid.MustParse(category_data.User_id)

	db, error := sql.Open("postgres", connStr)
	if error != nil {
		panic(error)
	}
	defer db.Close()

	if category_data.Category == "New category" {

		sqlStatement := "SELECT category_id FROM category WHERE category = $1 and user_id = $2;"
		rows, err := db.Query(sqlStatement, category_data.Name, user_id)
		if err != nil {
			panic(err)
		}

		var new_category_uuid uuid.UUID
		for rows.Next() {
			err = rows.Scan(&new_category_uuid)
			if err != nil {
				panic(err)
			}
			fmt.Fprintf(w, "This category already exists")
			return
		}

		new_category_uuid = uuid.New()

		sqlStatement = "INSERT INTO category (category_id, user_id, category, description, category_color, text_color) VALUES ($1, $2, $3, $4, $5, $6);"
		_, err = db.Exec(sqlStatement, new_category_uuid, user_id, category_data.Name, category_data.Description, category_data.Back_color, category_data.Text_color)
		if err != nil {
			panic(err)
		}

		if len(category_data.Image) >= 1 {

			unbased, _ := base64.StdEncoding.DecodeString(category_data.Image)
			jpgI, _ := jpeg.Decode(bytes.NewReader(unbased))
			path, _ := os.Getwd()
			image_uid := uuid.New()
			f, _ := os.OpenFile(path+"/Other_Image/"+image_uid.String()+".jpg", os.O_WRONLY|os.O_CREATE, 0777)
			jpeg.Encode(f, jpgI, &jpeg.Options{Quality: 100})

			personal_image_id := uuid.New()

			sqlStatement = "INSERT INTO image (image_id, url, inserted_on) SELECT $1, CAST($2 AS VARCHAR), $3 WHERE NOT EXISTS (SELECT * FROM image WHERE url = $2);"
			_, err = db.Exec(sqlStatement, personal_image_id, path+"/Other_Image/"+image_uid.String()+".jpg", time.Now())
			if err != nil {
				panic(err)
			}

			sqlStatement = "UPDATE category SET backgroundimage_id = $1 WHERE category_id = $2;"
			_, err = db.Exec(sqlStatement, personal_image_id, new_category_uuid)
			if err != nil {
				panic(err)
			}

		}

	} else {

		sqlStatement := "SELECT category_id FROM category WHERE category = $1 and user_id = $2;"
		rows, err := db.Query(sqlStatement, category_data.Name, user_id)
		if err != nil {
			panic(err)
		}

		var category_uuid uuid.UUID
		for rows.Next() {
			err = rows.Scan(&category_uuid)
			if err != nil {
				panic(err)
			}
		}

		sqlStatement = "UPDATE category SET category = $1, description = $2, category_color = $3, text_color = $4 WHERE category = $5 and user_id = $6;"
		_, err = db.Exec(sqlStatement, category_data.Name, category_data.Description, category_data.Back_color, category_data.Text_color, category_data.Category, user_id)
		if err != nil {
			panic(err)
		}

		if len(category_data.Image) >= 1 {

			unbased, _ := base64.StdEncoding.DecodeString(category_data.Image)
			jpgI, _ := jpeg.Decode(bytes.NewReader(unbased))
			path, _ := os.Getwd()
			image_uid := uuid.New()
			f, _ := os.OpenFile(path+"/Other_Image/"+image_uid.String()+".jpg", os.O_WRONLY|os.O_CREATE, 0777)
			jpeg.Encode(f, jpgI, &jpeg.Options{Quality: 100})

			personal_image_id := uuid.New()

			sqlStatement = "INSERT INTO image (image_id, url, inserted_on) SELECT $1, CAST($2 AS VARCHAR), $3 WHERE NOT EXISTS (SELECT * FROM image WHERE url = $2);"
			_, err = db.Exec(sqlStatement, personal_image_id, path+"/Other_Image/"+image_uid.String()+".jpg", time.Now())
			if err != nil {
				panic(err)
			}

			sqlStatement = "UPDATE category SET backgroundimage_id = $1 WHERE category_id = $2;"
			_, err = db.Exec(sqlStatement, personal_image_id, category_uuid)
			if err != nil {
				panic(err)
			}

		}

	}

}

type get_all_categories struct {
	Category string `json:"category"`
}

type categories []get_all_categories

func getCategoryList(w http.ResponseWriter, r *http.Request) {

	decoder := json.NewDecoder(r.Body)
	var user all_notes_for_user
	err := decoder.Decode(&user)
	if err != nil {
		panic(err)
	}

	user_id := uuid.MustParse(user.User_id)

	db, error := sql.Open("postgres", connStr)
	if error != nil {
		panic(error)
	}
	defer db.Close()

	sqlStatement := "SELECT category FROM category WHERE user_id = $1;"
	rows, err := db.Query(sqlStatement, user_id)
	if err != nil {
		panic(err)
	}

	var got = categories{}

	for rows.Next() {
		var tmp get_all_categories
		err = rows.Scan(&tmp.Category)
		if err != nil {
			panic(err)
		}
		got = append(got, tmp)
	}

	final_all_notes, err := json.Marshal(got)
	if err != nil {
		log.Fatal("Cannot encode to JSON ", err)
	}

	w.Header().Set("Content-Type", "application/json")
	w.Write(final_all_notes)

}

type current_category struct {
	User_id  string `json:"user_id"`
	Category string `json:"category"`
}

type current_category_data struct {
	Category       string `json:"category"`
	Description    string `json:"description"`
	Category_color string `json:"category_color"`
	Text_color     string `json:"text_color"`
	Image          string `json:"image"`
}

func getCategoryData(w http.ResponseWriter, r *http.Request) {

	decoder := json.NewDecoder(r.Body)
	var user current_category
	err := decoder.Decode(&user)
	if err != nil {
		panic(err)
	}

	user_id := uuid.MustParse(user.User_id)

	db, error := sql.Open("postgres", connStr)
	if error != nil {
		panic(error)
	}
	defer db.Close()

	sqlStatement := "SELECT category, description, category_color, text_color FROM category  WHERE user_id = $1 and category = $2;"
	rows, err := db.Query(sqlStatement, user_id, user.Category)
	if err != nil {
		panic(err)
	}

	var got current_category_data

	got.Category = ""
	got.Category_color = ""
	got.Description = ""
	got.Image = ""
	got.Text_color = ""

	for rows.Next() {
		err = rows.Scan(&got.Category, &got.Description, &got.Category_color, &got.Text_color)
		if err != nil {
			panic(err)
		}
	}

	sqlStatement = "SELECT url FROM category INNER JOIN image ON category.backgroundimage_id = image.image_id WHERE user_id = $1 and category = $2;"
	rows, err = db.Query(sqlStatement, user_id, user.Category)
	if err != nil {
		panic(err)
	}

	for rows.Next() {
		var url string
		err = rows.Scan(&url)
		if err != nil {
			panic(err)
		}

		imgFile, err := os.Open(url)
		if err != nil {
			panic(err)
		}
		defer imgFile.Close()

		fInfo, _ := imgFile.Stat()
		var size int64 = fInfo.Size()
		buf := make([]byte, size)

		fReader := bufio.NewReader(imgFile)
		fReader.Read(buf)

		imgBase64Str := base64.StdEncoding.EncodeToString(buf)

		got.Image = imgBase64Str

	}

	final_all_notes, err := json.Marshal(got)
	if err != nil {
		log.Fatal("Cannot encode to JSON ", err)
	}

	w.Header().Set("Content-Type", "application/json")
	w.Write(final_all_notes)

}

type data_for_new_group struct {
	User_id    string `json:"user_id"`
	Group_name string `json:"group_name"`
}

func createGroup(w http.ResponseWriter, r *http.Request) {

	/*decoder := json.NewDecoder(r.Body)
	var user data_for_new_group
	err := decoder.Decode(&user)
	if err != nil {
		panic(err)
	}

	user_id := uuid.MustParse(user.User_id)

	db, error := sql.Open("postgres", connStr)
	if error != nil {
		panic(error)
	}
	defer db.Close()

	sqlStatement := "SELECT group_id FROM group_data  WHERE user_id = $1 and group_name = $2;"
	rows, err := db.Query(sqlStatement, user_id, user.Group_name)
	if err != nil {
		panic(err)
	}*/

}

func main() {

	fs := http.FileServer(http.Dir(""))
	http.Handle("/", fs)

	http.HandleFunc("/upload_text", uploadText)
	http.HandleFunc("/upload_image", uploadImage)
	http.HandleFunc("/upload_video", uploadVideo)
	http.HandleFunc("/upload_file", uploadFile)

	http.HandleFunc("/signIn/", signIn)
	http.HandleFunc("/registration/", registration)
	http.HandleFunc("/getusernotes", getUserNotes)
	http.HandleFunc("/newnote/", newNote)
	http.HandleFunc("/sendcurrentnote", sendCurrentNote)
	http.HandleFunc("/getcurrentnote", getCurrentNote)
	http.HandleFunc("/setversion", setVersion)
	http.HandleFunc("/getversions", getVersions)
	http.HandleFunc("/deletecurrentnote", deleteCurrentNote)

	http.HandleFunc("/getpersonalinfo", getPersonalInfo)
	http.HandleFunc("/getpersonalimage", getPersonalImage)
	http.HandleFunc("/setpersonalinfo", setPersonalInfo)

	http.HandleFunc("/createcategory", createCategory)
	http.HandleFunc("/getcategorylist", getCategoryList)
	http.HandleFunc("/getcategorydata", getCategoryData)

	http.HandleFunc("/creategroup", createGroup)

	log.Fatal(http.ListenAndServe(":8080", nil))

}
