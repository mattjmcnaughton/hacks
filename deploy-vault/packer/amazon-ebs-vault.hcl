listener "tcp" {
  address = "0.0.0.0:8200"
}

# Eventually this should be DynamoDB.
storage "file" {
  path = "/vault"
}
