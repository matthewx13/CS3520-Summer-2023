CXX = g++
CXXFLAGS = -std=c++11
LDLIBS = -lncurses

SRC = world.cpp organism.cpp ant.cpp queen_ant.cpp male_female_ant.cpp doodlebug.cpp main.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = simulation

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

run: $(EXEC)
	TERM=xterm-256color ./$(EXEC)
