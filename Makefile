LIBS=-lraylib -lopengl32 -lgdi32 -lwinmm
LIBSMAC = -lraylib -lopengl32 -lgdi32 -lwinmm

test:
	g++ main.cpp ${LIBS} -o main.exe
	main
	rm main.exe
mac:
	g++ main.cpp ${LIBSMAC} -o main.exe
	main.exe
	rm main.exe