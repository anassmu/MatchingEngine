# **Matching Engine**

Tether matching engine coding test in C++.

---

## **Features**

- **Order Matching**:
  - Matches buy and sell orders based on price and priority.
  - Uses a fair priority mechanism for processing orders.

- **Order Cancellation**:
  - Supports canceling specific orders by their ID.
  - Logs rejections for invalid cancellation attempts.

- **Multithreaded Design**:
  - Clients and the matching engine run on separate threads.
  - Thread-safe queues ensure synchronization between components.

- **Extensible Framework**:
  - Handles multiple client activities like placing and canceling orders.
  - Easily customizable for additional features.

---

## **Project Structure**

```
MatchingEngine/
├── include/
│   ├── MatchingEngine.h   # Matching engine logic
│   ├── MessageTypes.h     # Data structures
│   ├── OrderBook.h        # Order book management
│   ├── ThreadSafeQueue.h  # Thread-safe queue for multithreaded operations
├── src/
│   ├── MatchingEngine.cpp 
│   ├── OrderBook.cpp  
│   ├── main.cpp           # Main simulation file
├── CMakeLists.txt         # CMake configuration
```

---

## **Getting Started**

### **Dependencies**
- **C++17 or higher** (C++23 recommended)
- **CMake** (minimum version 3.10)
- A modern compiler:
  - GCC, Clang, or MSVC

---

### **Build and Run**

1. **Clone the Repository**

2. **Build the Project**
   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```

3. **Run the Program**


---

## **Simulation**

The program simulates as requested :
1. 2 clients placing and canceling orders.
2. A matching engine processing these requests in real-time.

Example logs:
```
client 1 starting...
client 1 sending order: order ID: 100, price: 50, amount: 10, type: buy
client 1 sending cancel request for order ID: 100
Request rejected: ID = 100, Reason = Order not found: Unable to cancel the order.
After Matching:
Buy Orders:
Price: 50, Amount: 10
Sell Orders:
Price: 60, Amount: 10
```