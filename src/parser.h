#ifndef PARSER_H
#define PARSER_H

#include "header.h"
#include "order.h"

void tokenize(std::vector<unsigned int>& elems, std::string str)
{
    std::stringstream ss(str);
    unsigned int i;
    while (ss >> i)
    {
        elems.push_back(i);
        if (ss.peek() == ',')
        {
            ss.ignore();
        }
    }
}

template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args )
{
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

class Counter
{
    private:
        Counter(){};
        Counter(Counter const& rhs);
        Counter& operator=(Counter const& rhs);
        unsigned int count = 1;
    public:
        static Counter& getInstance()
        {
            static Counter instance;
            return instance;
        }
        unsigned int operator()(void){
            return count++;
        }
};

std::unique_ptr<Order> parser(std::string str)
{
    std::vector<unsigned int> msg;
    try{
        tokenize(msg, str);
        if (msg.size() == 5 && msg[0] == 0){
            return make_unique<Order>(msg[4], msg[3], msg[1], Counter::getInstance()(), !bool(msg[2]));
        }
        else if (msg.size() == 2 && msg[0] == 1){
            return make_unique<Order>(0, 0, msg[1], 0, false);
        }
        else{
            throw std::runtime_error("BAD MESSAGE");
        }
    } catch (...){
        std::cerr << "Unknown message type: " << str << std::endl;
        return std::unique_ptr<Order>();
    }
}

#endif