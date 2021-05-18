// Copyright [2020] <Copyright Kevin, kevin.lau.gd@gmail.com>

#ifndef FT_INCLUDE_FT_BASE_CONFIG_H_
#define FT_INCLUDE_FT_BASE_CONFIG_H_

#include <string>
#include <vector>

namespace ft {

struct GlobalConfig {
  std::string contract_file;
};

struct OmsConfig {
  std::string contract_file;
};

struct GatewayConfig {
  std::string api;
  std::string trade_server_address;
  std::string quote_server_address;
  std::string broker_id;
  std::string investor_id;
  std::string password;
  std::string auth_code;
  std::string app_id;
  std::vector<std::string> subscription_list;

  bool cancel_outstanding_orders_on_startup;

  std::string arg0;
  std::string arg1;
  std::string arg2;
  std::string arg3;
};

struct RmsConfig {
  uint64_t throttle_rate_limit_period_ms = 0;
  uint64_t throttle_rate_order_limit = 0;
  uint64_t throttle_rate_volume_limit = 0;
};

struct StrategyConfig {
  std::string strategy_name;
  std::string trade_mq_name;
  std::string rsp_mq_name;
  std::string md_mq_name;
  std::vector<std::string> subscription_list;
};

struct FlareTraderConfig {
  bool Load(const std::string& file);

  GlobalConfig global_config;
  OmsConfig oms_config;
  GatewayConfig gateway_config;
  RmsConfig rms_config;
  std::vector<StrategyConfig> strategy_config_list;
};

}  // namespace ft

#endif  // FT_INCLUDE_FT_BASE_CONFIG_H_
