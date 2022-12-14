# $Header$
#
CFLAGS	      = -D$(VERSION) -I../../../../include -O

DEST	      = ../../../../lib

EXTHDRS	      = ../../../../include/hash.h \
		../../../../include/macro.h \
		../../../../include/null.h

HDRS	      =

LIBNAME	      = hash

LIBRARY	      = libhash.a

LINTFLAGS     = -D$(VERSION) -I../../../../include

LINTLIB	      = llib-l$(LIBNAME).ln

LINTLIST      = -lc

MAKEFILE      = Makefile

OBJS	      = hthash.o \
		htinit.o \
		htinstall.o \
		htlookup.o \
		htrm.o

PRINT	      = pr

SRCS	      = hthash.c \
		htinit.c \
		htinstall.c \
		htlookup.c \
		htrm.c

VERSION	      = V4BSD

all:		$(LIBRARY)

$(LIBRARY):	$(OBJS) $(LINTLIB)
		@echo -n "Loading $(LIBRARY) ... "
		@ar cru $(LIBRARY) $(OBJS)
		@ranlib $(LIBRARY)
		@echo "done"

$(LINTLIB):	$(SRCS) $(HDRS) $(EXTHDRS)
		@echo "Loading $(LINTLIB) ..."
		@lint $(LINTFLAGS) -C$(LIBNAME) $(SRCS)
		@echo "done"

clean:;		@rm -f $(OBJS)

co:;		@co -r$(VERSION) $(HDRS) $(SRCS)

depend:;	@mkmf -f $(MAKEFILE) LIBRARY=$(LIBRARY) DEST=$(DEST)

diff:;		@rcsdiff -r$(VERSION) $(HDRS) $(SRCS)

extract:;	@ar xo $(DEST)/$(LIBRARY)
		@rm -f __.SYMDEF

index:;		@ctags -wx $(HDRS) $(SRCS)

install:	$(LIBRARY)
		@echo Installing $(LIBRARY) in $(DEST)
		@install $(LIBRARY) $(DEST)
		@ranlib $(DEST)/$(LIBRARY)
		@echo Installing $(LINTLIB) in $(DEST)
		@install $(LINTLIB) $(DEST)

library:        $(LIBRARY)

lint:;		@lint $(LINTFLAGS) $(SRCS) $(LINTLIST)

lintlib:	$(LINTLIB)

print:;		@$(PRINT) $(HDRS) $(SRCS)

tags:           $(HDRS) $(SRCS); @ctags $(HDRS) $(SRCS)

update:         $(DEST)/$(LIBRARY)

$(DEST)/$(LIBRARY): $(SRCS) $(HDRS) $(EXTHDRS)
		@-ar xo $(DEST)/$(LIBRARY)
		@make -f $(MAKEFILE) DEST=$(DEST) install tags clean
