CFLAGS := -I/opt/X11/include $(shell pkg-config --cflags jansson X11)
LDLIBS := -lforms -lflimage $(shell pkg-config --libs jansson X11)

push: push.o

all: push

clean:
	rm -f push *.o

.PHONY: clean push
