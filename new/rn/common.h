/* $Header: common.h,v 4.3.1.4 86/10/31 15:46:09 lwall Exp $
 * 
 * $Log:	common.h,v $
 * Revision 4.3.1.4  86/10/31  15:46:09  lwall
 * Expanded maximum number of .newsrc lines for net reorganization.
 * 
 * Revision 4.3.1.3  85/05/23  17:19:32  lwall
 * Now allows 'r' and 'f' on null articles.
 * 
 * Revision 4.3.1.2  85/05/13  09:30:39  lwall
 * Added CUSTOMLINES option.
 * 
 * Revision 4.3.1.1  85/05/10  11:32:04  lwall
 * Branch for patches.
 * 
 * Revision 4.3  85/05/01  11:37:11  lwall
 * Baseline for release with 4.3bsd.
 * 
 */

#include "config.h"	/* generated by installation script */
#ifdef WHOAMI
#    include <whoami.h>
#endif

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>

#ifndef isalnum
#   define isalnum(c) (isalpha(c) || isdigit(c))
#endif

#include <errno.h>
#include <signal.h>
#ifdef IOCTL
#include <sys/ioctl.h>
#endif IOCTL

#ifdef FCNTL
#   include <fcntl.h>
#endif

#ifdef TERMIO
#   include <termio.h>
#else
#   include <sgtty.h>
#endif

#ifdef GETPWENT
#   include <pwd.h>
#endif

#define BITSPERBYTE 8
#define LBUFLEN 512	/* line buffer length */
			/* (don't worry, .newsrc lines can exceed this) */
#ifdef pdp11
#   define CBUFLEN 256	/* command buffer length */
#   define PUSHSIZE 128
#else
#   define CBUFLEN 512	/* command buffer length */
#   define PUSHSIZE 256
#endif
#ifdef pdp11
#   define MAXFILENAME 128
#else
#   define MAXFILENAME 512
#endif
#define LONGKEY 15	/* longest keyword: currently "posting-version" */
#define FINISHCMD 0177

/* some handy defs */

#define bool char
#define TRUE (1)
#define FALSE (0)
#define Null(t) ((t)0)
#define Nullch Null(char *)
#define Nullfp Null(FILE *)

#define Ctl(ch) (ch & 037)

#define strNE(s1,s2) (strcmp(s1,s2))
#define strEQ(s1,s2) (!strcmp(s1,s2))
#define strnNE(s1,s2,l) (strncmp(s1,s2,l))
#define strnEQ(s1,s2,l) (!strncmp(s1,s2,l))

/* Things we can figure out ourselves */

#ifdef SIGTSTP
#   define BERKELEY 	/* include job control signals? */
#endif

#ifdef SIGPROF
#   define BSD42		/* do we have Berkeley 4.2? */
#endif

#ifdef FIONREAD
#   define PENDING
#else
#   ifdef O_NDELAY
#	define PENDING
#   endif
#endif

#ifdef EUNICE
#   define LINKART		/* add 1 level of possible indirection */
#   define UNLINK(victim) while (!unlink(victim))
#else
#   define UNLINK(victim) unlink(victim)
#endif

