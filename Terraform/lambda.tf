
resource "aws_lambda_function" "aws_waf_logs_lambda"{
  function_name = "lambda_function"
  role = aws_iam_role.lambda.arn
  runtime = "python3.8"
  handler = "filename.handler_function"
  filename = "aws_waf_logs_lambda.zip"

}

resource "aws_iam_role" "lambda" {
  name = "lambda"

  assume_role_policy = <<EOF
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Action": "sts:AssumeRole",
      "Principal": {
        "Service": "lambda.amazonaws.com"
      },
      "Effect": "Allow",
      "Sid": ""
    }
  ]
}
EOF
}