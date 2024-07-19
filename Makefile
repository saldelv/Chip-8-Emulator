all:
	g++ -I src/include -L src/lib -o main src/main.cpp src/Chip8.cpp src/Graphics.cpp -lmingw32 -lSDL2main -lSDL2