/* Valid substitutions for strings marked with % comment are:
 *	%a	Current article number
 *	%A	Full name of current article (%P/%c/%a)
 *		(if LINKART defined, is the name of the real article)
 *	%b	Destination of a save command, a mailbox or command
 *	%B	The byte offset to the beginning of the article for saves
 *		with or without the header
 *	%c	Current newsgroup, directory form
 *	%C	Current newsgroup, dot form
 *	%d	%P/%c
 *	%D	Old Distribution: line
 *	%f	Old From: line or Reply-To: line
 *	%F	Newsgroups to followup to from Newsgroups: and Followup-To:
 *	%h	Name of header file to pass to mail or news poster
 *	%H	Host name (yours)
 *	%i	Old Message-I.D.: line, with <>
 *	%I	Inclusion indicator
 *	%l	News administrator login name
 *	%L	Login name (yours)
 *	%M	Number of articles markd with M
 *	%n	Newsgroups from source article
 *	%N	Full name (yours)
 *	%o	Organization (yours)
 *	%O	Original working directory (where you ran rn from)
 *	%p	Your private news directory (-d switch)
 *	%P	Public news spool directory (SPOOLDIR)
 *	%r	Last reference (parent article id)
 *	%R	New references list
 *	%s	Subject, with all Re's and (nf)'s stripped off
 *	%S	Subject, with one Re stripped off
 *	%t	New To: line derived from From: and Reply-To (Internet always)
 *	%T	New To: line derived from Path:
 *	%u	Number of unread articles
 *	%U	Number of unread articles disregarding current article
 *	%x	News library directory, usually /usr/lib/news
 *	%X	Rn library directory, usually %x/rn
 *	%z	Size of current article in bytes.
 *	%~	Home directory
 *	%.	Directory containing . files
 *	%$	current process number
 *	%{name} Environment variable "name".  %{name-default} form allowed.
 *	%[name]	Header line beginning with "Name: ", without "Name: " 
 *	%"prompt"
 *		Print prompt and insert what is typed.
 *	%`command`
 *		Insert output of command.
 *	%(test_text=pattern?if_text:else_text)
 *		Substitute if_text if test_text matches pattern, otherwise
 *		substitute else_text.  Use != for negated match.
 *		% substitutions are done on test_text, if_text, and else_text.
 *		(Note: %() only works if CONDSUB defined.)
 *	%digit	Substitute the text matched by the nth bracket in the last
 *		pattern that had brackets.  %0 matches the last bracket
 *		matched, in case you had alternatives.
 *
 *	Put ^ in the middle to capitalize the first letter: %^C = Net.jokes
 *	Put _ in the middle to capitalize last component: %_c = net/Jokes
 *
 *	~ interpretation in filename expansion happens after % expansion, so
 *	you could put ~%{NEWSLOGNAME-news} and it will expand correctly.
 */

/* *** System Dependent Stuff *** */

/* NOTE: many of these are defined in the config.h file */

/* name of organization */
#ifndef ORGNAME
#   define ORGNAME "ACME Widget Company, Widget Falls, Southern North Dakota"
#endif

#ifndef MBOXCHAR
#   define MBOXCHAR 'F'	/* how to recognize a mailbox by 1st char */
#endif

#ifndef ROOTID
#   define ROOTID 0        /* uid of superuser */
#endif

#ifdef NORMSIG
#   define sigset signal
#   define sigignore(sig) signal(sig,SIG_IGN)
#endif

#ifndef LOGDIRFIELD
#   define LOGDIRFIELD 6		/* Which field (origin 1) is the */
					/* login directory in /etc/passwd? */
					/* (If it is not kept in passwd, */
					/* but getpwnam() returns it, */
					/* define the symbol GETPWENT) */
#endif
#ifndef GCOSFIELD
#   define GCOSFIELD 5
#endif

#ifndef NEGCHAR
#   define NEGCHAR '!'
#endif

/* Space conservation section */

/* To save D space, cut down size of MAXRCLINE, NGMAX, VARYSIZE. */
#define MAXRCLINE 1000	/* number of lines allowed in .newsrc */
			/* several parallel arrays affected. */
			/* (You can have more lines in the active file, */
			/* just not in the .newsrc) */
#define HASHSIZ 1103	/* should be prime, and at least MAXRCLINE + 10% */
#define NGMAX 100	/* number of newsgroups allowed on command line */
			/* undefine ONLY symbol to disable "only" feature */
#define VARYSIZE 256	/* this makes a block 1024 bytes long in DECville */
			/* (used by virtual array routines) */

