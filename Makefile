# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -Wall -std=c++11
# Add -O for optimization and remove -g when you are ready to submit
# CXXFLAGS = -Wall -O -std=c++11

# Linker Flags
LDFLAGS = -pthread

# Object Files
OBJ = main.o producer.o consumer.o tands.o

# Executable Name
EXE = prodcon

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cpp common.h tands.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ) $(EXE)
