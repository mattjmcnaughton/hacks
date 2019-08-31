package main

import (
	"crypto/tls"
	http_helper "github.com/gruntwork-io/terratest/modules/http-helper"
	"github.com/gruntwork-io/terratest/modules/terraform"
	"testing"
	"time"
)

func TestWebServer(t *testing.T) {
	terraformOptions := &terraform.Options{
		TerraformDir: "../web-server",
	}

	defer terraform.Destroy(t, terraformOptions)

	terraform.InitAndApply(t, terraformOptions)

	url := terraform.Output(t, terraformOptions, "url")

	tlsConfig := tls.Config{}

	status := 200
	text := "Hello, world"
	retries := 30
	sleep := 5 * time.Second

	http_helper.HttpGetWithRetry(t, url, &tlsConfig, status, text, retries, sleep)
}
