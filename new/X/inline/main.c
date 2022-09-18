/* Copyright (c) 1984 Regents of the University of California */

#ifndef lint
static char sccsid[] = "@(#)main.c	1.6	(Berkeley)	9/20/84";
#endif not lint

#include <stdio.h>
#include <ctype.h>
#include "inline.h"

/*
 * These are the pattern tables to be loaded
 */
struct pats *inittables[] = {
	language_ptab,
	libc_ptab,
	machine_ptab,
	0
};

/*
 * Statistics collection
 */
struct stats {
	int	attempted;	/* number of expansion attempts */
	int	finished;	/* expansions done before end of basic block */
	int	lostmodified;	/* mergers inhibited by intervening mod */
	int	savedpush;	/* successful push/pop merger */
	int     savedmove;      /* move to tmp reg eliminated */
} stats;
int dflag;

main(argc, argv)
	int argc;
	char *argv[];
{
	register char *cp, *lp, *qp;
	register char *bufp;
	register struct pats *pp, **php;
	struct pats **tablep;
	register struct inststoptbl *itp, **ithp;
	int size;
	extern char *index();

	if (argc > 1 && bcmp(argv[1], "-d", 3) == 0)
		dflag++, argc--, argv++;
	if (argc > 1)
		freopen(argv[1], "r", stdin);
	if (argc > 2)
		freopen(argv[2], "w", stdout);
	/*
	 * Set up the hash table for the patterns.
	 */
	for (tablep = inittables; *tablep; tablep++) {
		for (pp = *tablep; pp->name[0] != '\0'; pp++) {
			php = &patshdr[hash(pp->name, &size)];
			pp->size = size;
			pp->next = *php;
			*php = pp;
		}
	}
	/*
	 * Set up the hash table for the instruction stop table.
	 */
	for (itp = inststoptable; itp->name[0] != '\0'; itp++) {
		ithp = &inststoptblhdr[hash(itp->name, &size)];
		itp->size = size;
		itp->next = *ithp;
		*ithp = itp;
	}
	/*
	 * check each line and replace as appropriate
	 */
	buftail = bufhead = 0;
	bufp = line[0];
	while (fgets(bufp, MAXLINELEN, stdin)) {
		lp = index(bufp, LABELCHAR);
		if (lp != NULL) {
			qp = index(bufp, QUOTECHAR);
			if (qp == NULL) {
			     bufp = newline();
			     if (*++lp == '\n') {
				emptyqueue();
				continue;
			      }
			     strcpy(bufp, lp);
			     *lp++ = '\n';
			     *lp = '\0';
			     emptyqueue();
			}
		}
		for (cp = bufp; isspace(*cp); cp++)
			/* void */;
		if ((cp = doreplaceon(cp)) == 0) {
			bufp = newline();
			continue;
		}
		for (pp = patshdr[hash(cp, &size)]; pp; pp = pp->next) {
			if (pp->size == size && bcmp(pp->name, cp, size) == 0) {
				expand(pp->replace);
				bufp = line[bufhead];
				break;
			}
		}
		if (!pp) {
			emptyqueue();
			fputs(bufp, stdout);
		}
	}
	emptyqueue();
	if (dflag)
		fprintf(stderr, "inline: %s %d, %s %d, %s %d, %s %d\n",
			"attempts", stats.attempted,
			"finished", stats.finished,
			"inhibited", stats.lostmodified,
			"merged", stats.savedpush,
	                "nomoves", stats.savedmove);
	exit(0);
}

/*
 * Integrate an expansion into the assembly stream
 */
