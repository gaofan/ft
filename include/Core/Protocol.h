// Copyright [2020] <Copyright Kevin, kevin.lau.gd@gmail.com>

#ifndef FT_INCLUDE_CORE_PROTOCOL_H_
#define FT_INCLUDE_CORE_PROTOCOL_H_

#include <fmt/format.h>

#include <cstdint>
#include <string>

namespace ft {

using StrategyIdType = char[16];

/*
 * 这部分是TradingEngine和Gateway之间的交互协议
 */

// 这个是TradingEngine发给Gateway的下单信息
struct OrderReq {
  /*
   * 这个ID是给风控使用的，因为风控在发单前需要检查订单，如果后续发单失败，
   * 需要通过某种途径通知风控模块该订单对应于之前的哪个请求。Gateway返回的
   * 订单号要在发单之后才能知道，而风控在发单前就需要把订单能一一对应起来，
   * 于是TradingEngine会维护这个engine_order_id
   */
  uint64_t engine_order_id;

  /*
   * 这个ID是策略发单的时候提供的，使策略能对应其订单回报
   */
  uint32_t user_order_id;

  uint32_t ticker_index;
  uint32_t type;
  uint32_t direction;
  uint32_t offset;
  int volume = 0;
  double price = 0;
} __attribute__((packed));

/*
 * 这部分是Strategy和TradingEngine之间的交互协议
 * Strategy通过IPC向TradingEngine发送交易相关指令
 */

inline const uint32_t TRADER_CMD_MAGIC = 0x1709394;

enum TraderCmdType { NEW_ORDER = 1, CANCEL_ORDER, CANCEL_TICKER, CANCEL_ALL };

struct TraderOrderReq {
  uint32_t user_order_id;
  uint32_t ticker_index;
  uint32_t direction;
  uint32_t offset;
  uint32_t type;
  int volume;
  double price;
} __attribute__((packed));

struct TraderCancelReq {
  uint64_t order_id;
} __attribute__((packed));

struct TraderCancelTickerReq {
  uint32_t ticker_index;
} __attribute__((packed));

struct TraderCommand {
  uint32_t magic;
  uint32_t type;
  StrategyIdType strategy_id;
  union {
    TraderOrderReq order_req;
    TraderCancelReq cancel_req;
    TraderCancelTickerReq cancel_ticker_req;
  };
} __attribute__((packed));

/*
 *
 */
struct OrderResponse {
  uint32_t user_order_id;
  uint32_t order_id;
  uint32_t ticker_index;
  uint32_t direction;
  uint32_t offset;
  int original_volume;
  int traded_volume;

  bool completed;
  uint32_t this_traded;
  double this_traded_price;
} __attribute__((packed));

constexpr const char* const TRADER_CMD_TOPIC = "trader_cmd";

inline std::string proto_md_topic(const std::string& ticker) {
  return fmt::format("md-{}", ticker);
}

inline std::string proto_pos_key(const std::string& ticker) {
  return fmt::format("pos-{}", ticker);
}

}  // namespace ft

#endif  // FT_INCLUDE_CORE_PROTOCOL_H_