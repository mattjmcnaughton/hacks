package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"os"
)

type Project struct {
	Id           int    `json:"id"`
	Color        int    `json:"color"`
	Name         string `json:"name"`
	CommentCount int    `json:"comment_count"`
	Shared       bool   `json:"shared"`
	Favorite     bool   `json:"favorite"`
	SyncId       int    `json:"sync_id"`
	InboxProject bool   `json:"inbox_project"`
	Url          string `json:"url"`
}

func main() {
	client := &http.Client{}
	todoistUrl := "https://api.todoist.com/rest/v1/projects"
	req, err := http.NewRequest("GET", todoistUrl, nil)

	token := os.Getenv("TODOIST_TOKEN")

	req.Header.Add("Authorization", fmt.Sprintf("Bearer %s", token))

	resp, err := client.Do(req)
	if err != nil {
		log.Fatalf(err.Error())
	}

	defer resp.Body.Close()

	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		log.Fatalf(err.Error())
	}

	var projs []Project
	err = json.Unmarshal([]byte(body), &projs)
	if err != nil {
		log.Fatalf(err.Error())
	}

	fmt.Printf("proj url: %#v\n", projs[0].Url)
}
