#include "order_book.h"
#include "parser.h"

int main()
{
    OrderBook ob;
    std::string line;
    while(std::cin) {
        if(std::getline(std::cin,line)) {
            std::unique_ptr<Order> res = parser(line);
            if (res){
                Order o = *res.get();
                //std::cout << o << std::endl;
                ob.processOrder(o);
                //std::cout << ob << std::endl;
            }
        }
    }
    //std::cout << ob << std::endl;
    return 0;
}
