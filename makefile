TARGET = -mmacosx-version-min=10.8
LIBS = -F/System/Library/Frameworks -framework OpenGL -framework GLUT -lm

all: a1

a1: a1.c
	clang a1.c -o a1 $(LIBS) $(TARGET)