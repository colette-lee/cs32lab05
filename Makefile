CXX=clang++

CXXFLAGS = -std=c++11 -Wall -Wextra -Werror
#CXXFLAGS = -std=c++11 -Wall -Wextra -Wno-unused-parameter -Wno-unused-private-field

BINARIES=WordCount lab05Test

all: ${BINARIES}

test: lab05Test.o WordCount.o tddFuncs.o
	${CXX} $^ -o $@


clean:
	/bin/rm -f ${BINARIES} *.o
