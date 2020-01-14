#include "../src/order_book.h"
#include "../src/order_book.cpp"
#include "../src/order.h"
#include "../src/order.cpp"
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ORDER_BOOK)

BOOST_AUTO_TEST_CASE(CANCEL)
{

    OrderBook ob;
    
    BOOST_CHECK(ob.getBuys().empty());

    ob.addBuy(Order(1025, 4, 123, 1, true));
    BOOST_CHECK_EQUAL(ob.getBuys().size(), (unsigned long)1);

    
    ob.cancel(Order(0, 0, 123, 0, true));
    BOOST_CHECK_EQUAL(ob.getBuys().size(), (unsigned long)0);
    BOOST_CHECK(ob.getBuys().empty());
    
}


BOOST_AUTO_TEST_CASE(PROCESS)
{

    OrderBook ob;
    
    BOOST_CHECK(ob.getBuys().empty());
    BOOST_CHECK(ob.getSells().empty());
    /*
    Order buy = Order(1025, 4, 123, 1, true);
    ob.processOrder(buy);
    BOOST_CHECK_EQUAL(ob.getBuys().size(), (unsigned long)1);

    Order sell = Order(1024, 4, 124, 2, false);
    ob.processOrder(sell);
    BOOST_CHECK_EQUAL(ob.getBuys().size(), (unsigned long)0);
    BOOST_CHECK_EQUAL(ob.getSells().size(), (unsigned long)0);
    */
    
    Order sell1(1075, 1, 100000, 3, false);
    Order buy1(1000, 9, 100001, 4, true);
    Order buy2(975, 30, 100002, 5, true);
    Order sell2(1050, 10, 100003, 6, false);
    Order buy3(950, 10, 100004, 7, true);
    ob.processOrder(sell1);
    BOOST_CHECK_EQUAL(ob.getSells().size(), (unsigned long)1);
    ob.processOrder(buy1);
    BOOST_CHECK_EQUAL(ob.getBuys().size(), (unsigned long)1);
    BOOST_CHECK_EQUAL(ob.getSells().size(), (unsigned long)1);
    ob.processOrder(buy2);
    ob.processOrder(sell2);
    ob.processOrder(buy3);
    BOOST_CHECK_EQUAL(ob.getBuys().size(), (unsigned long)3);
    BOOST_CHECK_EQUAL(ob.getSells().size(), (unsigned long)2);
    Order sell3(1025, 2, 100005, 8, false);
    ob.processOrder(sell3);
    BOOST_CHECK_EQUAL(ob.getSells().size(), (unsigned long)3);
    Order buy4(1000, 1, 100006, 9, true);
    ob.processOrder(buy4);
    BOOST_CHECK_EQUAL(ob.getBuys().size(), (unsigned long)4);
    Order cancel1(0, 0, 100004, 0, false);
    ob.processOrder(cancel1);
    BOOST_CHECK_EQUAL(ob.getBuys().size(), (unsigned long)3);

    Order sell4(1025, 5, 100007, 10, false);
    ob.processOrder(sell4);
    BOOST_CHECK_EQUAL(ob.getSells().size(), (unsigned long)4);
    
    Order buy5(1050, 3, 100008, 11, true);
    ob.processOrder(buy5);
}

BOOST_AUTO_TEST_SUITE_END()