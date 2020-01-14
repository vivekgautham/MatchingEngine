#include "order_book.h"

OrderBook::OrderBook()
{

}

bool OrderBook::cancel(const Order& o)
{
    buys.erase(o);
    sells.erase(o);
    return true;
}

void OrderBook::addBuy(const Order& o)
{
    buys.insert(o);
}

void OrderBook::addSell(const Order& o)
{
    sells.insert(o);
}

const std::set<Order>& OrderBook::getBuys() const 
{
    return buys;
}

const std::set<Order>& OrderBook::getSells() const
{
    return sells;
}

void OrderBook::executeTrade(Order& o, Order& restingOrder)
{
    unsigned int minQty = std::min(restingOrder.getQty(), o.getQty());
    std::cout << "2," 
                << minQty 
                << "," 
                << restingOrder.getPrice()
                << std::endl;
    unsigned int remCurrent = o.updateQty(minQty);
    if (!remCurrent)
    {
        std::cout << "3," 
                    << o.getOrderId() 
                    << std::endl;
    }
    else 
    {
        std::cout << "4," 
                    << o.getOrderId() 
                    << "," 
                    << (unsigned int)(!o.getSide()) 
                    << "," << o.getQty() 
                    << std::endl;
    }
    unsigned int remResting = restingOrder.updateQty(minQty);
    if (!remResting){
        std::cout << "3," 
                    << restingOrder.getOrderId() 
                    << std::endl;
    }
    else{
        std::cout << "4," 
                    << restingOrder.getOrderId() 
                    << "," << (unsigned int)(!restingOrder.getSide()) 
                    << "," 
                    << restingOrder.getQty() 
                    << std::endl;
        if (restingOrder.getSide()){
            addBuy(restingOrder);
        }
        else{
            addSell(restingOrder);
        }
    }
}

void OrderBook::processBuy(Order& o)
{
    while (!sells.empty() && o.getQty())
    {
        // the lowest-price resting sell for an aggressive buy
        Order sellOrder = *sells.begin();
        if (o.getPrice() >= sellOrder.getPrice())
        {
            // Trade Event Happening, so remove the order from the book and execute trade
            sells.erase(sellOrder);
            executeTrade(o, sellOrder);
        }
        else{
            break;
        }
    }
    if (o.getQty()){
        addBuy(o);
    }
}

void OrderBook::processSell(Order& o)
{
    while (!buys.empty() && o.getQty())
    {
        // the highest-price resting buy for an aggressive sell
        Order buyOrder = *buys.rbegin();
        if (o.getPrice() <= buyOrder.getPrice())
        {
            // Trade Event Happening, so remove the order from the book and execute trade
            buys.erase(buyOrder);
            executeTrade(o, buyOrder);
        }
        else
        {
            break;
        }
    }
    if (o.getQty()){
        addSell(o);
    }
}

void OrderBook::processOrder(Order& o)
{
    if (o.getCount() == 0){
        cancel(o);
    }
    else{
        if (o.getSide())
        {
            processBuy(o);
        }
        else
        {        
            processSell(o);
        }
    }
}

std::ostream& operator<<(std::ostream& os, const OrderBook& ob)
{
    auto buys = ob.getBuys();
    if (!buys.empty()){
	    os << "Following are the buys" << std::endl;
        for (auto it=buys.rbegin(); it != buys.rend(); it++){
            os << *it << std::endl;
        }
    }
    auto sells = ob.getSells();
    if (!sells.empty()){
	    os << "Following are the sells" << std::endl;
        for (auto it=sells.begin(); it != sells.end(); it++){
            os << *it << std::endl;
        }
    }
    return os;
}