expand(replace)
	char *replace;
{
	register int curptr;
	char *nextreplace, *argv[MAXARGS];
	int argc, argreg, foundarg, mod = 0, args = 0;
	char parsebuf[BUFSIZ];
	int argno = 0;
	int flag;
	struct oparg oparg[MAXARGS];

	stats.attempted++;
	for (curptr = bufhead; ; ) {
		nextreplace = copyline(replace, line[bufhead]);
		argc = parseline(line[bufhead], argv, parsebuf);
		argreg = nextarg(argc, argv, &flag);
		if (argreg == -1)
			break;
		args++;
		for (foundarg = 0; curptr != buftail; ) {
			curptr = PRED(curptr);
			argc = parseline(line[curptr], argv, parsebuf);
			if (isendofblock(argc, argv))
				break;
			if (foundarg = ispusharg(argc, argv))
				break;
			mod |= 1 << modifies(argc, argv);
		}
		if (!foundarg)
			break;
		replace = nextreplace;
		if (mod & (1 << argreg)) {
		    stats.lostmodified++;
		    if (curptr == buftail) {
			(void)newline();
			break;
		    }
		    (void)newline();
		} else {
		    if (checkvar(argc, argv, flag, oparg[argno].source, mod)) {
			line[curptr][0] = '\0';
			oparg[argno].reg = argreg;
			argno++;
			stats.savedmove++;
		    } else {
			rewrite(line[curptr], argc, argv, argreg);
			stats.savedpush++;
			mod |= 1 << argreg;
		    }
		}
	}
	if (argreg == -1)
		stats.finished++;
	emptyqueue();
	output_replace(replace, oparg, argno, stdout);
	cleanup(args);
}

/*
 * Parse a line of assembly language into opcode and arguments.
 */
parseline(linep, argv, linebuf)
	char *linep;
	char *argv[];
	char *linebuf;
{
	register char *bufp = linebuf, *cp = linep;
	register int argc = 0;

	for (;;) {
		/*
		 * skip over white space
		 */
		while (isspace(*cp))
			cp++;
		if (*cp == '\0')
			return (argc);
		/*
		 * copy argument
		 */
		if (argc == MAXARGS - 1) {
			fprintf(stderr, "instruction too long->%s", linep);
			return (argc);
		}
		argv[argc++] = bufp;
		while (!isspace(*cp) && *cp != ARGSEPCHAR && *cp != COMMENTCHAR)
			*bufp++ = *cp++;
		*bufp++ = '\0';
		if (*cp == COMMENTCHAR)
			return (argc);
		if (*cp == ARGSEPCHAR)
			cp++;
	}
}

/*
 * Check for instructions that end a basic block.
 */
isendofblock(argc, argv)
	int argc;
	char *argv[];
{
	register struct inststoptbl *itp;
	int size;

	if (argc == 0)
		return (0);
	for (itp = inststoptblhdr[hash(argv[0], &size)]; itp; itp = itp->next)
		if (itp->size == size && bcmp(argv[0], itp->name, size) == 0)
			return (1);
	return (0);
}

/*
 * Copy a newline terminated string.
 * Return pointer to character following last character copied.
 */
char *
copyline(from, to)
	register char *from, *to;
{

	while (*from != '\n')
		*to++ = *from++;
	*to++ = *from++;
	*to = '\0';
	return (from);
}

/*
 * open space for next line in the queue
 */
char *
newline()
{
	bufhead = SUCC(bufhead);
	if (bufhead == buftail) {
		fputs(line[buftail], stdout);
		buftail = SUCC(buftail);
	}
	return (line[bufhead]);
}

/*
 * empty the queue by printing out all its lines.
 */
emptyqueue()
{
	while (buftail != bufhead) {
		fputs(line[buftail], stdout);
		buftail = SUCC(buftail);
	}
}

/*
 * Compute the hash of a string.
 * Return the hash and the size of the item hashed
 */
hash(cp, size)
	char *cp;
	int *size;
{
	register char *cp1 = cp;
	register int hash = 0;

	while (*cp1 && *cp1 != '\n')
		hash += (int)*cp1++;
	*size = cp1 - cp + 1;
	hash &= HSHSIZ - 1;
	return (hash);
}
