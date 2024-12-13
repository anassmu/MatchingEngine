#include "MatchingEngine.h"
#include <iostream>
#include <thread>

MatchingEngine::MatchingEngine() : processing_(true) {}

void MatchingEngine::handleIncomingOrders(ThreadSafeQueue<PlaceOrder>& placeQueue, ThreadSafeQueue<int>& cancelQueue) {
    while (processing_) {
        // cancel requests
        int cancelOrderId;
        while (!cancelQueue.empty()) {
            if (cancelQueue.pop(cancelOrderId)) {
                handleCancelOrder(cancelOrderId);
            }
        }
        // place orders
        PlaceOrder order;
        if (placeQueue.pop(order)) {
            if (order.orderId == -1) {
                std::cout << "stop signal received.\n";
                break;
            }
            handlePlaceOrder(order);
        }
        processMatching();
    }
}

void MatchingEngine::stopProcessing() {
    processing_ = false;
}

std::optional<RequestRejected> MatchingEngine::handlePlaceOrder(const PlaceOrder& order) {
    if (order.price <= 0 || order.amount <= 0) {
        return RequestRejected{
            order.orderId,
            "Invalid order: Price and amount must be greater than 0."
        };
    }
    orderBook.addOrder(order);
    // no reject
    return std::nullopt; 
}

std::optional<RequestRejected> MatchingEngine::handleCancelOrder(int orderId) {
    if (!orderBook.cancelOrder(orderId)) {
        return RequestRejected{
            orderId,
            "Order not found: Unable to cancel the order."
        };
    }
    // no reject
    return std::nullopt;
}

const OrderBook& MatchingEngine::getOrderBook() const {
    return orderBook;
}

std::vector<OrderTraded> MatchingEngine::processMatching() {
    std::vector<OrderTraded> trades;

    while (orderBook.hasBuyOrders() && orderBook.hasSellOrders()) {

        //  the best buy and sell orders info
        auto& bestBuyOrders = orderBook.getBestBuyOrder();
        auto& bestSellOrders = orderBook.getBestSellOrder();
        int bestBuyPrice = bestBuyOrders.front().price;
        int bestSellPrice = bestSellOrders.front().price;

        // trade is possible
        if (bestBuyPrice >= bestSellPrice) {

            int tradedAmount = std::min(bestBuyOrders.front().amount, bestSellOrders.front().amount);
            int tradedPrice = bestBuyPrice;  // the buyer's price is used for the trade

            trades.push_back({bestBuyOrders.front().orderId, tradedPrice, tradedAmount});
            trades.push_back({bestSellOrders.front().orderId, tradedPrice, tradedAmount});

            std::cout << "trade executed: buyer ID = " << bestBuyOrders.front().orderId
                                << ", seller ID = " << bestSellOrders.front().orderId
                                << ", price = " << tradedPrice
                                << ", amount = " << tradedAmount << "\n";

            // update the order amounts
            orderBook.updateBuyOrder(bestBuyPrice, tradedAmount);
            orderBook.updateSellOrder(bestSellPrice, tradedAmount);
        } else {
            break;
        }
    }

    return trades;
}