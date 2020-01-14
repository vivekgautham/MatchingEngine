#include "../src/order.h"
#include "../src/parser.h"
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(PARSER)

BOOST_AUTO_TEST_CASE(PARSE)
{
    
    auto result1 = parser("0,123,0,9,1000");
    BOOST_CHECK_EQUAL(result1->getCount(), (unsigned long)0);
    BOOST_CHECK_EQUAL(result1->getOrderId(), (unsigned long)123);
    BOOST_CHECK_EQUAL(result1->getPrice(), (unsigned long)1000);
    BOOST_CHECK_EQUAL(result1->getQty(), (unsigned long)9);

    auto result2 = parser("0,124,0,90,1000");
    BOOST_CHECK_EQUAL(result2->getCount(), (unsigned long)1);
    BOOST_CHECK_EQUAL(result2->getOrderId(), (unsigned long)124);
    BOOST_CHECK_EQUAL(result2->getPrice(), (unsigned long)1000);
    BOOST_CHECK_EQUAL(result2->getQty(), (unsigned long)90);

    auto result3 = parser("1,123");
    BOOST_CHECK_EQUAL(result3->getCount(), (unsigned long)0);
    BOOST_CHECK_EQUAL(result3->getOrderId(), (unsigned long)123);
    BOOST_CHECK_EQUAL(result3->getPrice(), (unsigned long)0);
    BOOST_CHECK_EQUAL(result3->getQty(), (unsigned long)0);
    

    auto result4 = parser("BAD_MESSAGE");
    BOOST_CHECK(result4.get() == nullptr);

}

BOOST_AUTO_TEST_SUITE_END()