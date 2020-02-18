all: compile doc

compile: shamir39-split shamir39-combine

doc: shamir39.1 shamir39.1.html

shamir39-split: shamir39.c funcs.h funcs.c constants.h bip39.h bip39.c sha256.h sha256.c 
	$(CC) -O0 -DNOMLOCK -DHAVE_LITTLE_ENDIAN -W -Wall -o shamir39-split shamir39.c funcs.c bip39.c sha256.c -lgmp
	strip shamir39-split

shamir39-combine: shamir39-split
	ln -f shamir39-split shamir39-combine

shamir39.1: shamir39.manpage.xml
	if [ `which xmltoman` ]; then xmltoman shamir39.manpage.xml > shamir39.1; else echo "WARNING: xmltoman not found, skipping generate of man page."; fi
	if [ -e shamir39.1 ]; then cp shamir39.1 shamir39-split.1; cp shamir39.1 shamir39-combine.1; fi

shamir39.1.html: shamir39.manpage.xml
	if [ `which xmlmantohtml` ]; then xmlmantohtml shamir39.manpage.xml > shamir39.1.html; else echo "WARNING: xmlmantohtml not found, skipping generation of HTML documentation."; fi

clean:
	rm -rf shamir39-split shamir39-combine shamir39.1 shamir39-split.1 shamir39-combine.1 shamir39.1.html

install:
	if [ -e shamir39.1 ]; then install -o root -g wheel -m 644 shamir39.1 shamir39-split.1 shamir39-combine.1 /usr/share/man/man1; else echo "WARNING: No man page was generated, so none will be installed."; fi
	install -o root -g wheel -m 755 shamir39-split shamir39-combine /usr/bin
