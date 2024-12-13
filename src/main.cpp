#include <iostream>
#include "MatchingEngine.h"

int main() {

    MatchingEngine engine;

    // Simulate / no threading till now

    // 1st  buyer wants to buy 15 assets at a price of 60
    PlaceOrder buyOrder = {1, 60, 15, OrderType::Buy};
    engine.handlePlaceOrder(buyOrder);
    // 1st seller wants to sell 10 assets at a price of 50
    PlaceOrder sellOrder1 = {2, 50, 10, OrderType::Sell};
    engine.handlePlaceOrder(sellOrder1);

    // 2nd seller wants to sell 10 assets at a price of 55
    PlaceOrder sellOrder2 = {3, 55, 10, OrderType::Sell};
    engine.handlePlaceOrder(sellOrder2);

    std::cout << "Before Matching:" << std::endl;
    engine.getOrderBook().printOrderBook();

    // match
    std::vector<OrderTraded> trades = engine.processMatching();

    // resulting trades
    std::cout << "Trades executed:" << std::endl;
    for (const auto& trade : trades) {
        std::cout << "Order ID: " << trade.orderId
                  << ", Traded Price: " << trade.tradedPrice
                  << ", Traded Amount: " << trade.tradedAmount << std::endl;
    }

    // order book after trading
    std::cout << "After Matching:" << std::endl;
    engine.getOrderBook().printOrderBook();

    return 0;
}