all:
	g++ -I src/include -L src/lib -o Chip_8_Emulator src/Main.cpp src/Chip8.cpp src/Graphics.cpp src/Input.cpp src/Sound.cpp -lmingw32 -lSDL2main -lSDL2