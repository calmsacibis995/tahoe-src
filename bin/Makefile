#
# Copyright (c) 1980, 1988 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
#	@(#)Makefile	5.28 (Berkeley) 7/9/88
#
DESTDIR=
CFLAGS=	-O
LIBC=	/lib/libc.a

# Programs that live in subdirectories, and have makefiles of their own.
#
SUBDIR=	adb as awk cpio csh diff make passwd sed sh tp

# Shell scripts that need only be installed and are never removed.
#
SCRIPT=	false true

# C source that lives in the current directory
#
SRCS=	ar.c cat.c cc.c chmod.c cmp.c cp.c date.c dd.c df.c du.c \
	echo.c ed.c expr.c hostid.c hostname.c kill.c ld.c ln.c login.c \
	ls.c machine.c mkdir.c mt.c mv.c nice.c nm.c od.c pagesize.c \
	pr.c ps.c pwd.c rcp.c rm.c rmdir.c size.c strip.c \
	stty.c su.c sync.c tar.c tee.c test.c time.c wall.c who.c write.c

# C programs that live in the current directory and do not need
# explicit make lines.
#
STD=	ar cat cc chmod cmp cp date dd du echo ed hostid \
	hostname kill ld ln ls machine mkdir mt mv nice nm od pagesize pr \
	pwd rm rmdir size strip stty sync tar tee test time who

# C programs that live in the current directory and need explicit make lines.
#
NSTD=	expr ps

# Programs that get installed with special permissions
#
PERM=	df login rcp su wall write

all:	${SUBDIR} ${STD} ${NSTD} ${PERM}

${SUBDIR}: FRC
	cd $@; make ${MFLAGS}

${STD} ${PERM}: ${LIBC}
	${CC} ${CFLAGS} -o $@ $@.c

install: FRC
	-for i in ${SUBDIR}; do \
		(cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} install); done
	-for i in ${SCRIPT}; do \
		(install -c -o bin -g bin -m 755 $$i.sh ${DESTDIR}/bin/$$i); \
	done
	install -o bin -g bin -m 755 ${STD} ${DESTDIR}/bin
# programs that run with special permissions
	install -s -o root -g bin -m 4755 login ${DESTDIR}/bin/login
	install -s -o root -g bin -m 4755 rcp ${DESTDIR}/bin/rcp
	install -s -o root -g bin -m 4755 su ${DESTDIR}/bin/su
	install -s -o bin -g operator -m 2755 df ${DESTDIR}/bin/df
	install -s -o bin -g kmem -m 2755 ps ${DESTDIR}/bin/ps
	install -s -o bin -g tty -m 2755 wall ${DESTDIR}/bin/wall
	install -s -o bin -g tty -m 2755 write ${DESTDIR}/bin/write
	install -s -o bin -g bin -m 755 expr ${DESTDIR}/bin/expr