/* Undefine any of the following features to save both I and D space */
/* In general, earlier ones are easier to get along without */
/* Pdp11's without split I and D may have to undefine them all */
#define DEBUGGING	/* include debugging code */
#define CUSTOMLINES	/* include code for HIDELINE and PAGESTOP */
#define PUSHBACK	/* macros and keymaps using pushback buffer */
#define SPEEDOVERMEM	/* use more memory to run faster */
#define WORDERASE	/* enable ^W to erase a word */
#define MAILCALL	/* check periodically for mail */
#define CLEAREOL	/* use clear to end-of-line instead of clear screen */
#define NOFIREWORKS	/* keep whole screen from flashing on certain */
			/* terminals such as older Televideos */
#define VERIFY		/* echo the command they just typed */
#define HASHNG		/* hash newsgroup lines for fast lookup-- */
			/* linear search used if not defined */
#define CONDSUB		/* allow %(cond?text:text) */
#define BACKTICK	/* allow %`command` */
#define PROMPTTTY	/* allow %"prompt" */
#define ULSMARTS	/* catch _^H in text and do underlining */
#define TERMMOD		/* allow terminal type modifier on switches */
#define BAUDMOD		/* allow baudrate modifier on switches */
#define GETLOGIN	/* use getlogin() routine as backup to environment */
			/* variables USER or LOGNAME */
#define ORGFILE		/* if organization begins with /, look up in file */
#define TILDENAME	/* allow ~logname expansion */
#define SETENV		/* allow command line environment variable setting */
#define GETWD		/* use our getwd() instead of piped in pwd */
#ifndef BSD42		/* 4.2 sites should just use groups for this */
#define SETUIDGID	/* substitute eaccess() for access() so that rn */
			/* can run setuid or setgid */
			/* if not setuid or setgid, you don't need it */
#endif
#define MAKEDIR		/* use our makedir() instead of shell script */
#define MEMHELP		/* keep help messages in memory */
#define VERBOSE		/* compile in more informative messages */
#define TERSE		/* compile in shorter messages */
			/* (Note: both VERBOSE and TERSE can be defined; -t
			 * sets terse mode.  One or the other MUST be defined.
			 */
#ifndef pdp11
#   define CACHESUBJ	/* cache subject lines in memory */
			/* without this ^N still works but runs really slow */
			/* but you save lots and lots of D space */
#   define CACHEFIRST	/* keep absolute first article numbers in memory */
			/* cost: about 2k */
#endif
#define ROTATION	/* enable x, X and ^X commands to work */
#define DELBOGUS	/* ask if bogus newsgroups should be deleted */
#define RELOCATE	/* allow newsgroup rearranging */
#define ESCSUBS		/* escape substitutions in multi-character commands */
#define DELAYMARK	/* allow articles to be temporarily marked as read */
			/* until exit from current newsgroup or Y command */
#define MCHASE		/* unmark xrefed articles on m or M */
#define MUNGHEADER	/* allow alternate header formatting via */
			/* environment variable ALTHEADER (not impl) */
#define ASYNC_PARSE	/* allow parsing headers asyncronously to reading */
			/* used by MCHASE and MUNGHEADER */
#define FINDNEWNG	/* check for new newsgroups on startup */
#define FASTNEW		/* do optimizations on FINDNEWNG for faster startup */
			/* (this optimization can make occasional mistakes */
			/* if a group is removed and another group of the */
			/* same length is added, and if no softpointers are */
			/* affected by said change.) */
#define INNERSEARCH	/* search command 'g' with article */
#define CATCHUP		/* catchup command at newsgroup level */
#define NGSEARCH	/* newsgroup pattern matching */
#define ONLY		/* newsgroup restrictions by pattern */
#define KILLFILES	/* automatic article killer files */
#define ARTSEARCH	/* pattern searches among articles */
			/* /, ?, ^N, ^P, k, K */

/* some dependencies among options */

#ifndef ARTSEARCH
#   undef KILLFILES
#   undef INNERSEARCH
#   undef CACHESUBJ
#endif

#ifndef DELAYMARK
#   ifndef MCHASE
#	ifndef MUNGHEADER
#	    undef ASYNC_PARSE
#	endif
#   endif
#endif

#ifndef SETUIDGID
#   define eaccess access
#endif

