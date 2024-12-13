#include "MatchingEngine.h"
#include <iostream>

OrderPlaced MatchingEngine::handlePlaceOrder(const PlaceOrder& order) {
    orderBook.addOrder(order);
    return {order.orderId, order.price, order.amount};
}

OrderCanceled MatchingEngine::handleCancelOrder(int orderId) {
    orderBook.cancelOrder(orderId);
    // 0 for now
    return {orderId, 0};
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

            // update the order amounts
            orderBook.updateBuyOrder(bestBuyPrice, tradedAmount);
            orderBook.updateSellOrder(bestSellPrice, tradedAmount);
        } else {
            break;
        }
    }

    return trades;
}