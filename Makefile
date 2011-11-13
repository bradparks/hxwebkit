
OS = Linux
PROJECT := webkit
INSTALL_PATH = /usr/lib/neko/
CFLAGS = -shared -g -O2 -Wall
NDLL = ndll/$(OS)/$(PROJECT).ndll
WEBKIT_FLAGS := $(shell pkg-config --cflags --libs gtk+-2.0 webkit-1.0)
LDFLAGS = -Iinclude -I/usr/include -I/usr/lib/neko/include
OBJ = src/hxwebkit.o src/hxwebkit_webview.o src/hxwebkit_javascript.o src/hxwebkit_util.o \
	src/hxwebkit_plugin_test.o

all: $(NDLL)

%.o : %.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(WEBKIT_FLAGS) -c -o $@ $<

$(NDLL): $(OBJ)
	$(CC) $(CFLAGS) -o $(NDLL) $(OBJ) $(LDFLAGS) $(WEBKIT_FLAGS)
	
build: $(NDLL)

doc:
	cd doc && haxe build.hxml
	
install: build
	cp $(NDLL) $(INSTALL_PATH)
	
clean:
	rm -f src/*.o  $(NDLL) tests/*.n doc/*.xml doc/*.n doc/index.html
	rm -rf doc/content

.PHONY: all build tests tests-run doc install clean