# directories and links
	rm -f ${DESTDIR}/bin/[; ln ${DESTDIR}/bin/test ${DESTDIR}/bin/[
	rm -f ${DESTDIR}/bin/e; ln ${DESTDIR}/bin/ed ${DESTDIR}/bin/e

clean: FRC
	rm -f ${STD} ${NSTD} ${PERM} expr.c a.out core *.s *.o errs
	for i in ${SUBDIR}; do (cd $$i; make ${MFLAGS} clean); done

depend: ldepend
	for i in ${SUBDIR}; do (cd $$i; make ${MFLAGS} depend); done

ldepend: expr.c FRC
	mkdep -p ${CFLAGS} ${SRCS}

FRC:

# Files listed in ${NSTD} have explicit make lines given below.

expr: expr.o
	${CC} ${CFLAGS} -o $@ expr.o

ps:
	${CC} ${CFLAGS} -o $@ ps.c -lm

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

ar: ar.c /usr/include/sys/param.h /usr/include/sys/types.h
ar: /usr/include/signal.h /usr/include/machine/trap.h
ar: /usr/include/machine/machparam.h /usr/include/machine/endian.h
ar: /usr/include/sys/stat.h /usr/include/sys/time.h /usr/include/time.h
ar: /usr/include/stdio.h /usr/include/ar.h
cat: cat.c /usr/include/stdio.h /usr/include/sys/types.h
cat: /usr/include/sys/stat.h
cc: cc.c /usr/include/sys/param.h /usr/include/sys/types.h
cc: /usr/include/signal.h /usr/include/machine/trap.h
cc: /usr/include/machine/machparam.h /usr/include/machine/endian.h
cc: /usr/include/stdio.h /usr/include/ctype.h /usr/include/signal.h
cc: /usr/include/sys/dir.h
chmod: chmod.c /usr/include/stdio.h /usr/include/sys/types.h
chmod: /usr/include/sys/stat.h /usr/include/sys/dir.h
cmp: cmp.c /usr/include/sys/param.h /usr/include/sys/types.h
cmp: /usr/include/signal.h /usr/include/machine/trap.h
cmp: /usr/include/machine/machparam.h /usr/include/machine/endian.h
cmp: /usr/include/sys/file.h /usr/include/sys/stat.h /usr/include/stdio.h
cmp: /usr/include/ctype.h /usr/include/errno.h
cp: cp.c /usr/include/stdio.h /usr/include/sys/param.h /usr/include/sys/types.h
cp: /usr/include/signal.h /usr/include/machine/trap.h
cp: /usr/include/machine/machparam.h /usr/include/machine/endian.h
cp: /usr/include/sys/stat.h /usr/include/sys/dir.h /usr/include/sys/time.h
cp: /usr/include/time.h
date: date.c /usr/include/sys/param.h /usr/include/sys/types.h
date: /usr/include/signal.h /usr/include/machine/trap.h
date: /usr/include/machine/machparam.h /usr/include/machine/endian.h
date: /usr/include/sys/time.h /usr/include/time.h /usr/include/sys/file.h
date: /usr/include/errno.h /usr/include/syslog.h /usr/include/utmp.h
date: /usr/include/tzfile.h /usr/include/stdio.h /usr/include/ctype.h
date: /usr/include/strings.h /usr/include/sys/socket.h
date: /usr/include/netinet/in.h /usr/include/netdb.h
date: /usr/include/protocols/timed.h
dd: dd.c /usr/include/sys/file.h /usr/include/stdio.h /usr/include/signal.h
dd: /usr/include/machine/trap.h
df: df.c /usr/include/sys/param.h /usr/include/sys/types.h
df: /usr/include/signal.h /usr/include/machine/trap.h
df: /usr/include/machine/machparam.h /usr/include/machine/endian.h
df: /usr/include/sys/fs.h /usr/include/sys/stat.h /usr/include/errno.h
df: /usr/include/stdio.h /usr/include/fstab.h /usr/include/mtab.h
du: du.c /usr/include/stdio.h /usr/include/sys/param.h /usr/include/sys/types.h
du: /usr/include/signal.h /usr/include/machine/trap.h
du: /usr/include/machine/machparam.h /usr/include/machine/endian.h
du: /usr/include/sys/stat.h /usr/include/sys/dir.h
echo: echo.c /usr/include/stdio.h
ed: ed.c /usr/include/signal.h /usr/include/machine/trap.h /usr/include/sgtty.h
ed: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
ed: /usr/include/sys/ttydev.h /usr/include/setjmp.h
expr: expr.c /usr/include/stdio.h
hostid: hostid.c /usr/include/sys/types.h /usr/include/stdio.h
hostid: /usr/include/netdb.h
hostname: hostname.c /usr/include/stdio.h /usr/include/sys/param.h
hostname: /usr/include/sys/types.h /usr/include/signal.h
hostname: /usr/include/machine/trap.h /usr/include/machine/machparam.h
hostname: /usr/include/machine/endian.h
kill: kill.c /usr/include/signal.h /usr/include/machine/trap.h
kill: /usr/include/ctype.h
ld: ld.c /usr/include/sys/param.h /usr/include/sys/types.h
ld: /usr/include/signal.h /usr/include/machine/trap.h
ld: /usr/include/machine/machparam.h /usr/include/machine/endian.h
ld: /usr/include/signal.h /usr/include/stdio.h /usr/include/ctype.h
ld: /usr/include/ar.h /usr/include/a.out.h /usr/include/sys/exec.h
ld: /usr/include/ranlib.h /usr/include/sys/stat.h /usr/include/sys/file.h
ln: ln.c /usr/include/sys/param.h /usr/include/sys/types.h
ln: /usr/include/signal.h /usr/include/machine/trap.h
ln: /usr/include/machine/machparam.h /usr/include/machine/endian.h
ln: /usr/include/sys/stat.h /usr/include/stdio.h /usr/include/errno.h
login: login.c /usr/include/sys/param.h /usr/include/sys/types.h
login: /usr/include/signal.h /usr/include/machine/trap.h
login: /usr/include/machine/machparam.h /usr/include/machine/endian.h
login: /usr/include/sys/quota.h /usr/include/sys/stat.h /usr/include/sys/time.h
login: /usr/include/time.h /usr/include/sys/resource.h /usr/include/sys/file.h
login: /usr/include/sgtty.h /usr/include/sys/ioctl.h
login: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
login: /usr/include/utmp.h /usr/include/signal.h /usr/include/pwd.h
login: /usr/include/stdio.h /usr/include/lastlog.h /usr/include/errno.h
login: /usr/include/ttyent.h /usr/include/syslog.h /usr/include/grp.h
ls: ls.c /usr/include/sys/param.h /usr/include/sys/types.h
ls: /usr/include/signal.h /usr/include/machine/trap.h
ls: /usr/include/machine/machparam.h /usr/include/machine/endian.h
ls: /usr/include/sys/stat.h /usr/include/sys/dir.h /usr/include/stdio.h
ls: /usr/include/sgtty.h /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
ls: /usr/include/sys/ttydev.h /usr/include/pwd.h /usr/include/grp.h
ls: /usr/include/utmp.h
machine: machine.c /usr/include/sys/param.h /usr/include/sys/types.h
machine: /usr/include/signal.h /usr/include/machine/trap.h
machine: /usr/include/machine/machparam.h /usr/include/machine/endian.h
mkdir: mkdir.c /usr/include/stdio.h
mt: mt.c /usr/include/stdio.h /usr/include/ctype.h /usr/include/sys/types.h
mt: /usr/include/sys/mtio.h /usr/include/sys/ioctl.h
mt: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
mt: /usr/include/tahoevba/cyreg.h
mv: mv.c /usr/include/sys/param.h /usr/include/sys/types.h
mv: /usr/include/signal.h /usr/include/machine/trap.h
mv: /usr/include/machine/machparam.h /usr/include/machine/endian.h
mv: /usr/include/sys/stat.h /usr/include/sys/time.h /usr/include/time.h
mv: /usr/include/sys/file.h /usr/include/stdio.h /usr/include/errno.h
nice: nice.c /usr/include/stdio.h /usr/include/sys/time.h /usr/include/time.h
nice: /usr/include/sys/resource.h
nm: nm.c /usr/include/sys/types.h /usr/include/sys/file.h /usr/include/ar.h
nm: /usr/include/stdio.h /usr/include/ctype.h /usr/include/a.out.h
nm: /usr/include/sys/exec.h /usr/include/stab.h /usr/include/ranlib.h
od: od.c /usr/include/stdio.h /usr/include/sys/types.h /usr/include/sys/stat.h
pagesize: pagesize.c
pr: pr.c /usr/include/stdio.h /usr/include/signal.h /usr/include/machine/trap.h
pr: /usr/include/sys/types.h /usr/include/sys/stat.h
ps: ps.c /usr/include/stdio.h /usr/include/ctype.h /usr/include/a.out.h
ps: /usr/include/sys/exec.h /usr/include/pwd.h /usr/include/sys/param.h
ps: /usr/include/sys/types.h /usr/include/signal.h /usr/include/machine/trap.h
ps: /usr/include/machine/machparam.h /usr/include/machine/endian.h
ps: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
ps: /usr/include/sys/ttydev.h /usr/include/sys/tty.h
ps: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
ps: /usr/include/sys/dir.h /usr/include/sys/user.h /usr/include/machine/pcb.h
ps: /usr/include/sys/dmap.h /usr/include/sys/time.h /usr/include/time.h
ps: /usr/include/sys/resource.h /usr/include/sys/namei.h /usr/include/sys/uio.h
ps: /usr/include/errno.h /usr/include/sys/proc.h /usr/include/machine/pte.h
ps: /usr/include/sys/vm.h /usr/include/sys/vmparam.h
ps: /usr/include/machine/vmparam.h /usr/include/sys/vmmac.h
ps: /usr/include/sys/vmmeter.h /usr/include/sys/vmsystm.h
ps: /usr/include/sys/text.h /usr/include/sys/stat.h /usr/include/sys/mbuf.h
ps: /usr/include/math.h /usr/include/errno.h /usr/include/utmp.h
pwd: pwd.c /usr/include/stdio.h /usr/include/sys/param.h
pwd: /usr/include/sys/types.h /usr/include/signal.h /usr/include/machine/trap.h
pwd: /usr/include/machine/machparam.h /usr/include/machine/endian.h
rcp: rcp.c /usr/include/sys/param.h /usr/include/sys/types.h
rcp: /usr/include/signal.h /usr/include/machine/trap.h
rcp: /usr/include/machine/machparam.h /usr/include/machine/endian.h
rcp: /usr/include/sys/file.h /usr/include/sys/stat.h /usr/include/sys/time.h
rcp: /usr/include/time.h /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
rcp: /usr/include/sys/ttydev.h /usr/include/netinet/in.h /usr/include/stdio.h
rcp: /usr/include/signal.h /usr/include/pwd.h /usr/include/ctype.h
rcp: /usr/include/netdb.h /usr/include/errno.h /usr/include/sys/dir.h
rm: rm.c /usr/include/stdio.h /usr/include/sys/param.h /usr/include/sys/types.h
rm: /usr/include/signal.h /usr/include/machine/trap.h
rm: /usr/include/machine/machparam.h /usr/include/machine/endian.h
rm: /usr/include/sys/stat.h /usr/include/sys/dir.h /usr/include/sys/file.h
rmdir: rmdir.c /usr/include/stdio.h
size: size.c /usr/include/sys/param.h /usr/include/sys/types.h
size: /usr/include/signal.h /usr/include/machine/trap.h
size: /usr/include/machine/machparam.h /usr/include/machine/endian.h
size: /usr/include/sys/file.h /usr/include/a.out.h /usr/include/sys/exec.h
size: /usr/include/stdio.h
strip: strip.c /usr/include/a.out.h /usr/include/sys/exec.h
strip: /usr/include/signal.h /usr/include/machine/trap.h /usr/include/stdio.h
strip: /usr/include/sys/file.h
stty: stty.c /usr/include/stdio.h /usr/include/sys/ioctl.h
stty: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
su: su.c /usr/include/stdio.h /usr/include/pwd.h /usr/include/grp.h
su: /usr/include/syslog.h /usr/include/sys/types.h /usr/include/sys/time.h
su: /usr/include/time.h /usr/include/sys/resource.h
sync: sync.c
tar: tar.c /usr/include/stdio.h /usr/include/sys/param.h
tar: /usr/include/sys/types.h /usr/include/signal.h /usr/include/machine/trap.h
tar: /usr/include/machine/machparam.h /usr/include/machine/endian.h
tar: /usr/include/sys/stat.h /usr/include/sys/dir.h /usr/include/sys/ioctl.h
tar: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
tar: /usr/include/sys/mtio.h /usr/include/sys/time.h /usr/include/time.h
tar: /usr/include/signal.h /usr/include/errno.h /usr/include/fcntl.h
tee: tee.c /usr/include/signal.h /usr/include/machine/trap.h
tee: /usr/include/sys/types.h /usr/include/sys/stat.h /usr/include/errno.h
test: test.c /usr/include/stdio.h /usr/include/sys/types.h
test: /usr/include/sys/stat.h
time: time.c /usr/include/stdio.h /usr/include/signal.h
time: /usr/include/machine/trap.h /usr/include/sys/types.h
time: /usr/include/sys/time.h /usr/include/time.h /usr/include/sys/resource.h
wall: wall.c /usr/include/stdio.h /usr/include/utmp.h /usr/include/errno.h
wall: /usr/include/signal.h /usr/include/machine/trap.h /usr/include/sys/time.h
wall: /usr/include/time.h /usr/include/fcntl.h /usr/include/sys/types.h
wall: /usr/include/sys/stat.h
who: who.c /usr/include/stdio.h /usr/include/utmp.h /usr/include/pwd.h
who: /usr/include/ctype.h
write: write.c /usr/include/stdio.h /usr/include/ctype.h
write: /usr/include/sys/types.h /usr/include/sys/stat.h /usr/include/signal.h
write: /usr/include/machine/trap.h /usr/include/utmp.h /usr/include/sys/time.h
write: /usr/include/time.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
