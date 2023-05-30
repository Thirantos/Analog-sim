LIBS=-lraylib -lopengl32 -lgdi32 -lwinmm -LC:\raylib\raylib\src
LIBSMAC = -L. -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo



build:
	g++ main.cpp ${LIBS} -o main.exe -g -w
mac:
	g++ main.cpp ${LIBSMAC} -o main.exe -std=c++11 -mcpu=apple-m1 -Wall -Wextra -g