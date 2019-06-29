resource "aws_vpc" "vault_demo" {
  cidr_block = "10.0.0.0/16"

  tags = {
    Name = "vault_demo"
    team = "vault_demo"
    env  = "test"
  }
}

# This is a rough scaffolding of what is necessary to support accessing hosts in
# a vpc.
resource "aws_internet_gateway" "vault_demo" {
  vpc_id = aws_vpc.vault_demo.id
}

resource "aws_route_table" "public" {
  vpc_id = aws_vpc.vault_demo.id
}

resource "aws_route_table_association" "public_ea" {
  subnet_id = aws_subnet.vault_demo_subnet_ea.id
  route_table_id = aws_route_table.public.id
}

resource "aws_route_table_association" "public_eb" {
  subnet_id = aws_subnet.vault_demo_subnet_eb.id
  route_table_id = aws_route_table.public.id
}

resource "aws_route" "public_internet_gateway" {
  route_table_id = aws_route_table.public.id
  destination_cidr_block = "0.0.0.0/0"
  gateway_id = aws_internet_gateway.vault_demo.id
}

resource "aws_subnet" "vault_demo_subnet_ea" {
  vpc_id = aws_vpc.vault_demo.id
  cidr_block = "10.0.0.0/24"
  availability_zone = "us-east-1a"

  # Temporary until I have the VPN setup.
  map_public_ip_on_launch = true
}

resource "aws_subnet" "vault_demo_subnet_eb" {
  vpc_id = aws_vpc.vault_demo.id
  cidr_block = "10.0.1.0/24"
  availability_zone = "us-east-1b"

  # Temporary until I have the VPN setup.
  map_public_ip_on_launch = true
}

resource "aws_kms_key" "vault_demo_unsealor" {
  description = "Key for auto-unseal Hashicorp vault"

  tags = {
    Name = "vault_demo_unsealor"
    team = "vault_demo"
    env  = "test"
  }
}

resource "aws_iam_role" "vault_demo_ec2" {
  name = "vault_demo_ec2"

  # Allows an ec2 machine to assume the role.
  assume_role_policy = <<EOF
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Action": "sts:AssumeRole",
      "Principal": {
        "Service": "ec2.amazonaws.com"
      },
      "Effect": "Allow",
      "Sid": ""
    }
  ]
}
EOF

}

resource "aws_iam_instance_profile" "vault_demo_ec2" {
  name = "vault_demo_ec2"
  role = aws_iam_role.vault_demo_ec2.name
}

resource "aws_iam_policy" "vault_demo_access_kms_key" {
  name = "vault_demo_access_kms_key"
  description = "Access Kms key for encrypting/decrypting"

  # For now, this is much to loose a policy. It allows access to any KMS key. We
  # want to make more restrictive.
  policy = <<EOF
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Action": [
        "kms:ListKeys",
        "kms:ListAliases",
        "kms:DescribeKey",
        "kms:ListKeyPolicies",
        "kms:GetKeyPolicy",
        "kms:GetKeyRotationStatus",
        "iam:ListUsers",
        "iam:ListRoles",
        "kms:Encrypt",
        "kms:Decrypt"
      ],
      "Resource": "*",
      "Effect": "Allow",
      "Sid": ""
    }
  ]
}
EOF

}

resource "aws_iam_role_policy_attachment" "attach_vault_demo_ec2_to_access_kms_key" {
  role       = aws_iam_role.vault_demo_ec2.name
  policy_arn = aws_iam_policy.vault_demo_access_kms_key.arn
}

# This is too generous a permission.
resource "aws_iam_role_policy_attachment" "attach_vault_demo_ec2_to_dynamo_db_full_access" {
  role       = aws_iam_role.vault_demo_ec2.name
  policy_arn = "arn:aws:iam::aws:policy/AmazonDynamoDBFullAccess"
}

resource "aws_key_pair" "mattjmcnaughton_personal_rsa" {
  key_name = "mattjmcnaughton_personal_rsa"
  public_key = file("~/.ssh/mattjmcnaughton_personal_rsa.pub")
}

resource "aws_security_group" "allow_ssh" {
  name = "allow_ssh"
  description = "Allow SSH from all IPs [INSECURE]"
  vpc_id = aws_vpc.vault_demo.id

  ingress {
    from_port = 22
    to_port = 22
    protocol = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }
}

resource "aws_security_group" "all_outbound" {
  name = "all_outbound"
  description = "Allow all outbound connections"
  vpc_id = aws_vpc.vault_demo.id

  egress {
    from_port = 0
    to_port = 0
    protocol = -1
    cidr_blocks = ["0.0.0.0/0"]
  }
}

# Need to set this so that we can delete the auto-scaling group without deleting
# it.
resource "aws_launch_configuration" "vault_demo_launch_configuration" {
  name_prefix = "vault_demo"
  # This should be a variable
  image_id = "ami-002b9f3b851cb1c54"
  # Shouldn't be the final value.
  instance_type = "t3.medium"

  # We will add start up commands via `user_data` later.
  user_data = filebase64("${path.module}/user_data.sh")

  iam_instance_profile = aws_iam_instance_profile.vault_demo_ec2.name
  security_groups = [aws_security_group.allow_ssh.id, aws_security_group.all_outbound.id]
  associate_public_ip_address = true
  key_name = aws_key_pair.mattjmcnaughton_personal_rsa.key_name
}

resource "aws_autoscaling_group" "vault_demo_asg" {
  desired_capacity = 1
  max_size = 1
  min_size = 1

  # Only wait 1 second before can apply auto-scaling behavior.
  default_cooldown = 1
  health_check_grace_period = 60

  vpc_zone_identifier = [aws_subnet.vault_demo_subnet_ea.id, aws_subnet.vault_demo_subnet_eb.id]

  launch_configuration = aws_launch_configuration.vault_demo_launch_configuration.name
}
