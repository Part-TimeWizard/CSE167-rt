CC = g++
CFLAGS = -g -std=c++11 -Wno-deprecated-register -Wno-deprecated-declarations -DGL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
INCFLAGS = -I./glm-0.9.7.1 -I./include/
LDFLAGS = -framework GLUT -framework OpenGL -L./lib/mac/ -lm  -lfreeimage 

RM = /bin/rm -f
all: RayTracer
RayTracer: main.o Camera.o Light.o Ray.o RayHit.o Scene.o Sphere.o Triangle.o
	$(CC) -o RayTracer main.o Camera.o Light.o Ray.o RayHit.o Scene.o Sphere.o Triangle.o $(LDFLAGS)
ImageLibraryTest: main.o
	$(CC) -o ImageLibraryTest main.o $(LDFLAGS)
main.o: main.cpp
	$(CC) $(CFLAGS) $(INCFLAGS) -c main.cpp 
Camera.o: src/Camera.cpp include/Camera.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Camera.cpp
Light.o: src/Light.cpp include/Light.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Light.cpp
Ray.o: src/Ray.cpp include/Ray.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Ray.cpp
RayHit.o: src/RayHit.cpp include/RayHit.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/RayHit.cpp
Scene.o: src/Scene.cpp include/Scene.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Scene.cpp
Sphere.o: src/Sphere.cpp include/Sphere.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Sphere.cpp
Triangle.o: src/Triangle.cpp include/Triangle.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Triangle.cpp
clean: 
	$(RM) *.o RayTracer ImageLibraryTest
