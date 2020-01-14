
Note: C++11 flag is used to compile this program.

To get the executable, issue "make run" in your shell. 
Then you can you do ./run < input.txt to run the code

AWARE: In the example provided, OrderPartiallyFilled is printed as "4,orderId,side,new_qantity"
So in my code, it does the same thing as example.

We use Boost Unittest framework to test the code. We have  "-lboost_system -lboost_unit_test_framework" in LDFLAGS in Makefile.
"make test" creates test executable.


