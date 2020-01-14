#include "order.h"
#include "header.h"

Order::Order(
    unsigned int price, 
    unsigned int qty, 
    unsigned int orderId, 
    unsigned int count,
    bool side
    ): price(price), qty(qty), orderId(orderId), count(count), side(side)
{
    
}

Order::Order(const Order& o)
{
    price = o.price;
    qty = o.qty;
    orderId = o.orderId;
    count = o.count;
    side = o.side;
}

Order& Order::operator=(const Order& rhs)
{
    if(&rhs == this)
        return *this;
    price = rhs.price;
    qty = rhs.qty;
    orderId = rhs.orderId;
    count = rhs.count;
    side = rhs.side;
    return *this;
}

/* In std::set, Elements a and b are considered equal iff !(a < b) && !(b < a). Taking advantage of that here */
bool Order::operator<(const Order& rhs) const
{
    if (orderId == rhs.orderId) {
        return false;
    }
    if (price != rhs.price){
        return price < rhs.price;
    }
    else{
        if (!side){
            return count < rhs.count;
        }else {
            return count > rhs.count;
        }
    }
}

unsigned int Order::updateQty(unsigned int tradeQty)
{
    qty -= tradeQty;
    qty = std::max<unsigned int>(0, qty);
    return qty;
}

unsigned int Order::getPrice() const
{
    return price;
}

unsigned int Order::getQty() const
{
    return qty;
}

unsigned int Order::getOrderId() const
{
    return orderId;
}

unsigned int Order::getCount() const
{
    return count;
}

bool Order::getSide() const
{
    return side;
}

std::ostream& operator<<(std::ostream& os, const Order& o)
{
    if (o.getSide()){
        os << "Buy ";
    } 
    else {
        os << "Sell ";
    }
    os << "Price: " << o.getPrice() << " ";
    os << "Qty: " << o.getQty() << " ";
    os << "OrderId: " << o.getOrderId() << " ";
    os << "count: " << o.getCount() << " ";
    return os;
}