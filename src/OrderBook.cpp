#include "OrderBook.h"
#include <iostream>

void OrderBook::addOrder(const PlaceOrder& order) {
    if (order.price <= 0 || order.amount <= 0) {
        std::cerr << "Invalid order: Price and amount must bepositive." << std::endl;
        return;
    }

    if (order.type == OrderType::Buy) {
        buyOrders[order.price].push_back(order);
    } else if (order.type == OrderType::Sell) {
        sellOrders[order.price].push_back(order);
    }
}

void OrderBook::cancelOrder(int orderId) {
    for (auto& [price, orders] : buyOrders) {
        orders.erase(
            std::remove_if(orders.begin(), orders.end(),
                [orderId](const PlaceOrder& order) { return order.orderId == orderId; }),
            orders.end());
    }

    for (auto& [price, orders] : sellOrders) {
        orders.erase(
            std::remove_if(orders.begin(), orders.end(),
                [orderId](const PlaceOrder& order) { return order.orderId == orderId; }),
            orders.end());
    }
}

void OrderBook::printOrderBook() const {
    std::cout << "Buy Orders:" << std::endl;
    for (const auto& [price, orders] : buyOrders) {
        for (const auto& order : orders) {
            std::cout << "Price: " << price << ", Amount: " << order.amount << std::endl;
        }
    }

    std::cout << "Sell Orders:" << std::endl;
    for (const auto& [price, orders] : sellOrders) {
        for (const auto& order : orders) {
            std::cout << "Price: " << price << ", Amount: " << order.amount << std::endl;
        }
    }
}

std::vector<PlaceOrder>& OrderBook::getBestBuyOrder() {
    return buyOrders.begin()->second;
}

std::vector<PlaceOrder>& OrderBook::getBestSellOrder() {
    return sellOrders.begin()->second;
}

void OrderBook::removeFullyMatchedBuyOrder() {
    auto it = buyOrders.begin();
    it->second.erase(it->second.begin());
    if (it->second.empty()) {
        buyOrders.erase(it);
    }
}

void OrderBook::removeFullyMatchedSellOrder() {
    auto it = sellOrders.begin();
    it->second.erase(it->second.begin());
    if (it->second.empty()) {
        sellOrders.erase(it);
    }
}