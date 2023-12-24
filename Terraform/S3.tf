resource "aws_s3_bucket" "aws-waf-logs-terraform-test"{
  bucket = "aws-waf-logs-terraform-test"

  tags = {
    Name = "waf-logs-bucket"
  }
}