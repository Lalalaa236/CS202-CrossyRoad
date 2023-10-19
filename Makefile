all:
	g++ -w -o CrossRoad -Iinclude src/*.cpp *.cpp -Llib -lraylib -lopengl32 -lgdi32 -lwinmm && CrossRoad
clean:
	-del *.exe 