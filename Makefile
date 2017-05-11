CXX= g++
CXXFLAGS= -Wall -Werror -Wextra -pedantic -std=c++14
LDLIBS= -lsfml-graphics -lsfml-window -lsfml-system
SRC= $(addprefix src/, content-manager.o main.o character.o player.o \
                       game-manager.o map.o animate.o cop.o collision.o \
                       manager.o menu-manager.o end-manager.o pause-manager.o\
                       vision-ray.o switch-manager.o hud.o drone.o bad-end.o)

all: $(SRC)
	$(CXX) $(CXXFLAGS) -o CoG $^ $(LDLIBS)

clean:
	rm -f CoG $(SRC)
