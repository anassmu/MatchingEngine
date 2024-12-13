#ifndef MESSAGE_TYPES_H
#define MESSAGE_TYPES_H

enum class OrderType {
    Buy,
    Sell
};

struct PlaceOrder {
    int orderId;
    int price;
    int amount;
    OrderType type;  // Buy or Sell
};

struct CancelOrder {
    int orderId;
};

struct OrderPlaced {
    int orderId;
    int price;
    int amount;
};

struct OrderCanceled {
    int orderId;
    int reasonCode; // Optional
};

struct OrderTraded {
    int orderId;
    int tradedPrice;
    int tradedAmount;
};

#endif // MESSAGE_TYPES_H