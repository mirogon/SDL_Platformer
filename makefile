BIN=build/SDL_Platformer
CXX=g++
CXXFLAGS=-std=c++11
LIB=-lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lstdc++fs
OBJ=build/main.o build/Base.o build/Game.o build/Button.o build/GameObject.o build/Map_GameObject.o build/Object.o build/Player.o build/Texture.o

all: $(OBJ)
	$(CXX) -o $(BIN) $(OBJ) $(LIB)

build/%.o: src/%.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS) 

.PHONY: clean

clean:
	rm build/*.o $(BIN)
