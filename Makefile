LIBS=-lraylib -lopengl32 -lgdi32 -lwinmm
LIBSMAC = -L. -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo



test:
	g++ main.cpp ${LIBS} -o main.exe
	main
	rm main.exe
mac:
	g++ main.cpp ${LIBSMAC} -o main.exe -std=c++11 -mcpu=apple-m1 -Wall -Wextra