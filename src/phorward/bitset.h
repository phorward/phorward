/* -HEADER----------------------------------------------------------------------
Phorward Foundation Libraries :: Base Library
Copyright (C) 2006-2012 by Phorward Software Technologies, Jan Max Meyer
http://www.phorward-software.com ++ contact<at>phorward<dash>software<dot>com
All rights reserved. See $PHOME/LICENSE for more information.

File:	bitset.h
Author:	Jan Max Meyer
Usage:	Bitset library header
----------------------------------------------------------------------------- */

#ifndef BITSET_H
#define BITSET_H

/* Typedefs */
typedef uchar byte;
typedef byte* bitset;

/* Macros */
#define bitset_free( set ) 		free( set )

#endif
