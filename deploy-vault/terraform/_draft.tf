resource "aws_iam_policy" "access_dynamo_db" {

}

resource "aws_iam_role_policy_attachment" "attach_vault_demo_ec2_to_access_dynamo_db" {
  role = "${aws_iam_role.vault_demo_ec2.name}"
  policy_arn = "${aws_iam_policy.access_dynamo_db.arn}"
}
