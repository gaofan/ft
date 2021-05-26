// Copyright [2020] <Copyright Kevin, kevin.lau.gd@gmail.com>

#ifndef FT_INCLUDE_FT_COMPONENT_POSITION_CALCULATOR_H_
#define FT_INCLUDE_FT_COMPONENT_POSITION_CALCULATOR_H_

#include <functional>
#include <memory>
#include <unordered_map>

#include "ft/base/trade_msg.h"

namespace ft {

class PositionCalculator {
 public:
  using CallbackType = std::function<void(const Position&)>;

 public:
  PositionCalculator();

  void SetCallback(CallbackType&& f);

  // 直接设置仓位，会将现有的仓位覆盖
  void SetPosition(const Position& pos);

  // 二级市场买卖申报，更新交易品种的待成交数量
  void UpdatePending(uint32_t ticker_id, Direction direction, Offset offset, int changed);

  // 二级市场买卖成交，更新交易品种的持仓
  void UpdateTraded(uint32_t ticker_id, Direction direction, Offset offset, int traded,
                    double traded_price);

  // 更新浮动盈亏
  void UpdateFloatPnl(uint32_t ticker_id, double bid, double ask);

  const Position* GetPosition(uint32_t ticker_id) const {
    auto iter = positions_.find(ticker_id);
    if (iter == positions_.end()) {
      return nullptr;
    }
    return &iter->second;
  }

  // 获取持仓的总资产
  double TotalAssets() const;

 private:
  std::unordered_map<uint32_t, Position> positions_;
  std::unique_ptr<CallbackType> cb_;
};

}  // namespace ft

#endif  // FT_INCLUDE_FT_COMPONENT_POSITION_CALCULATOR_H_
