#OBJS specifies which files to compile as part of the project
OBJS = game_01.cpp

#CC specifies which compiler we're using
CC = g++
# CC = gcc

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_ttf 

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = game_01

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) -g $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
