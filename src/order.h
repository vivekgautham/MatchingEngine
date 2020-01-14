#ifndef ORDER_H
#define ORDER_H

#include "header.h"

class Order
{
    private:
        unsigned int price;
        unsigned int qty;
        unsigned int orderId;
        unsigned int count;
        bool side;

    public:
        Order() = delete; 
        Order(unsigned int, unsigned int, unsigned int, unsigned int, bool);
        Order& operator=(const Order&);
        Order(const Order&);
        bool operator<(const Order&) const;
        unsigned int updateQty(unsigned int);
        friend std::ostream& operator<<(std::ostream&, const Order&);
        unsigned int getPrice() const;
        unsigned int getQty() const;
        unsigned int getOrderId() const;
        unsigned int getCount() const;
        bool getSide() const;
};

#endif