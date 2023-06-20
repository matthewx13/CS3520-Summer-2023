CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -pthread
TARGET = fibonacci

all: $(TARGET)

$(TARGET): fibonacci
	$(CXX) $(CXXFLAGS) -o $(TARGET) fibonacci_threads.o

fibonacci_threads.o: fibonacci_threads.cpp
	$(CXX) $(CXXFLAGS) -c fibonacci_threads.cpp

clean:
	rm -f $(TARGET) *.o
