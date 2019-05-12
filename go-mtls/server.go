package main

import (
	"crypto/tls"
	"crypto/x509"
	"io"
	"io/ioutil"
	"log"
	"net/http"
)

func helloHandler(w http.ResponseWriter, r *http.Request) {
	io.WriteString(w, "Hello World!\n")
}

func main() {
	http.HandleFunc("/hello", helloHandler)

	// Create a CA certificate pool and add clientCert.pem to it.
	caCert, err := ioutil.ReadFile("clientCert.pem")
	if err != nil {
		log.Fatal(err)
	}

	caCertPool := x509.NewCertPool()
	caCertPool.AppendCertsFromPEM(caCert)

	// Create the TLS config with the CA pool and enable Client certificate
	// validation
	tlsConfig := &tls.Config{
		ClientCAs: caCertPool,
		// Enforces mutual TLS.
		ClientAuth: tls.RequireAndVerifyClientCert,
	}

	tlsConfig.BuildNameToCertificate()

	server := &http.Server{
		Addr:      ":8443",
		TLSConfig: tlsConfig,
	}

	log.Fatal(server.ListenAndServeTLS("serverCert.pem", "serverKey.pem"))
}
