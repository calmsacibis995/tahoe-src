/*
 *	$Source: /u1/X/libis/RCS/misc.c,v $
 *	$Header: misc.c,v 1.1 86/11/17 14:34:18 swick Rel $
 */

#ifndef lint
static char *rcsid_misc_c = "$Header: misc.c,v 1.1 86/11/17 14:34:18 swick Rel $";
#endif	lint

#include "is-copyright.h"

/*
 *	misc.c		miscellaneous utility functions
 *
 *	SwapShorts	swap order of bytes in shorts
 *	SwapBits	swap order of bits in bytes
 *	Overlap		determine if two rectangles overlap
 *	Intersection	return the intersection of two rectangles
 *
 *	Copyright (c) 1986, Integrated Solutions, Inc.
 */

#include "Xis.h"

#define MIN(a,b)	(((a)<(b))?(a):(b))
#define MAX(a,b)	(((a)>(b))?(a):(b))

/*
 *	bit reverse array used by bit swapping routines
 */
static unsigned char bitrev[] = {
    0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
    0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
    0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
    0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
    0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
    0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
    0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec,
    0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
    0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
    0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
    0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea,
    0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
    0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6,
    0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
    0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
    0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
    0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1,
    0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
    0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9,
    0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
    0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
    0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
    0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed,
    0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
    0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
    0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
    0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
    0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
    0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7,
    0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
    0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef,
    0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff,
};

SwapShorts(wordp, bytecnt)
short	*wordp;
int	bytecnt;
{
    register unsigned char *p = (unsigned char *)wordp;
    register int cnt = bytecnt >> 1;
    while (cnt--) {
	register unsigned char tmp = *p;
	*p = *(p+1);
	*(p+1) = tmp;
	p += sizeof(short);
    }
}

/*
 *	SwapBits - slow 'C' version
 *
 *	swap bit 0 and bit 15, swap bit 1 and bit 14, etc.
 */
SwapBits(wordp, bytecnt)
register short	*wordp;
int		bytecnt;
{
    register int cnt = bytecnt >> 1;
    while (cnt--) {
	*wordp = (bitrev[(unsigned char)((*wordp)>>8)]<<8) |
		(bitrev[(unsigned char)*wordp]);
	wordp++;
    }
}

/*
 *	Overlap
 */
int
Overlap(r1, r2)
CLIP	r1, r2;
{
    /* normalize rectangles */
    if (r1.width < 0) {
	r1.width = -r1.width;
	r1.left -= r1.width-1;
    }
    if (r1.height < 0) {
	r1.height = -r1.height;
	r1.top -= r1.height-1;
    }
    if (r2.width < 0) {
	r2.width = -r2.width;
	r2.left -= r2.width-1;
    }
    if (r2.height < 0) {
	r2.height = -r2.height;
	r2.top -= r2.height-1;
    }
    if (r1.left < r2.left) {
	if (r2.left >= r1.left + r1.width)
	    return (FALSE);
    } else if (r1.left >= r2.left + r2.width) {
	return (FALSE);
    }

    if (r1.top < r2.top) {
	if (r2.top >= r1.top + r1.height)
	    return (FALSE);
    } else if (r1.top >= r2.top + r2.height) {
	return (FALSE);
    }

    return (TRUE);
}

/*
 *	Intersection
 */
CLIP
Intersection(r1, r2)
CLIP	r1, r2;
{
    CLIP i;

    /* normalize rectangles */
    if (r1.width < 0) {
	r1.width = -r1.width;
	r1.left -= r1.width-1;
    }
    if (r1.height < 0) {
	r1.height = -r1.height;
	r1.top -= r1.height-1;
    }
    if (r2.width < 0) {
	r2.width = -r2.width;
	r2.left -= r2.width-1;
    }
    if (r2.height < 0) {
	r2.height = -r2.height;
	r2.top -= r2.height-1;
    }
    i.left	= MAX(r1.left, r2.left);
    i.top	= MAX(r1.top, r2.top);
    i.width	= MIN(r1.left+r1.width, r2.left+r2.width) - i.left;
    i.height	= MIN(r1.top+r1.height, r2.top+r2.height) - i.top;

    return (i);
}
