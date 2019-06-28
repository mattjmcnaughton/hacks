provider "aws" {
  region = "us-east-1"
}

terraform {
  backend "s3" {
    bucket  = "mattjmcnaughton-terraform-test"
    key     = "deploy-vault"
    region  = "us-east-1"
    encrypt = true
  }
}
