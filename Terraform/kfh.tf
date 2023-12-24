resource "aws_kinesis_firehose_delivery_stream" "waf_firehose_stream"{
  name = "waf_firehose_stream"
  destination = "elasticsearch"

  elasticsearch_configuration {
    index_name = "aws-waf-logs"
    role_arn   = aws_iam_role.firehose_role.arn
    domain_arn = aws_elasticsearch_domain.domain.arn
    s3_backup_mode = "AllDocuments"
    s3_configuration {
      bucket_arn = aws_s3_bucket.aws-waf-logs-terraform-test.arn
      role_arn   = aws_iam_role.firehose_role.arn
      buffering_size     = 10
      buffering_interval = 400
      compression_format = "GZIP"
    }
  }

}

#firehose iam, 다른 aws 서비스
resource "aws_iam_role" "firehose_role" {
  name = "firehose_role"

  assume_role_policy = <<EOF
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Action": "sts:AssumeRole",
      "Principal": {
        "Service": "firehose.amazonaws.com"
      },
      "Effect": "Allow",
      "Sid": ""
    }
  ]
}
EOF
}

resource "aws_iam_role_policy" "firehose_policy" {
  name = "firehose_policy"
  role   = aws_iam_role.firehose_role.id
  policy = <<EOF
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Effect": "Allow",
      "Action": [
        "s3:*",
        "es:*"
      ],
      "Resource": "*"
    }
  ]
}
EOF

}