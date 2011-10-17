
SYS = Linux
GTK_FLAGS := `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`
WEBKIT_FLAGS := `pkg-config --cflags --libs webkit-1.0`
LIBS = -I/usr/include -I/usr/lib/neko/include -I/usr/include/gtk-3.0
NDLL = ndll/$(SYS)/webkit.ndll

OBJS = src/gtk.o src/webkit.o src/util.o

all: $(NDLL)

%.o : %.c
	$(CC) $(LIBS) $(GTK_FLAGS) $(WEBKIT_FLAGS) -c -o $@ $<

$(NDLL): $(OBJS) src/*.c Makefile
	$(CC) -shared -o $@ -O2 -g -Wall -fmessage-length=0 $(OBJS) $(LIBS) $(WEBKIT_FLAGS)

install : $(NDLL)
	cp $(NDLL) /usr/lib/neko/
	
uninstall :
	rm -f /usr/lib/neko/webkit.ndll

test :
	cd tests && haxe build.hxml
	
test-run : test
	cd tests && neko testwebkit.n
	
clean:
	rm -f src/*.o
	rm -f $(NDLL)

.PHONY: install uninstall test test-run clean all
