CXX     = g++
AR      = ar
PROG     = CPSGrader
PROG_SRC = $(PROG).cpp
LIB     = libcpsgrader.a 
LEX     = /usr/bin/flex
YACC    = /opt/local/bin/bison 
INCLUDE = -I../include/ -I./ -I../
SRCS    = stl_parser.cpp \
          stl_scanner.cpp \
          stl_driver.cpp \
          tools.cpp \
          stl_atom.cpp \
          transducer.cpp \
          interval_transducer.cpp \
          interval.cpp \
          robustness.cpp \
          signal.cpp \
          signal_expr.cpp \

          
CFLAGS  = -std=c++11 -O3 #-DYYDEBUG=1  
LIBPATH = ../lib

CSRCS   = $(filter %.c, $(SRCS))
CPPSRCS = $(filter %.cpp, $(SRCS))
OBJS    = $(patsubst %.cpp,%.o,$(CPPSRCS)) $(patsubst %.c,%.o,$(CSRCS))

all: $(PROG) $(LIB)

parser: stl_scanner.cpp stl_parser.cpp
	mv *.h* ../include >& /dev/null

test: $(PROG) ../examples/test_plan_regression.stl
	cd ..; ./bin/$(PROG) examples/test_plan_regression.stl

.cpp.o :
	$(CXX) -c $(CFLAGS) $(INCLUDE) -o $@ $<

stl_scanner.cpp: stl_scanner.lpp
	$(LEX) -o stl_scanner.cpp stl_scanner.lpp

stl_parser.cpp: stl_parser.ypp 
	$(YACC) -o stl_parser.cpp --defines=stl_parser.h stl_parser.ypp

$(PROG) : $(PROG_SRC) $(LIB)
	$(CXX) $(CFLAGS) $(PROG_SRC) $(LIB) -o $@ $(INCLUDE) -lm; cp -f $@ ../bin/ 

$(LIB): $(OBJS)
	$(AR) rcs $(LIB) $(OBJS)
	cp $(LIB) $(LIBPATH)/$(LIB) 

clean :
	rm -f stl_parser.cpp stl_scanner.cpp *.o ../bin/$(PROG) $(PROG) ../include/stl_parser.h

