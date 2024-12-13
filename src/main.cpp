#include <iostream>
#include "OrderBook.h"

int main() {

    OrderBook orderBook;

    // test
    PlaceOrder order1 = {1, 100, 10, OrderType::Buy};
    PlaceOrder order2 = {2, 101, 5, OrderType::Sell};
    PlaceOrder order3 = {3, 100, 20, OrderType::Buy};

    orderBook.addOrder(order1);
    orderBook.addOrder(order2);
    orderBook.addOrder(order3);

    orderBook.printOrderBook();

    return 0;
}