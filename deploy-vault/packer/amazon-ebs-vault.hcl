listener "tcp" {
  address = "0.0.0.0:8200"

  # Temporarily disable tls.
  tls_disable = "true"
}

storage "dynamodb" {
  region = "us-east-1"
  table = "vault-data"
}

# Something around Amazon KMS for auto-unseal
