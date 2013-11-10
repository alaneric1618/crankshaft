# makefile for phototube
# Author: Eric Alan Bischoff
# Platform: Mac OS X 10.8.5

TARGET     = barrel-bump
CC         = g++
LD         = g++
DEBUG      = -g
LIBPATH    = -L"/System/Library/Frameworks/OpenGL.framework/Libraries"
LIBRARIES  = -lGL -lGLU -lm -ltcl
FRAMEWORKS = -framework GLUT -framework OpenGL
CFLAGS     = -Wall -Wno-deprecated -c -frounding-math
LFLAGS     = -Wall $(FRAMEWORKS) $(LIBPATH) $(LIBRARIES)
OBJS       = obj/Game.o obj/SceneGraph.o obj/HUD.o obj/GameState.o obj/GameTimer.o obj/Updatable.o obj/Drawable.o obj/Group.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(LFLAGS) $(OBJS) -o $(TARGET)

obj/Game.o: src/Game.cpp
	$(CC) $(CFLAGS) -o $@ $<

obj/SceneGraph.o: src/SceneGraph.cpp
	$(CC) $(CFLAGS) -o $@ $<

obj/HUD.o: src/HUD.cpp
	$(CC) $(CFLAGS) -o $@ $<

obj/GameState.o: src/GameState.cpp
	$(CC) $(CFLAGS) -o $@ $<

obj/GameTimer.o: src/GameTimer.cpp
	$(CC) $(CFLAGS) -o $@ $<

obj/Group.o: src/Group.cpp
	$(CC) $(CFLAGS) -o $@ $<

obj/Updatable.o: src/Updatable.h
	$(CC) $(CFLAGS) -o $@ $<

obj/Drawable.o: src/Drawable.h
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f obj/*
	rm -f $(TARGET)

