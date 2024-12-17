#include "OrderBook.h"
#include <iostream>

void OrderBook::addOrder(const PlaceOrder& order) {
    int price = order.price;

    if (order.amount > 0) {
        auto it = buyOrders.try_emplace(price).first;
        it->second.push_back(order);
        orderLookup[order.orderId] = {it, it->second.size() - 1};
    } else {
        auto it = sellOrders.try_emplace(price).first;
        it->second.push_back(order);
        orderLookup[order.orderId] = {it, it->second.size() - 1};
    }
}


bool OrderBook::cancelOrder(int orderId) {

    auto it = orderLookup.find(orderId);

    if (it == orderLookup.end()) {
        return false; 
    }

    auto& [mapIt, index] = it->second;
    auto& orders = mapIt->second;

    // Remove the order by swapping with the last element
    if (index < orders.size()) {
        orders[index] = orders.back();
        orders.pop_back();
    }

    // Clean up empty price levels
    if (orders.empty()) {
        if (mapIt->first > 0) { 
            buyOrders.erase(mapIt);
        } else {
            sellOrders.erase(mapIt);
        }
    }

    orderLookup.erase(it);
    return true;
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