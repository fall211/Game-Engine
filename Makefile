CXX = g++
CXXFLAGS = -Isrc -std=c++17 -I/opt/homebrew/Cellar/sfml/2.6.1/include
LDFLAGS = -L/opt/homebrew/opt/sfml/lib
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = bin/game

$(TARGET): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

clean:
	rm -fr $(OBJ) $(TARGET)