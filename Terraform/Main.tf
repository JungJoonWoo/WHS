locals {
  common_tags = {
    terraform = "true"
  }
}

#Web-ACL 생성
resource "aws_wafv2_web_acl" "wafv2-web-acl"{
  name = "wafv2-web-acl"
  scope = "REGIONAL"

  default_action {
    allow {

    }
  }
  visibility_config {
    cloudwatch_metrics_enabled = false
    metric_name                = "WAF_Common_Protections"
    sampled_requests_enabled   = false
  }

  #AWSManagedRulesCommonRuleSet
  rule{
    name = "AWS-AWSManagedRulesCommonRuleSet"
    priority = 0
    statement{
      managed_rule_group_statement {
        name        = "AWSManagedRulesCommonRuleSet"
        vendor_name = "AWS"
      }
    }
    visibility_config {
      cloudwatch_metrics_enabled = false
      metric_name                = "AWS-AWSManagedRulesCommonRuleSet"
      sampled_requests_enabled   = false
    }
  }

  #AWSManagedRulesLinuxRuleSet
  rule{
    name = "AWS-AWSManagedRulesLinuxRule"
    priority = 1
    statement {
      managed_rule_group_statement {
        name        = "AWSManagedRulesLinuxRuleSet"
        vendor_name = "AWS"
      }
    }
    visibility_config{
      cloudwatch_metrics_enabled = false
      metric_name                = "AWS-AWSManagedRulesLinuxRuleSet"
      sampled_requests_enabled   = false
    }
  }
  #AWSManagedRulesWindowsRuleSet
  rule{
    name = "AWS-AWSManagedRulesWindowsRuleSet"
    priority = 9
    statement {
      managed_rule_group_statement {
        name        = "AWSManagedRulesWindowsRuleSet"
        vendor_name = "AWS"
      }
    }
    visibility_config {
      cloudwatch_metrics_enabled = false
      metric_name                = "AWS-AWSManagedRulesWindowsRuleSet"
      sampled_requests_enabled   = false
    }
  }

  #속도 기반 규칙에 따라 동일 IP에서 5분에 200번 이상 접속을 요청하면 차단하는 규칙
  rule{
    name = "RateBasedRule"
    priority = 10

    action{
      block {
      }
    }
    statement {
      rate_based_statement {
        aggregate_key_type = "IP"
        limit = 200
      }
    }
    visibility_config {
      cloudwatch_metrics_enabled = false
      metric_name                = "RateBasedRule"
      sampled_requests_enabled   = false
    }
  }

  tags = merge(
    local.common_tags, {
      customer = "wafv2-web-acl"
    }
  )
}