#
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	@(#)Makefile	5.5	(Berkeley)	1/21/88
#
# reorder gives an editor command for most common terminals
# (in reverse order from n'th to 1'st most commonly used)
# to move them to the front of termcap
#
all: termcap

termcap: reorder termcap.src
	ex - termcap.src < reorder

clean: FRC
	rm -f termcap

install: FRC
	install -c -o bin -g bin -m 444 map3270 ${DESTDIR}/etc/map3270
	install -o bin -g staff -m 444 termcap ${DESTDIR}/etc/termcap
	rm -rf ${DESTDIR}/usr/lib/tabset
	mkdir ${DESTDIR}/usr/lib/tabset
	chown bin.bin ${DESTDIR}/usr/lib/tabset
	chmod 755 ${DESTDIR}/usr/lib/tabset
	install -c -o bin -g bin -m 444 tabset/* ${DESTDIR}/usr/lib/tabset

depend:
lint:
tags:
FRC:
