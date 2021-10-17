package main

import (
	"fmt"
	"io/ioutil"
	"net/http"
	"os"
)

func main() {
	client := &http.Client{}
	todoistUrl := "https://api.todoist.com/rest/v1/projects"
	req, err := http.NewRequest("GET", todoistUrl, nil)

	token := os.Getenv("TODOIST_TOKEN")

	req.Header.Add("Authorization", fmt.Sprintf("Bearer %s", token))

	resp, err := client.Do(req)
	if err != nil {
		panic(err)
	}

	defer resp.Body.Close()

	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		panic(err)
	}

	println(string(body))
}
