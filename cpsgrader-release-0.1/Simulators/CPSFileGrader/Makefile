PROG     = CPSFileGrader
CXX     = g++
CFLAGS  =  -std=c++11  

# Paths for include and the cpsgrader library
CPSGRADER_PATH = ../..
LIBPATH = $(CPSGRADER_PATH)/STLDriver/lib
INCLUDE = -I$(CPSGRADER_PATH)/STLDriver/include/ -I./
CPSGRADER_LIB     =  $(LIBPATH)/libcpsgrader.a

PROG_SRC = $(PROG).cpp
# add additional source files here if needed
SRCS = 

CSRCS   = $(filter %.c, $(SRCS))
CPPSRCS = $(filter %.cpp, $(SRCS))
OBJS    = $(patsubst %.cpp,%.o,$(CPPSRCS)) $(patsubst %.c,%.o,$(CSRCS))

all: $(PROG) 

#test: $(PROG) ../examples/test.stl
#	./$(PROG) ../examples/test.stl

.cpp.o :
	$(CXX) -c $(CFLAGS) $(INCLUDE) -o $@ $<

$(PROG) : $(PROG_SRC) $(OBJS)
	$(CXX) -o $@ $(PROG_SRC) $(CFLAGS) $(OBJS)  $(INCLUDE) $(CPSGRADER_LIB)

clean :
	rm -f  $(PROG) $(OBJS) 