#ifdef ONLY				/* idiot lint doesn't grok #if */
#   define NGSORONLY
#else
#   ifdef NGSEARCH
#	define NGSORONLY
#   endif
#endif

#ifdef VERBOSE
#   ifdef TERSE
#	define IF(c) if (c)
#	define ELSE else
#   else !TERSE
#	define IF(c)
#	define ELSE
#   endif
#else !VERBOSE
#   ifndef TERSE
#	define TERSE
#   endif
#   define IF(c) "IF" outside of VERBOSE???
#   define ELSE "ELSE" outside of VERBOSE???
#endif

#ifdef DEBUGGING
#   define assert(ex) {if (!(ex)){fprintf(stderr,"Assertion failed: file %s, line %d\n", __FILE__, __LINE__);sig_catcher(0);}}
#else
#   define assert(ex) ;
#endif

#ifdef SPEEDOVERMEM
#   define OFFSET(x) (x)
#else
#   define OFFSET(x) ((x)-absfirst)
#endif

/* If you're strapped for space use the help messages in shell scripts */
/* if {NG,ART,PAGER,SUBS}HELP is undefined, help messages are in memory */
#ifdef MEMHELP  /* undef MEMHELP above to get them all as sh scripts */
#   undef NGHELP
#   undef ARTHELP
#   undef PAGERHELP
#   undef SUBSHELP
#else
#   ifndef NGHELP			/* % and ~ */
#	define NGHELP "%X/ng.help"
#   endif
#   ifndef ARTHELP			/* % and ~ */
#	define ARTHELP "%X/art.help"
#   endif
#   ifndef PAGERHELP		/* % and ~ */
#	define PAGERHELP "%X/pager.help"
#   endif
#   ifndef SUBSHELP		/* % and ~ */
#	define SUBSHELP "%X/subs.help"
#   endif
#endif

#ifdef CLEAREOL
#   define TCSIZE 512	/* capacity for termcap strings */
#else
#   ifdef pdp11
#	define TCSIZE 256	/* capacity for termcap strings */
#   else
#	define TCSIZE 512	/* capacity for termcap srings */
#   endif
#endif

/* Additional ideas:
 *	Make the do_newsgroup() routine a separate process.
 *	Keep .newsrc on disk instead of in memory.
 *	Overlays, if you have them.
 *	Get a bigger machine.
 */

/* End of Space Conservation Section */

/* More System Dependencies */

/* news library */
#ifndef LIB		/* ~ and %l only ("~%l" is permissable) */
#   define LIB "/usr/lib/news"
#endif

/* path to private executables */
#ifndef RNLIB		/* ~, %x and %l only */
#   define RNLIB "%x/rn"
#endif

/* system-wide RNINIT switches */
#ifndef GLOBINIT
#   define GLOBINIT "%X/INIT"
#endif

/* where to find news files */
#ifndef SPOOL			/* % and ~ */
#   define SPOOL "/usr/spool/news"
#endif

/* file containing list of active newsgroups and max article numbers */
#ifndef ACTIVE			/* % and ~ */
#   define ACTIVE "%x/active"
#endif

/* location of history file */
#ifndef ARTFILE			/* % and ~ */
#    define ARTFILE "%x/history"
#endif

/* command to setup a new .newsrc */
#ifndef NEWSETUP		/* % and ~ */
#   define NEWSETUP "newsetup"
#endif

/* command to display a list of un-subscribed-to newsgroups */
#ifndef NEWSGROUPS		/* % and ~ */
#   define NEWSGROUPS "newsgroups"
#endif

/* preferred shell for use in doshell routine */
/*  ksh or sh would be okay here */
#ifndef PREFSHELL
#   define PREFSHELL "/bin/csh"
#endif

/* path to fastest starting shell */
#ifndef SH
#   define SH "/bin/sh"
#endif

/* path to default editor */
#ifndef DEFEDITOR
#   define DEFEDITOR "/usr/ucb/vi"
#endif

/* location of macro file */
#ifndef RNMACRO
#   ifdef PUSHBACK
#	define RNMACRO "%./.rnmac"
#   endif
#endif

