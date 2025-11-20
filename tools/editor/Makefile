CFLAGS := $(shell pkg-config X11 Xt Xext Xp --cflags)
CFLAGS += -I/opt/homebrew/Cellar/openmotif/2.3.8_3/include
LDLIBS := $(shell pkg-config X11 Xt Xext Xp --libs)
LDLIBS += -L/opt/homebrew/Cellar/openmotif/2.3.8_3/lib -lXm

push: push.o junk.o

clean:
	rm push

.PHONY: clean
