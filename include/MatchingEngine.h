#ifndef MATCHING_ENGINE_H
#define MATCHING_ENGINE_H

#include <vector>
#include <atomic>
#include <optional>
#include "MessageTypes.h"
#include "OrderBook.h"
#include "ThreadSafeQueue.h"

class MatchingEngine {
public:
    MatchingEngine();

    void handleIncomingOrders(ThreadSafeQueue<PlaceOrder>& placeQueue, ThreadSafeQueue<int>& cancelQueue);
    void stopProcessing();

    std::optional<RequestRejected> handlePlaceOrder(const PlaceOrder& order);
    std::optional<RequestRejected> handleCancelOrder(int orderId);

    const OrderBook& getOrderBook() const;

    // return a list of traded orders
    std::vector<OrderTraded> processMatching();

private:
    OrderBook orderBook;
    // should continue running ?
    std::atomic<bool> processing_;
};

#endif // MATCHING_ENGINE_H