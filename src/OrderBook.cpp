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
    // buyOrders
    for (auto it = buyOrders.begin(); it != buyOrders.end();) {
        auto& orders = it->second;
        orders.erase(
            std::remove_if(orders.begin(), orders.end(),
                [orderId](const PlaceOrder& order) { return order.orderId == orderId; }),
            orders.end());

        // If no orders remove the price
        if (orders.empty()) {
            it = buyOrders.erase(it);
        } else {
            ++it;
        }
    }

    // sellOrders
    for (auto it = sellOrders.begin(); it != sellOrders.end();) {
        auto& orders = it->second;
        orders.erase(
            std::remove_if(orders.begin(), orders.end(),
                [orderId](const PlaceOrder& order) { return order.orderId == orderId; }),
            orders.end());

        // If no orders remove the price
        if (orders.empty()) {
            it = sellOrders.erase(it);
        } else {
            ++it;
        }
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

void OrderBook::updateBuyOrder(int price, int amount) {
    auto it = buyOrders.find(price);
    if (it != buyOrders.end() && !it->second.empty()) {
        it->second.front().amount -= amount;
        if (it->second.front().amount <= 0) {
            // remove the fully matched order and price if no order remain
            it->second.erase(it->second.begin());  
            if (it->second.empty()) {
                buyOrders.erase(it);
            }
        }
    }
}

void OrderBook::updateSellOrder(int price, int amount) {
    auto it = sellOrders.find(price);
    if (it != sellOrders.end() && !it->second.empty()) {
        it->second.front().amount -= amount;
        if (it->second.front().amount <= 0) {
            it->second.erase(it->second.begin());
            if (it->second.empty()) {
                sellOrders.erase(it);
            }
        }
    }
}