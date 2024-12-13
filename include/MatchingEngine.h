#ifndef MATCHING_ENGINE_H
#define MATCHING_ENGINE_H

#include <vector>
#include <atomic>
#include "MessageTypes.h"
#include "OrderBook.h"
#include "ThreadSafeQueue.h"

class MatchingEngine {
public:
    MatchingEngine();

    void handleIncomingOrders(ThreadSafeQueue<PlaceOrder>& queue);
    void stopProcessing();

    OrderPlaced handlePlaceOrder(const PlaceOrder& order);
    OrderCanceled handleCancelOrder(int orderId);

    const OrderBook& getOrderBook() const;

    // return a list of traded orders
    std::vector<OrderTraded> processMatching();

private:
    OrderBook orderBook;
    // should continue running ?
    std::atomic<bool> processing_;
};

#endif // MATCHING_ENGINE_H