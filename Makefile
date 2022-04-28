OBJS = main.cpp init.cpp entity.cpp window.cpp sounds.cpp level.cpp rect.cpp LTimer.cpp
OBJ_NAME = cubee
CC = g++
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer
all : $(OBJS)
	$(CC) --no-warnings $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)
