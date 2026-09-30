CC      = clang
CFLAGS  = -Wall -Wextra -pedantic
PREFIX  = /usr/local

acorem: src/main.c
	$(CC) $(CFLAGS) -o acorem src/main.c

install: acorem
	install -d $(DESTDIR)$(PREFIX)/bin
	install -m 755 acorem $(DESTDIR)$(PREFIX)/bin/acorem

update:
	git pull
	$(MAKE) install

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/acorem

clean:
	rm -f acorem

.PHONY: install uninstall clean
