#ifndef MATCHING_ENGINE_H
#define MATCHING_ENGINE_H

#include <vector>
#include "MessageTypes.h"
#include "OrderBook.h"

class MatchingEngine {
public:

    OrderPlaced handlePlaceOrder(const PlaceOrder& order);
    OrderCanceled handleCancelOrder(int orderId);

    const OrderBook& getOrderBook() const;

    // return a list of traded orders
    std::vector<OrderTraded> processMatching();

private:
    OrderBook orderBook;
};

#endif // MATCHING_ENGINE_H