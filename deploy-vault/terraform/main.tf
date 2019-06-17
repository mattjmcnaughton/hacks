
resource "aws_vpc" "vault_demo" {
  cidr_block = "10.0.0.0/16"

  tags = {
    Name = "vault_demo"
    team = "vault_demo"
    env = "test"
  }
}

resource "aws_kms_key" "vault_demo_unsealor" {
  description = "Key for auto-unseal Hashicorp vault"

  tags = {
    Name = "vault_demo_unsealor"
    team = "vault_demo"
    env = "test"
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
      "Resource": "*"
      "Effect": "Allow",
      "Sid": ""
    }
  ]
}
EOF
}

resource "aws_iam_policy" "access_dynamo_db" {

}

resource "aws_iam_role_policy_attachment" "attach_vault_demo_ec2_to_access_kms_key" {
  role = "${aws_iam_role.vault_demo_ec2.name}"
  policy_arn = "${aws_iam_policy.access_kms_key.arn}"
}

resource "aws_iam_role_policy_attachment" "attach_vault_demo_ec2_to_access_dynamo_db" {
  role = "${aws_iam_role.vault_demo_ec2.name}"
  policy_arn = "${aws_iam_policy.access_dynamo_db.arn}"
}
