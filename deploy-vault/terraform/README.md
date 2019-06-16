# terraform

To deploy vault, we need the following:

- VPC to deploy into
- KMS for auto-unsealing vault
  - https://blog.gruntwork.io/a-guide-to-automating-hashicorp-vault-1-auto-unsealing-b219970f02c6
    - KMS for key... via terraform
- IAM profile for vault ec2 instance
- Amazon Dynamo DB (should I let vault configure or do I want to create?)
  - IAM profile for vault ec2 instance
  - Apache Dynamo DB (should I let vault configure or do I want to create?)
- EC2 instance/AutoScaling Group
- Security group

Note, in the future, much of this infrastructure will be base level
infrastructure.
