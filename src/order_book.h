#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include "header.h"
#include "order.h"

class OrderBook
{
    private:
        std::set<Order> buys;
        std::set<Order> sells;
        
    public:
        OrderBook();
        void addBuy(const Order&);
        void addSell(const Order&);
        bool cancel(const Order&);
        void processBuy(Order&);
        void processSell(Order&);
        void processOrder(Order&);
        void executeTrade(Order&, Order&);
        const std::set<Order>& getBuys() const;
        const std::set<Order>& getSells() const;
        friend std::ostream& operator<<(std::ostream& os, const OrderBook& ob);
};



#endif