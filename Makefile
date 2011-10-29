
OS = Linux
GTK_FLAGS := `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`
WEBKIT_FLAGS := `pkg-config --cflags --libs webkit-1.0`
LIBS = -Iinclude -I/usr/include -I/usr/lib/neko/include -I/usr/include/gtk-2.0
NDLL = ndll/$(OS)/webkit.ndll
SRC = src/*.c include/*.h
OBJS = src/util.o src/hxgtk.o src/hxwebkit.o src/javascript.o src/plugin_test.o


all: ndll


%.o : %.c
	$(CC) $(LIBS) $(GTK_FLAGS) $(WEBKIT_FLAGS) -c -o $@ $<


ndll : $(OBJS) $(SRC) Makefile
	$(CC) -shared -o $(NDLL) -O2 -g -Wall -fmessage-length=0 $(OBJS) $(LIBS) $(WEBKIT_FLAGS)

install : ndll
	cp $(NDLL) /usr/lib/neko/
	
uninstall :
	rm -f /usr/lib/neko/webkit.ndll

samples : samples/* Makefile
	cd samples/ && haxe build.hxml
	
samples-run : samples Makefile
	cd samples/ && neko testwebkit.n


cpp-32 : $(OBJS) src/*.c Makefile
	haxelib run hxcpp ndll.xml
	#$(CC) $(OBJS) $(LIBS) $(WEBKIT_FLAGS) -c -fvisibility=hidden -O2 -fpic -fPIC -DHX_LINUX -m32 -I/home/t0ng/data/dev/haxelib/hxcpp/2,08,0/include
cpp : cpp-32
	

clean:
	rm -f src/*.o
	rm -f $(NDLL)


.PHONY: ndll install uninstall samples samples-run cpp clean all
