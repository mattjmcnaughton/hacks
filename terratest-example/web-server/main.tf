provider "aws" {
  region = "us-east-2"
}

resource "aws_instance" "web_server" {
  ami = "ami-07e26819c90e50327"
  instance_type = "t2.micro"
  vpc_security_group_ids = ["${aws_security_group.web_server.id}"]

  user_data = <<-EOF
              #!/bin/bash
              echo "Hello, world" > index.html
              nohup busybox httpd -f -p 8080 &
              EOF
}

resource "aws_security_group" "web_server" {
  ingress {
    from_port = 8080
    to_port = 8080
    protocol = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }
}

output "url" {
  value = "http://${aws_instance.web_server.public_ip}:8080"
}
