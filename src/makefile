.DEFAULT_GOAL := test

ifeq ($(shell uname), Compiler)                                           # Apple
    CXX          := g++
    INCLUDE      := /usr/local/include
    CXXFLAGS     := -pedantic -std=c++14 -I$(INCLUDE) -Wall -Weffc++
    LIBB         := /usr/local/lib
    LIBG         := /usr/local/lib
    LDFLAGS      := -lboost_serialization -lgtest_main
    CLANG-CHECK  := clang-check
    GCOV         := gcov
    GCOVFLAGS    := -fprofile-arcs -ftest-coverage
    VALGRIND     := valgrind
    DOXYGEN      := doxygen
    CLANG-FORMAT := clang-format
else ifeq ($(CI), true)                                                 # Travis CI
    CXX          := g++-5
    INCLUDE      := /usr/include
    CXXFLAGS     := -pedantic -std=c++14 -Wall -Weffc++
    LIBB         := /usr/lib
    LIBG         := $(PWD)/gtest
    LDFLAGS      := -lboost_serialization -lgtest -lgtest_main -pthread
    CLANG-CHECK  := clang-check
    GCOV         := gcov-5
    GCOVFLAGS    := -fprofile-arcs -ftest-coverage
    VALGRIND     := valgrind
    DOXYGEN      := doxygen
    CLANG-FORMAT := clang-format
else ifeq ($(shell uname -p), unknown)                                  # Docker
    CXX          := g++
    INCLUDE      := /usr/include
    CXXFLAGS     := -pedantic -std=c++14 -Wall -Weffc++
    LIBB         := /usr/lib
    LIBG         := /usr/lib
    LDFLAGS      := -lboost_serialization -lgtest -lgtest_main -pthread
    CLANG-CHECK  := clang-check
    GCOV         := gcov
    GCOVFLAGS    := -fprofile-arcs -ftest-coverage
    VALGRIND     := valgrind
    DOXYGEN      := doxygen
    CLANG-FORMAT := clang-format-3.5
else                                                                    # UTCS
    CXX          := g++
    INCLUDE      := /usr/include
    CXXFLAGS     := -pedantic -std=c++14 -Wall -Weffc++
    LIBB         := /usr/lib/x86_64-linux-gnu
    LIBG         := /usr/local/lib
    LDFLAGS      := -lboost_serialization -lgtest -lgtest_main -pthread
    CLANG-CHECK  := clang-check
    GCOV         := gcov
    GCOVFLAGS    := -fprofile-arcs -ftest-coverage
    VALGRIND     := valgrind
    DOXYGEN      := doxygen
    CLANG-FORMAT := clang-format-3.8
endif


clean:
	rm -f  *.bin
	rm -f  *.db
	rm -f  *.tmp
	rm -f  ../build/*.tmp
	rm -f  *.gcda
	rm -f  *.gcno
	rm -f  *.gcov
	rm -f  *.plist
	rm -f  ../build/Compiler
	rm -f  ../build/TestCompiler
	rm -f  ../build/compiler.in.c
    

.PHONY: Compiler.tmp
Compiler.tmp: Compiler
	../build/./Compiler ../build/compiler.in > ../build/Compiler.tmp
	diff ../build/Compiler.tmp ../build/Compiler.out

Compiler:
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) Visitor.c++ Compiler.c++ -o ../build/Compiler
	-$(CLANG-CHECK) -extra-arg=-std=c++11          Compiler.c++     --
	-$(CLANG-CHECK) -extra-arg=-std=c++11          Visitor.c++      --

TestCompiler:
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) TestCompiler.c++ Visitor.c++ Compiler.c++ -o ../build/TestCompiler $(LDFLAGS)
	-$(CLANG-CHECK) -extra-arg=-std=c++11          TestCompiler.c++ --

.PHONY: TestCompiler.tmp
TestCompiler.tmp: TestCompiler
	$(VALGRIND) ../build/./TestCompiler                                       >  ../build/TestCompiler.tmp 2>&1
	-$(GCOV) -b Compiler.c++ | grep -A 5 "File 'Compiler.c++'"     >> ../build/TestCompiler.tmp
	-$(GCOV) -b Visitor.c++ | grep -A 5 "File 'Visitor.c++'"     >> ../build/TestCompiler.tmp
	-$(GCOV) -b TestCompiler.c++ | grep -A 5 "File 'TestCompiler.c++'" >> ../build/TestCompiler.tmp
	cat ../build/TestCompiler.tmp

config:
	git config -l

format:
	$(CLANG-FORMAT) -i ../include/Compiler.h
	$(CLANG-FORMAT) -i ../include/Node.h
	$(CLANG-FORMAT) -i ../include/Token.h
	$(CLANG-FORMAT) -i ../include/Visitor.h
	$(CLANG-FORMAT) -i TestCompiler.c++
	$(CLANG-FORMAT) -i Compiler.c++
	$(CLANG-FORMAT) -i Visitor.c++

scrub:
	make clean
	rm -f  Doxyfile
	rm -rf html

status:
	make clean
	@echo
	git branch
	git remote -v
	git status

test: Compiler.tmp TestCompiler.tmp

