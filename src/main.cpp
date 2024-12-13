#include <iostream>
#include <thread>
#include "MatchingEngine.h"
#include "ThreadSafeQueue.h"

void testClient(ThreadSafeQueue<PlaceOrder>& placeQueue, ThreadSafeQueue<int>& cancelQueue, int clientId) {
    
    std::vector<int> placedOrderIds;

    std::cout << "client " << clientId << " starting...\n";

    for (int i = 0; i < 5; ++i) {
        if (i % 2 == 1 && !placedOrderIds.empty()) {
            // cancel the last placed order
            int cancelOrderId = placedOrderIds.back();
            cancelQueue.push(cancelOrderId);
            placedOrderIds.pop_back();
            std::cout << "client " << clientId << " sending cancel request for order ID: " << cancelOrderId << "\n";
        } else {
            // add a new order
            PlaceOrder order = {
                clientId * 100 + i,
                50 + i * 10,
                10,
                i % 2 == 0 ? OrderType::Buy : OrderType::Sell
            };

            std::cout << "client " << clientId << " sending order: "
                      << "order ID: " << order.orderId
                      << ", price: " << order.price
                      << ", amount: " << order.amount
                      << ", type: " << (order.type == OrderType::Buy ? "buy" : "sell") << "\n";

            placeQueue.push(order);
            placedOrderIds.push_back(order.orderId);  // Track the order ID
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    std::cout << "client " << clientId << " finished.\n";
}

int main() {
    
    ThreadSafeQueue<PlaceOrder> placeOrderQueue;
    ThreadSafeQueue<int> cancelOrderQueue;
    MatchingEngine engine;

    std::cout << "starting test\n";

    // threads for the 2 needed clients & matching engine
    std::thread client1(testClient, std::ref(placeOrderQueue), std::ref(cancelOrderQueue), 1);
    std::thread client2(testClient, std::ref(placeOrderQueue), std::ref(cancelOrderQueue), 2);
    std::thread engineThread(&MatchingEngine::handleIncomingOrders, &engine, std::ref(placeOrderQueue), std::ref(cancelOrderQueue));

    // wait for clients
    client1.join();
    client2.join();


    // process rejections
    while (!cancelOrderQueue.empty()) {
        int cancelOrderId;
        if (cancelOrderQueue.pop(cancelOrderId)) {
            auto rejection = engine.handleCancelOrder(cancelOrderId);
            if (rejection) {
                std::cout << "request rejected: ID = " << rejection->requestId
                          << ", reason = " << rejection->reason << "\n";
            }
        }
    }

    // send a stop signal -1
    placeOrderQueue.push({-1, 0, 0, OrderType::Buy});
    engine.stopProcessing();
    engineThread.join();

    // order book after trading
    std::cout << "After Matching:" << std::endl;
    engine.getOrderBook().printOrderBook();

    return 0;
}