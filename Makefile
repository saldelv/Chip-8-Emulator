all:
	g++ -I src/include -L src/lib -o main src/Main.cpp src/Chip8.cpp src/Graphics.cpp src/Input.cpp src/Sound.cpp -lmingw32 -lSDL2main -lSDL2