#ifndef MESSAGE_TYPES_H
#define MESSAGE_TYPES_H

struct PlaceOrder {
    int orderId;
    int price;
    int amount;
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