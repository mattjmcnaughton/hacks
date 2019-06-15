# deploy-vault

Exploration into deploying Hashicorp Vault.

## Guidelines

- Bake AMI using Packer
  - Ubuntu 18.04
- Deploy via Auto-Scaling Group
- Use DynamoDB for storage (allow Vault to create db)
  - IAM policy who can write to DynamoDB
  - Attach to ec2 host running vault
- Ansible playbook for one off commands
- Terraform to deploy all AWS infra
- For now, use my own self-signed certs (long term, I want to store these in s3
  and initiate as part of my bootstrapping)
- Allow 8200 everywhere and 22 for whitelisted ips (eventually my own VPN)
- Use auto-unsealing:
  https://blog.gruntwork.io/a-guide-to-automating-hashicorp-vault-1-auto-unsealing-b219970f02c6
  - KMS for key... via terraform
- Inspec to test

## Unclear

- What steps do I need to perform when recreating an instance? Will it work out
  of the box? Do I need to unlock it on the new host?
  - How does this relate to auto-unsealing?
