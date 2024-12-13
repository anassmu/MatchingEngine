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

private:
    // prioritize highest bids
    std::map<int, std::vector<PlaceOrder>, std::greater<>> buyOrders;

    // prioritize lowest asks
    std::map<int, std::vector<PlaceOrder>> sellOrders;
};

#endif // ORDER_BOOK_H
