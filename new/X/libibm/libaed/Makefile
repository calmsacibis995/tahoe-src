# Makefile for AED Device Dependent X library

SRCDIR= ../libsrc
INCPATH= -I. -I../../include -I../../X -I../bitblt
# CC= cc -g
CFLAGS= -c -C -O -DAED $(INCPATH)

SRCS= bitpix.c copy.c copybits.c cursor.c draw.c fill.c font.c \
	globals.c display.c put.c reversebits.c text.c tile.c \
	util.c aed.c mpixline.c makemask.c pathlist.c spixline.c \
	keyboard.c

OBJS= bitpix.o copy.o copybits.o cursor.o draw.o fill.o font.o \
	globals.o display.o put.o reversebits.o text.o tile.o \
	util.o aed.o mpixline.o makemask.o pathlist.o spixline.o \
	keyboard.o

all: libaed.a

bitpix.o: $(SRCDIR)/private.h $(SRCDIR)/bitblt.h $(SRCDIR)/bitpix.c
	$(CC) $(CFLAGS) $(SRCDIR)/bitpix.c
copy.o: $(SRCDIR)/private.h $(SRCDIR)/bitblt.h $(SRCDIR)/copy.c
	$(CC) $(CFLAGS) $(SRCDIR)/copy.c
fill.o: $(SRCDIR)/private.h $(SRCDIR)/bitblt.h $(SRCDIR)/fill.c
	$(CC) $(CFLAGS) $(SRCDIR)/fill.c
font.o: $(SRCDIR)/private.h $(SRCDIR)/xsite.h $(SRCDIR)/font.h \
	$(SRCDIR)/font.c
	$(CC) $(CFLAGS) $(SRCDIR)/font.c
globals.o: $(SRCDIR)/private.h $(SRCDIR)/globals.c
	$(CC) $(CFLAGS) $(SRCDIR)/globals.c
put.o: $(SRCDIR)/private.h $(SRCDIR)/bitblt.h $(SRCDIR)/put.c
	$(CC) $(CFLAGS) $(SRCDIR)/put.c
text.o: $(SRCDIR)/private.h $(SRCDIR)/bitblt.h $(SRCDIR)/text.h $(SRCDIR)/text.c
	$(CC) $(CFLAGS) $(SRCDIR)/text.c
tile.o: $(SRCDIR)/private.h $(SRCDIR)/bitblt.h $(SRCDIR)/tile.c
	$(CC) $(CFLAGS) $(SRCDIR)/tile.c
util.o: $(SRCDIR)/private.h $(SRCDIR)/util.c
	$(CC) $(CFLAGS) $(SRCDIR)/util.c
copybits.o: $(SRCDIR)/private.h $(SRCDIR)/bitblt.h $(SRCDIR)/copybits.c
	$(CC) $(CFLAGS) $(SRCDIR)/copybits.c
reversebits.o: $(SRCDIR)/private.h $(SRCDIR)/reversebits.c
	$(CC) $(CFLAGS) $(SRCDIR)/reversebits.c
draw.o: $(SRCDIR)/private.h $(SRCDIR)/bitblt.h $(SRCDIR)/draw.c
	$(CC) $(CFLAGS) $(SRCDIR)/draw.c
mpixline.o: $(SRCDIR)/private.h $(SRCDIR)/bitblt.h $(SRCDIR)/mpixline.c
	$(CC) $(CFLAGS) $(SRCDIR)/mpixline.c
spixline.o: $(SRCDIR)/private.h $(SRCDIR)/spixline.h $(SRCDIR)/spixline.c
	$(CC) $(CFLAGS) $(SRCDIR)/spixline.c
cursor.o: $(SRCDIR)/private.h $(SRCDIR)/cursor.c
	$(CC) $(CFLAGS) $(SRCDIR)/cursor.c
display.o: $(SRCDIR)/private.h $(SRCDIR)/display.c $(SRCDIR)/aed.h
	$(CC) $(CFLAGS) $(SRCDIR)/display.c
aed.o: $(SRCDIR)/private.h $(SRCDIR)/aed.h $(SRCDIR)/aed.c
	$(CC) $(CFLAGS) $(SRCDIR)/aed.c
makemask.o: $(SRCDIR)/private.h $(SRCDIR)/makemask.h $(SRCDIR)/pathlist.h \
	$(SRCDIR)/makemask.c
	$(CC) $(CFLAGS) $(SRCDIR)/makemask.c
pathlist.o: $(SRCDIR)/private.h $(SRCDIR)/pathlist.h $(SRCDIR)/pathlist.c
	$(CC) $(CFLAGS) $(SRCDIR)/pathlist.c
keyboard.o: $(SRCDIR)/private.h $(SRCDIR)/keymatch.h $(SRCDIR)/keyboard.c
	$(CC) $(CFLAGS) $(SRCDIR)/keyboard.c
$(SRCDIR)/private.h: /usr/include/machinecons/xio.h /usr/include/sys/types.h \
	/usr/include/stdio.h ../../X/vsinput.h ../../X/Xdev.h ../../X/X.h \
	/usr/include/machinecons/qevent.h /usr/include/sys/ioctl.h \
	/usr/include/sgtty.h /usr/include/fcntl.h /usr/include/sys/tbioctl.h \
	/usr/include/machineio/mouseio.h /usr/include/machinecons/qevent.h
	touch $(SRCDIR)/private.h

libaed.a: $(OBJS)
	@rm -f libaed.a
	ar r libaed.a $(OBJS)
	@ranlib libaed.a

clean:
	rm -f *.o libaed.a