/* location of full name */
#ifndef FULLNAMEFILE
#   ifndef PASSNAMES
#	define FULLNAMEFILE "%./.fullname"
#   endif
#endif

/* virtual array file name template */
#ifndef VARYNAME		/* % and ~ */
#   define VARYNAME "/tmp/rnvary.%$"
#endif

/* file to pass header to followup article poster */
#ifndef HEADNAME		/* % and ~ */
#   define HEADNAME "%./.rnhead"
/* or alternately #define HEADNAME "/tmp/rnhead.%$" */
#endif

#ifndef MAKEDIR
/* shell script to make n-deep subdirectories */
#   ifndef DIRMAKER		/* % and ~ */
#	define DIRMAKER "%X/makedir"
#   endif
#endif

/* location of newsrc file */
#ifndef RCNAME		/* % and ~ */
#   define RCNAME "%./.newsrc"
#endif

/* temporary newsrc file in case we crash while writing out */
#ifndef RCTNAME		/* % and ~ */
#   define RCTNAME "%./.newnewsrc"
#endif

/* newsrc file at the beginning of this session */
#ifndef RCBNAME		/* % and ~ */
#   define RCBNAME "%./.oldnewsrc"
#endif

/* if existent, contains process number of current or crashed rn */
#ifndef LOCKNAME		/* % and ~ */
#   define LOCKNAME "%./.rnlock"
#endif

/* information from last invocation of rn */
#ifndef LASTNAME		/* % and ~ */
#   define LASTNAME "%./.rnlast"
#endif

/* file with soft pointers into the active file */
#ifndef SOFTNAME		/* % and ~ */
#   define SOFTNAME "%./.rnsoft"
#endif

/* list of article numbers to mark as unread later (see M and Y cmmands) */
#ifndef RNDELNAME		/* % and ~ */
#   define RNDELNAME "%./.rndelay"
#endif

/* a motd-like file for rn */
#ifndef NEWSNEWSNAME		/* % and ~ */
#   define NEWSNEWSNAME "%X/newsnews"
#endif

/* command to send a reply */
#ifndef MAILPOSTER		/* % and ~ */
#   define MAILPOSTER "Rnmail -h %h"
#endif

#ifdef INTERNET
#   ifndef MAILHEADER		/* % */
#	ifdef CONDSUB
#	    define MAILHEADER "To: %t\nSubject: Re: %S\nNewsgroups: %n\nIn-Reply-To: %i\n%(%[references]!=^$?References\\: %[references]\n)Organization: %o\nCc: \nBcc: \n\n"
#	else
#	    define MAILHEADER "To: %t\nSubject: Re: %S\nNewsgroups: %n\nIn-Reply-To: %i\nReferences: %[references]\nCc: \nBcc: \n\n"
#	endif
#   endif
#else
#   ifndef MAILHEADER		/* % */
#	ifdef CONDSUB
#	    define MAILHEADER "To: %T\nSubject: %(%i=^$?:Re: %S\nNewsgroups: %n\nIn-Reply-To: %i)\n%(%[references]!=^$?References\\: %[references]\n)Organization: %o\nCc: \nBcc: \n\n"
#	else
#	    define MAILHEADER "To: %T\nSubject: Re: %S\nNewsgroups: %n\nIn-Reply-To: %i\nReferences: %[references]\nCc: \nBcc: \n\n"
#	endif
#   endif
#endif

#ifndef YOUSAID			/* % */
#   define YOUSAID "In article %i you write:"
#endif

/* command to submit a followup article */
#ifndef NEWSPOSTER		/* % and ~ */
#   define NEWSPOSTER "Pnews -h %h"
#endif

