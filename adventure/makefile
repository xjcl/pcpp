#parts of this file have been copied from https://github.com/Twinklebear/TwinklebearDev-Lessons

CXX = g++
# Update these paths to match your installation
# You may also need to update the linker option rpath, which sets where to look for
# the SDL2 libraries at runtime to match your install
SDL_LIB = -L/usr/local/lib -lSDL2 -lSDL2_image -Wl,-rpath=/usr/local/lib
SDL_INCLUDE = -I/usr/local/include
# You may need to change -std=c++11 to -std=c++0x if your compiler is a bit older
CXXFLAGS = -Wall -c -std=c++0x $(SDL_INCLUDE)
LDFLAGS = $(SDL_LIB)
EXE = run


all: $(EXE)

$(EXE): main.o
	$(CXX) chart.cpp $< $(LDFLAGS) -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) chart.cpp -o chart.o
	$(CXX) $(CXXFLAGS) $< -o $@
	


clean:
	rm *.o && rm $(EXE)

