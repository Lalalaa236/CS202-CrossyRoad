all:
	g++ -w -o CrossRoad -Iinclude src/*.cpp -Llib -lraylib -lopengl32 -lgdi32 -lwinmm
clean:
	-del *.exe 