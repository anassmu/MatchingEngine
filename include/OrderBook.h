#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include <map>
#include <vector>
#include "MessageTypes.h"

class OrderBook {
public:
    void addOrder(const PlaceOrder& order);
    void cancelOrder(int orderId);
    void printOrderBook() const;

    std::vector<PlaceOrder>& getBestBuyOrder();
    std::vector<PlaceOrder>& getBestSellOrder();

    bool hasBuyOrders() const { return !buyOrders.empty(); }
    bool hasSellOrders() const { return !sellOrders.empty(); }

    // update after a trade
    void updateBuyOrder(int price, int amount);
    void updateSellOrder(int price, int amount);

private:
    // prioritize highest bids
    std::map<int, std::vector<PlaceOrder>, std::greater<>> buyOrders;

    // prioritize lowest asks
    std::map<int, std::vector<PlaceOrder>> sellOrders;
};

#endif // ORDER_BOOK_H
