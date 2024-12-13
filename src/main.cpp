#include <iostream>
#include <thread>
#include "MatchingEngine.h"
#include "ThreadSafeQueue.h"

void testClient(ThreadSafeQueue<PlaceOrder>& queue, int clientId) {
    std::cout << "client " << clientId << " starting...\n";

    for (int i = 0; i < 5; ++i) {
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

        queue.push(order);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    std::cout << "client " << clientId << " finished.\n";
}

int main() {
    
    ThreadSafeQueue<PlaceOrder> orderQueue;
    MatchingEngine engine;

    std::cout << "starting test\n";

    // threads for the 2 needed clients & matching engine
    std::thread client1(testClient, std::ref(orderQueue), 1);
    std::thread client2(testClient, std::ref(orderQueue), 2);
    std::thread engineThread(&MatchingEngine::handleIncomingOrders, &engine, std::ref(orderQueue));

    // wait for clients
    client1.join();
    client2.join();

    // stop
    engine.stopProcessing();
    engineThread.join();

    // order book after trading
    std::cout << "After Matching:" << std::endl;
    engine.getOrderBook().printOrderBook();

    return 0;
}