#ifndef NEWSHEADER		/* % */
#   ifdef CONDSUB
#	define NEWSHEADER "Newsgroups: %(%F=^$?%C:%F)\nSubject: %(%S=^$?%\"\n\nSubject: \":Re: %S)\nSummary: \nExpires: \n%(%R=^$?:References: %R\n)Sender: \nReply-To: %L@%H.UUCP (%N)\nFollowup-To: \nDistribution: %(%i=^$?%\"Distribution: \":%D)\nOrganization: %o\nKeywords: %[keywords]\n\n"
#   else
#	define NEWSHEADER "Newsgroups: %F\nSubject: Re: %S\nSummary: \nExpires: \nReferences: %R\nSender: \nReply-To: %L@%H.UUCP (%N)\nFollowup-To: \nDistribution: %D\nOrganization: %o\nKeywords: %[keywords]\n\n"
#   endif
#endif

#ifndef ATTRIBUTION		/* % */
#   define ATTRIBUTION "In article %i %f writes:"
#endif

#ifndef PIPESAVER		/* % */
#   ifdef CONDSUB
#	define PIPESAVER "%(%B=^0$?<%A:tail +%Bc %A |) %b"
#   else
#	define PIPESAVER "tail +%Bc %A | %b"
#   endif
#endif

#ifndef NORMSAVER		/* % and ~ */
#   define NORMSAVER "%X/norm.saver %A %P %c %a %B %C \"%b\""
#endif

#ifndef MBOXSAVER		/* % and ~ */
#   ifdef MININACT		/* 2.10.2 site? */
#	define MBOXSAVER "%X/mbox.saver %A %P %c %a %B %C \"%b\" \"From %T %`date`\""
#   else
#	ifdef CONDSUB
#	    define MBOXSAVER "%X/mbox.saver %A %P %c %a %B %C \"%b\" \"From %T %(%[date]=^\\(\\w*\\), \\(\\w*\\)-\\(\\w*\\)-\\(\\w*\\) \\([^ ]*\\)?%1 %3 %(%2=..?%2: %2) %5 19%4)\""
					/* header munging with a vengeance */
#	else
#	    define MBOXSAVER "%X/mbox.saver %A %P %c %a %B %C \"%b\" \"From %T %[posted]\""
#	endif
#   endif
#endif

#ifdef MKDIRS

#   ifndef SAVEDIR			/* % and ~ */
#	define SAVEDIR "%p/%c"
#   endif
#   ifndef SAVENAME		/* % */
#	define SAVENAME "%a"
#   endif

#else

#   ifndef SAVEDIR			/* % and ~ */
#	define SAVEDIR "%p"
#   endif
#   ifndef SAVENAME		/* % */
#	define SAVENAME "%^C"
#   endif

#endif

#ifndef KILLGLOBAL		/* % and ~ */
#   define KILLGLOBAL "%p/KILL"
#endif

#ifndef KILLLOCAL		/* % and ~ */
#   define KILLLOCAL "%p/%c/KILL"
#endif

/* how to cancel an article */
#ifndef CANCEL
#   ifdef MININACT			/* 2.10.2 ? */
#	define CANCEL "%x/inews -h < %h"
#   else
#	define CANCEL "inews -h < %h"
#   endif
#endif

/* how to cancel an article, continued */
#ifndef CANCELHEADER
#   define CANCELHEADER "Newsgroups: %n\nSubject: cmsg cancel %i\nReferences: %R\nReply-To: %L@%H.UUCP (%N)\nDistribution: %D\nOrganization: %o\n"
#endif

/* where to find the mail file */
#ifndef MAILFILE
#   define MAILFILE "/usr/spool/mail/%L"
#endif

/* some important types */

typedef int		NG_NUM;		/* newsgroup number */
typedef long		ART_NUM;	/* article number */
#ifdef pdp11
    typedef short	ART_UNREAD;	/* ordinarily this should be long */
					/* like ART_NUM, but assuming that */
					/* we stay less than 32767 articles */
					/* behind saves a lot of space. */
					/* NOTE: do not make unsigned. */
#else
    typedef long	ART_UNREAD;
#endif
typedef long		ART_POS;	/* char position in article file */
typedef int		ART_LINE;	/* line position in article file */
typedef short		ACT_POS;	/* char position in active file */
typedef unsigned int	MEM_SIZE;	/* for passing to malloc */

