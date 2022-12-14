divert(10)
#
#  Sendmail
#  Copyright (c) 1983  Eric P. Allman
#  Berkeley, California
#
#  Copyright (c) 1983 Regents of the University of California.
#  All rights reserved.  The Berkeley software License Agreement
#  specifies the terms and conditions for redistribution.
#
#	@(#)nstcpm.m4	1.19 (Berkeley) 3/31/88
#
divert(0)
############################################################
############################################################
#####
#####		Arpanet TCP Mailer specification
#####
#####	Messages processed by this specification are assumed to leave
#####	the local domain -- hence, they must be canonical according to
#####	RFC822 etc.
#####
#####	This mailer is to be used with the Berkeley Name Server.
#####
############################################################
############################################################

Mtcp,	P=[IPC], F=mDFMueXLC, S=14, R=24, A=IPC $h, E=\r\n

S14

# pass <route-addr>'s through
R<@$+>$*		$@<@$[$1$]>$2			resolve <route-addr>

# map colons to dots everywhere
R$*:$*			$1.$2				map colons to dots

# output local host in user@host.BERKELEY.EDU syntax
R$-			$1<@$w>				user w/o host
R$+<@$=w>		$:$1<@$w>			this host
R$+<@$->		$:$1<@$[$2$]>			canonicalize into dom
R$+<@$->		$:$1<@$2.$D>			if nameserver fails
R$+<@$=N.$D>		$@$1<@$2.$D>			nic-reg hosts are ok
R$+<@$*.$D>		$@$1%$2.$D<@$A>			else -> u%h@gateway

# if not local, and not a "fake" domain, ask the nameserver
R$+<@$+.$~I>		$@$1<@$[$2.$3$]>		user@host.domain
R$+<@[$+]>		$@$1<@[$2]>			already ok

# output internal ("fake") domains as "user%host@relay"

R$+<@$+.CSNET>		$@$1%$2.CSNET<@relay.cs.net>	user@host.CSNET
R$+<@$+.BITNET>		$@$1%$2.BITNET<@jade.berkeley.edu> user@host.BITNET
R$+<@$+.UUCP>		$@$2!$1<@$w>			user@host.UUCP


S24

# put in <> kludge
R$*<$*>$*		$1$2$3				defocus
R$*			$:$>3$1				now canonical form

# pass <route-addr>'s through
R<@$+>$*		$@<@$[$1$]>$2			resolve <route-addr>

# map colons to dots everywhere.....
R$*:$*			$1.$2				map colons to dots

# output local host in user@host.domain syntax
R$-			$1<@$w>				user w/o host
R$+<@$=w>		$:$1<@$w>			this host
R$+<@$->		$:$1<@$[$2$]>			canonicalize into dom
R$+<@$->		$:$1<@$2.$D>			if nameserver fails
R$+<@$=N.$D>		$@$1<@$2.$D>			nic-reg hosts are ok
R$+<@$*.$D>		$@$1%$2.$D<@$A>			else -> u%h@gateway

# if not local, and not a "fake" domain, ask the nameserver
R$+<@$+.$~I>		$@$1<@$[$2.$3$]>		user@host.domain
R$+<@[$+]>		$@$1<@[$2]>			already ok

# Hide fake domains behind gateways

R$+<@$+.CSNET>		$@$1%$2.CSNET<@relay.cs.net>	user@host.CSNET
R$+<@$+.BITNET>		$@$1<@$2.BITNET>		user@host.BITNET
R$+<@$+.UUCP>		$@$2!$1				user@host.UUCP

