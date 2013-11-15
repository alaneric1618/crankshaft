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
OBJS       = obj/Game.o obj/SceneGraph.o obj/HUD.o obj/Updatable.o obj/Drawable.o obj/Group.o obj/Car.o obj/Frame.o obj/Camera.o obj/Point.o obj/Face.o obj/Vector.o obj/Mesh.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(LFLAGS) $(OBJS) -o $(TARGET)

obj/Game.o: src/Game.cpp src/Game.h src/HUD.h src/Camera.h src/SceneGraph.h src/Mesh.h src/Car.h src/Group.h
	$(CC) $(CFLAGS) -o $@ $<

obj/SceneGraph.o: src/SceneGraph.cpp src/SceneGraph.h src/Updatable.h src/Drawable.h
	$(CC) $(CFLAGS) -o $@ $<

obj/Camera.o: src/Camera.cpp src/Camera.h src/Updatable.h src/Drawable.h
	$(CC) $(CFLAGS) -o $@ $<

obj/HUD.o: src/HUD.cpp src/HUD.h src/Updatable.h src/Drawable.h
	$(CC) $(CFLAGS) -o $@ $<

obj/Point.o: src/Point.cpp src/Point.h
	$(CC) $(CFLAGS) -o $@ $<

obj/Face.o: src/Face.cpp src/Face.h
	$(CC) $(CFLAGS) -o $@ $<

obj/Vector.o: src/Vector.cpp src/Vector.h
	$(CC) $(CFLAGS) -o $@ $<

obj/Frame.o: src/Frame.cpp src/Frame.h
	$(CC) $(CFLAGS) -o $@ $<

obj/Mesh.o: src/Mesh.cpp src/Mesh.h src/Point.h src/Face.h src/Vector.h src/Group.h
	$(CC) $(CFLAGS) -o $@ $<

obj/Group.o: src/Group.cpp src/Group.h src/Frame.h src/Updatable.h src/Drawable.h
	$(CC) $(CFLAGS) -o $@ $<

obj/Car.o: src/Car.cpp src/Car.h src/Group.h
	$(CC) $(CFLAGS) -o $@ $<

obj/Updatable.o: src/Updatable.h
	$(CC) $(CFLAGS) -o $@ $<

obj/Drawable.o: src/Drawable.h
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f obj/*
	rm -f $(TARGET)