/* *** end of the machine dependent stuff *** */

/* GLOBAL THINGS */

/* file statistics area */

EXT struct stat filestat;

/* various things of type char */

char	*index();
char	*rindex();
char	*getenv();
char	*strcat();
char	*strcpy();
char	*sprintf();

EXT char buf[LBUFLEN+1];	/* general purpose line buffer */
EXT char cmd_buf[CBUFLEN];	/* buffer for formatting system commands */

EXT char *indstr INIT(">");	/* indent for old article embedded in followup */

EXT char *cwd INIT(Nullch);		/* current working directory */
EXT char *dfltcmd INIT(Nullch);	/* 1st char is default command */

/* switches */

#ifdef DEBUGGING
    EXT int debug INIT(0);				/* -D */
#   define DEB_INNERSRCH 32 
#   define DEB_FILEXP 64 
#   define DEB_HASH 128
#   define DEB_XREF_MARKER 256
#   define DEB_CTLAREA_BITMAP 512
#   define DEB_SOFT_POINTERS 1024
#   define DEB_NEWSRC_LINE 2048
#   define DEB_SEARCH_AHEAD 4096
#   define DEB_CHECKPOINTING 8192
#   define DEB_FEED_XREF 16384
#endif

#ifdef ARTSEARCH
    EXT int scanon INIT(0);				/* -S */
#endif

EXT bool mbox_always INIT(FALSE);			/* -M */
EXT bool norm_always INIT(FALSE);			/* -N */
EXT bool checkflag INIT(FALSE);			/* -c */
EXT bool suppress_cn INIT(FALSE);			/* -s */
EXT int countdown INIT(5);	/* how many lines to list before invoking -s */
EXT bool muck_up_clear INIT(FALSE);			/* -loco */
EXT bool erase_screen INIT(FALSE);			/* -e */
#ifdef CLEAREOL
EXT bool can_home_clear INIT(FALSE);		/* fancy -e -- PWP */
#endif CLEAREOL
EXT bool findlast INIT(FALSE);			/* -r */
EXT bool typeahead INIT(FALSE);			/* -T */
#ifdef VERBOSE
#   ifdef TERSE
	EXT bool verbose INIT(TRUE);			/* +t */
#   endif
#endif
#ifdef VERIFY
    EXT bool verify INIT(FALSE);			/* -v */
#endif

#define NOMARKING 0
#define STANDOUT 1
#define UNDERLINE 2
EXT int marking INIT(NOMARKING);			/* -m */

EXT ART_LINE initlines INIT(0);		/* -i */

/* miscellania */

long atol(), fseek(), ftell();
EXT bool in_ng INIT(FALSE);		/* current state of rn */
EXT char mode INIT('i');		/* current state of rn */

EXT FILE *tmpfp INIT(Nullfp);	/* scratch fp used for .rnlock, .rnlast, etc. */

EXT NG_NUM nextrcline INIT(0);	/* 1st unused slot in rcline array */
			/* startup to avoid checking twice in a row */

extern errno;

/* Factored strings */

EXT char nullstr[] INIT("");
EXT char sh[] INIT(SH);
EXT char defeditor[] INIT(DEFEDITOR);
EXT char hforhelp[] INIT("Type h for help.\n");
#ifdef STRICTCR
EXT char badcr[] INIT("\nUnnecessary CR ignored.\n");
#endif
EXT char readerr[] INIT("rn read error");
EXT char unsubto[] INIT("\n\nUnsubscribed to newsgroup %s\n");
EXT char cantopen[] INIT("Can't open %s\n");
EXT char cantcreate[] INIT("Can't create %s\n");

#ifdef VERBOSE
    EXT char nocd[] INIT("Can't chdir to directory %s\n");
#else
    EXT char nocd[] INIT("Can't find %s\n");
#endif

#ifdef NOLINEBUF
#define FLUSH ,fflush(stdout)
#else
#define FLUSH
#endif

#ifdef lint
#undef FLUSH
#define FLUSH
#undef putchar
#define putchar(c)
#endif
