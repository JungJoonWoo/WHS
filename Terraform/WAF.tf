#Web-ACL 생성
resource "aws_wafv2_web_acl" "wafv2-web-acl-terraform"{
  name = "wafv2-web-acl-terraform"
  scope = "REGIONAL"

  default_action {
    allow {

    }
  }
  visibility_config {
    cloudwatch_metrics_enabled = true
    metric_name                = "WAF_Common_Protections"
    sampled_requests_enabled   = true
  }

  #AWSManagedRulesCommonRuleSet
#  rule{
#    name = "AWS-AWSManagedRulesCommonRuleSet"
#    priority = 1
#    statement{
#      managed_rule_group_statement {
#        name        = "AWSManagedRulesCommonRuleSet"
#        vendor_name = "AWS"
#      }
#    }
#    visibility_config {
#      cloudwatch_metrics_enabled = false
#      metric_name                = "AWS-AWSManagedRulesCommonRuleSet"
#      sampled_requests_enabled   = false
#    }
#  }

  #AWSManagedRulesLinuxRuleSet
#  rule{
#    name = "AWS-AWSManagedRulesLinuxRule"
#    priority = 2
#    statement {
#      managed_rule_group_statement {
#        name        = "AWSManagedRulesLinuxRuleSet"
#        vendor_name = "AWS"
#      }
#    }
#    visibility_config{
#      cloudwatch_metrics_enabled = false
#      metric_name                = "AWS-AWSManagedRulesLinuxRuleSet"
#      sampled_requests_enabled   = false
#    }
#  }
  #AWSManagedRulesWindowsRuleSet
#  rule{
#    name = "AWS-AWSManagedRulesWindowsRuleSet"
#    priority = 3
#    statement {
#      managed_rule_group_statement {
#        name        = "AWSManagedRulesWindowsRuleSet"
#        vendor_name = "AWS"
#      }
#    }
#    visibility_config {
#      cloudwatch_metrics_enabled = false
#      metric_name                = "AWS-AWSManagedRulesWindowsRuleSet"
#      sampled_requests_enabled   = false
#    }
#  }

  #속도 기반 규칙에 따라 동일 IP에서 5분에 200번 이상 접속을 요청하면 차단하는 규칙
#  rule{
#    name = "RateBasedRule"
#    priority = 4
#
#    action{
#      block {
#      }
#    }
#    statement {
#      rate_based_statement {
#        aggregate_key_type = "IP"
#        limit = 200
#      }
#    }
#    visibility_config {
#      cloudwatch_metrics_enabled = false
#      metric_name                = "RateBasedRule"
#      sampled_requests_enabled   = false
#    }
#  }

  tags = merge(
    local.common_tags, {
      customer = "wafv2-web-acl"
    }
  )
}

resource "aws_wafv2_web_acl_association" "wafv2_association"{

  resource_arn = aws_lb.application-load-balancer.arn
  web_acl_arn  = aws_wafv2_web_acl.wafv2-web-acl-terraform.arn

}

resource "aws_wafv2_web_acl_logging_configuration" "wafv2_logging_configuration" {
  log_destination_configs = [aws_kinesis_firehose_delivery_stream.waf_firehose_stream.arn]
  resource_arn            = aws_wafv2_web_acl.wafv2-web-acl-terraform.arn
}