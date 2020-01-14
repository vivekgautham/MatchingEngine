
# Warnings frequently signal eventual errors:
CXXFLAGS= -g -std=gnu++11 -W -Wall -Weffc++ -Wextra -fsanitize=address -fsanitize-address-use-after-scope -pedantic -O0

# Linker flags for both OS X and Linux
LDFLAGS= -lboost_system -lboost_unit_test_framework

# Generates list of object files from all the
#   source files in directory
OBJS = $(addsuffix .o, $(basename $(shell find ./src -name "*cpp")))
DEPS = $(OBJS:.o=.d)

TESTOBJS = $(addsuffix .o, $(basename $(shell find ./unittests -name "*cpp")))
TESTDEPS = $(TESTOBJS:.o=.d)

# Set executable name
EXEC = run
TESTEXEC = test

all: run test

exec: run

tst: test

# Declare the phony targets
.PHONY: echo clean r t clang gcc setclang setgcc vg

# Phony targets to run dependencies in order
gcc: | setgcc $(EXEC)
clang: | setclang $(EXEC)

# For use with the clang static analyzer by
#  using the environment variable for CXX
sb: | $(clean) $(EXEC)

vg: $(EXEC)
	valgrind ./$(EXEC)

# Run the executable
r:
	./$(EXEC)

# Run the test
t:
	./$(TESTEXEC)

clean:
	rm -rf $(OBJS)
	rm -rf $(DEPS)
	rm -rf $(TESTOBJS)
	rm -rf $(TESTDEPS)
	rm -rf $(EXEC)
	rm -rf $(TESTEXEC)
	rm -rf ./unittests/*.d.*

# Phony target to use clang for compile and linking
setclang:
	@echo "Setting clang"
	$(eval CXX = clang)
	$(eval CXX_LINK = clang)

# Phony target to use g++ for compile and linking
setgcc:
	@echo "Setting g++"
	$(eval CXX = g++)
	$(eval CXX_LINK = g++)


$(TESTOBJS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TESTDEPS): %.d: %.cpp
	@echo "Generating "$@
	@set -e; rm -f $@; \
      g++ -MM $(CPPFLAGS) $< > $@.$$$$; \
      sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
      rm -f $@.$$$$


# $@ refers to the target
$(TESTEXEC): $(TESTOBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(TESTOBJS) $(LDFLAGS)

include $(TESTDEPS)



# $< refers to the first dependency
# Uses static pattern rule to keep from compiling all
#   objects every time.
$(OBJS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DEPS): %.d: %.cpp
	@echo "Generating "$@
	@set -e; rm -f $@; \
      g++ -MM $(CPPFLAGS) $< > $@.$$$$; \
      sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
      rm -f $@.$$$$


# $@ refers to the target
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

include $(DEPS)

