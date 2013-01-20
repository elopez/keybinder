CC=gcc

keybinder: map.o key.o
	$(CC) -o $@ $^

.PHONY: install uninstall clean

install: keybinder
	cp keybinder /usr/local/bin/
	chmod 755 /usr/local/bin/keybinder
	cp keybinder.conf /etc/

uninstall:
	rm -f /usr/local/bin/keybinder

clean:
	rm -f keybinder *.o
