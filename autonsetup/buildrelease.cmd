g++ -c src/*.cpp -std=c++2a -DDEBUG_MACROS -O3 -pthread -g -w -m64 -I include -I C:/SDL2/include 
g++ *.o -o bin/debug/main -L C:/SDL2/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf 
start bin/debug/main