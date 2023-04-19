LIBS=-lraylib -lopengl32 -lgdi32 -lwinmm

test:
	g++ main.cpp ${LIBS} -o main.exe
	main
	rm main.exe