# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
#
#	%W% (Berkeley) %G%
#

# The following is the telnet makefile for tn3270, using the shared telnet
# sources.

VPATH	=	../../telnet/Source
INCLUDES=	-I../../telnet/Source -I.
DEFINES	=	-DTN3270
CFLAGS	=	-O ${INCLUDES} ${DEFINES}
LD	=	ld
LDFLAGS	=	-r
LIBC=	/lib/libc.a
SRCS=	commands.c main.c network.c ring.c \
	sys_bsd.c sys_dos.c telnet.c terminal.c \
	tn3270.c utilities.c
OBJS=	commands.o main.o network.o ring.o sys_bsd.o sys_dos.o \
	telnet.o terminal.o tn3270.o utilities.o

all: telnet

telnet:	${OBJS} ${LIBC}
	${LD} ${LDFLAGS} -o $@ ${OBJS}

clean: FRC
	rm -f ${OBJS} core telnet

depend: FRC ${SRCS}
	mkdep ${CFLAGS} ${SRCS}

install: FRC
	install -s -o bin -g bin -m 755 telnet ${DESTDIR}/usr/ucb/telnet

lint: FRC
	lint ${CFLAGS} ${SRCS}

tags: FRC
	ctags ${SRCS}

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

commands.o: ../../telnet/Source/commands.c /usr/include/sys/types.h
commands.o: /usr/include/sys/socket.h /usr/include/netinet/in.h
commands.o: /usr/include/signal.h /usr/include/machine/trap.h
commands.o: /usr/include/netdb.h /usr/include/ctype.h
commands.o: /usr/include/arpa/telnet.h ../../telnet/Source/ring.h
commands.o: ../../telnet/Source/externs.h /usr/include/stdio.h
commands.o: /usr/include/setjmp.h ../../telnet/Source/defines.h
commands.o: ../../telnet/Source/types.h
main.o: ../../telnet/Source/main.c /usr/include/sys/types.h
main.o: ../../telnet/Source/ring.h ../../telnet/Source/externs.h
main.o: /usr/include/stdio.h /usr/include/setjmp.h
main.o: ../../telnet/Source/defines.h
network.o: ../../telnet/Source/network.c /usr/include/sys/types.h
network.o: /usr/include/sys/socket.h /usr/include/sys/time.h
network.o: /usr/include/time.h /usr/include/errno.h /usr/include/arpa/telnet.h
network.o: ../../telnet/Source/ring.h ../../telnet/Source/defines.h
network.o: ../../telnet/Source/externs.h /usr/include/stdio.h
network.o: /usr/include/setjmp.h ../../telnet/Source/fdset.h
ring.o: ../../telnet/Source/ring.c /usr/include/stdio.h /usr/include/errno.h
ring.o: /usr/include/sys/types.h /usr/include/sys/ioctl.h
ring.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
ring.o: /usr/include/sys/socket.h ../../telnet/Source/ring.h
ring.o: ../../telnet/Source/general.h
sys_bsd.o: ../../telnet/Source/sys_bsd.c /usr/include/sys/ioctl.h
sys_bsd.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
sys_bsd.o: /usr/include/sys/types.h /usr/include/sys/time.h /usr/include/time.h
sys_bsd.o: /usr/include/sys/socket.h /usr/include/signal.h
sys_bsd.o: /usr/include/machine/trap.h /usr/include/errno.h
sys_bsd.o: ../../telnet/Source/ring.h ../../telnet/Source/fdset.h
sys_bsd.o: ../../telnet/Source/defines.h ../../telnet/Source/externs.h
sys_bsd.o: /usr/include/stdio.h /usr/include/setjmp.h
sys_bsd.o: ../../telnet/Source/types.h
sys_dos.o: ../../telnet/Source/sys_dos.c
telnet.o: ../../telnet/Source/telnet.c /usr/include/sys/types.h
telnet.o: /usr/include/curses.h /usr/include/stdio.h /usr/include/sgtty.h
telnet.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
telnet.o: /usr/include/sys/ttydev.h /usr/include/arpa/telnet.h
telnet.o: /usr/include/strings.h ../../telnet/Source/ring.h
telnet.o: ../../telnet/Source/defines.h ../../telnet/Source/externs.h
telnet.o: /usr/include/stdio.h /usr/include/setjmp.h
telnet.o: ../../telnet/Source/types.h ../../telnet/Source/general.h
telnet.o: /usr/include/varargs.h
terminal.o: ../../telnet/Source/terminal.c /usr/include/arpa/telnet.h
terminal.o: /usr/include/sys/types.h ../../telnet/Source/ring.h
terminal.o: ../../telnet/Source/externs.h /usr/include/stdio.h
terminal.o: /usr/include/setjmp.h ../../telnet/Source/types.h
tn3270.o: ../../telnet/Source/tn3270.c ../../telnet/Source/fdset.h
utilities.o: ../../telnet/Source/utilities.c /usr/include/arpa/telnet.h
utilities.o: /usr/include/sys/types.h /usr/include/ctype.h
utilities.o: ../../telnet/Source/ring.h ../../telnet/Source/externs.h
utilities.o: /usr/include/stdio.h /usr/include/setjmp.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
