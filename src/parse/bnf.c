/* -MODULE----------------------------------------------------------------------
Phorward Foundation Toolkit
Copyright (C) 2006-2015 by Phorward Software Technologies, Jan Max Meyer
http://www.phorward-software.com ++ contact<at>phorward<dash>software<dot>com
All rights reserved. See LICENSE for more information.

File:	bnf.c
Usage:	Self-hosted grammar for ppgram, generated from bnf.syn
----------------------------------------------------------------------------- */

/* DO NOT CHANGE THIS FILE MANUALLY. IT WILL GO AWAY! */

#include "phorward.h"

void pp_bnf_define( ppgram* g )
{
	ppsym*	sym[ 66 ];

	/* Symbols */

	sym[ 1 ] = pp_sym_create( g, PPSYMTYPE_REGEX, (char*)NULL, "[\\t\\n\\r ]+" );
	sym[ 1 ]->flags |= PPFLAG_WHITESPACE;

	sym[ 2 ] = pp_sym_create( g, PPSYMTYPE_REGEX, (char*)NULL, "//.*\\n" );
	sym[ 2 ]->flags |= PPFLAG_WHITESPACE;

	sym[ 3 ] = pp_sym_create( g, PPSYMTYPE_REGEX, "ccl", "'.*'" );
	sym[ 3 ]->emit = 1;

	sym[ 4 ] = pp_sym_create( g, PPSYMTYPE_REGEX, "string", "\".*\"" );
	sym[ 4 ]->emit = 2;

	sym[ 5 ] = pp_sym_create( g, PPSYMTYPE_REGEX, "regex", "/(\\\\.|[^/\\\\])*/" );
	sym[ 5 ]->emit = 3;

	sym[ 6 ] = pp_sym_create( g, PPSYMTYPE_REGEX, "ident", "[A-Z_a-z][0-9A-Z_a-z]*" );
	sym[ 6 ]->emit = 10;

	sym[ 7 ] = pp_sym_create( g, PPSYMTYPE_REGEX, "int", "[0-9]+" );
	sym[ 7 ]->emit = 11;

	sym[ 8 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "symbol", (char*)NULL );
	sym[ 8 ]->emit = 20;

	sym[ 9 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "inline", (char*)NULL );
	sym[ 9 ]->emit = 32;

	sym[ 10 ] = pp_sym_create( g, PPSYMTYPE_CCL, (char*)NULL, "(" );

	sym[ 11 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "alternation", (char*)NULL );

	sym[ 12 ] = pp_sym_create( g, PPSYMTYPE_CCL, (char*)NULL, ")" );

	sym[ 13 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "mod_kleene", (char*)NULL );
	sym[ 13 ]->emit = 25;

	sym[ 14 ] = pp_sym_create( g, PPSYMTYPE_CCL, (char*)NULL, "*" );

	sym[ 15 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "mod_positive", (char*)NULL );
	sym[ 15 ]->emit = 26;

	sym[ 16 ] = pp_sym_create( g, PPSYMTYPE_CCL, (char*)NULL, "+" );

	sym[ 17 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "mod_optional", (char*)NULL );
	sym[ 17 ]->emit = 27;

	sym[ 18 ] = pp_sym_create( g, PPSYMTYPE_CCL, (char*)NULL, "?" );

	sym[ 19 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "modifier", (char*)NULL );

	sym[ 20 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "sequence", (char*)NULL );

	sym[ 21 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "production", (char*)NULL );

	sym[ 22 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "emit", (char*)NULL );
	sym[ 22 ]->emit = 42;

	sym[ 23 ] = pp_sym_create( g, PPSYMTYPE_STRING, (char*)NULL, "emit" );

	sym[ 24 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "int?", (char*)NULL );

	sym[ 25 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "flag", (char*)NULL );
	sym[ 25 ]->emit = 40;

	sym[ 26 ] = pp_sym_create( g, PPSYMTYPE_STRING, (char*)NULL, "noemit" );

	sym[ 27 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "emitflag", (char*)NULL );

	sym[ 28 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "flags", (char*)NULL );

	sym[ 29 ] = pp_sym_create( g, PPSYMTYPE_CCL, (char*)NULL, "%" );

	sym[ 30 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "emitflag+", (char*)NULL );

	sym[ 31 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "alternative", (char*)NULL );
	sym[ 31 ]->emit = 30;

	sym[ 32 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "flags?", (char*)NULL );

	sym[ 33 ] = pp_sym_create( g, PPSYMTYPE_CCL, (char*)NULL, "|" );

	sym[ 34 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "nontermflag", (char*)NULL );
	sym[ 34 ]->emit = 40;

	sym[ 35 ] = pp_sym_create( g, PPSYMTYPE_STRING, (char*)NULL, "goal" );

	sym[ 36 ] = pp_sym_create( g, PPSYMTYPE_STRING, (char*)NULL, "lexeme" );

	sym[ 37 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "nontermemitflag", (char*)NULL );

	sym[ 38 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "nontermflags", (char*)NULL );

	sym[ 39 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "nontermemitflag+", (char*)NULL );

	sym[ 40 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "nontermdef", (char*)NULL );
	sym[ 40 ]->emit = 31;

	sym[ 41 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "nontermflags?", (char*)NULL );

	sym[ 42 ] = pp_sym_create( g, PPSYMTYPE_CCL, (char*)NULL, ":" );

	sym[ 43 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "nontermdef'", (char*)NULL );

	sym[ 44 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "nontermdef'?", (char*)NULL );

	sym[ 45 ] = pp_sym_create( g, PPSYMTYPE_CCL, (char*)NULL, ";" );

	sym[ 46 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "termflag", (char*)NULL );
	sym[ 46 ]->emit = 40;

	sym[ 47 ] = pp_sym_create( g, PPSYMTYPE_STRING, (char*)NULL, "ignore" );

	sym[ 48 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "termemitflag", (char*)NULL );

	sym[ 49 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "termflags", (char*)NULL );

	sym[ 50 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "termemitflag+", (char*)NULL );

	sym[ 51 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "termdef", (char*)NULL );
	sym[ 51 ]->emit = 35;

	sym[ 52 ] = pp_sym_create( g, PPSYMTYPE_CCL, (char*)NULL, "$" );

	sym[ 53 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "ident?", (char*)NULL );

	sym[ 54 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "termdef'", (char*)NULL );

	sym[ 55 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "termflags?", (char*)NULL );

	sym[ 56 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "gflag", (char*)NULL );
	sym[ 56 ]->emit = 41;

	sym[ 57 ] = pp_sym_create( g, PPSYMTYPE_STRING, (char*)NULL, "emitall" );

	sym[ 58 ] = pp_sym_create( g, PPSYMTYPE_STRING, (char*)NULL, "emitnone" );

	sym[ 59 ] = pp_sym_create( g, PPSYMTYPE_STRING, (char*)NULL, "lrec" );

	sym[ 60 ] = pp_sym_create( g, PPSYMTYPE_STRING, (char*)NULL, "rrec" );

	sym[ 61 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "gflags", (char*)NULL );

	sym[ 62 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "gflag+", (char*)NULL );

	sym[ 63 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "definition", (char*)NULL );

	sym[ 64 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "grammar", (char*)NULL );
	g->goal = sym[ 64 ];

	sym[ 65 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "definition+", (char*)NULL );


	/* Productions */

	pp_prod_create( g, sym[ 8 ] /* symbol */,
		sym[ 9 ], /* inline */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 8 ] /* symbol */,
		sym[ 5 ], /* /\/(\\\\.|[^\/\\\\])*\// */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 8 ] /* symbol */,
		sym[ 4 ], /* /".*"/ */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 8 ] /* symbol */,
		sym[ 3 ], /* /'.*'/ */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 8 ] /* symbol */,
		sym[ 6 ], /* /[A-Z_a-z][0-9A-Z_a-z]*\/ */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 9 ] /* inline */,
		sym[ 10 ], /* '(' */
		sym[ 11 ], /* alternation */
		sym[ 12 ], /* ')' */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 13 ] /* mod_kleene */,
		sym[ 8 ], /* symbol */
		sym[ 14 ], /* '*' */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 15 ] /* mod_positive */,
		sym[ 8 ], /* symbol */
		sym[ 16 ], /* '+' */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 17 ] /* mod_optional */,
		sym[ 8 ], /* symbol */
		sym[ 18 ], /* '?' */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 19 ] /* modifier */,
		sym[ 8 ], /* symbol */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 19 ] /* modifier */,
		sym[ 17 ], /* mod_optional */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 19 ] /* modifier */,
		sym[ 15 ], /* mod_positive */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 19 ] /* modifier */,
		sym[ 13 ], /* mod_kleene */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 20 ] /* sequence */,
		sym[ 19 ], /* modifier */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 20 ] /* sequence */,
		sym[ 20 ], /* sequence */
		sym[ 19 ], /* modifier */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 21 ] /* production */,
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 21 ] /* production */,
		sym[ 20 ], /* sequence */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 24 ] /* int? */,
		sym[ 7 ], /* /[0-9]+/ */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 24 ] /* int? */,
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 22 ] /* emit */,
		sym[ 23 ], /* "emit" */
		sym[ 24 ], /* int? */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 25 ] /* flag */,
		sym[ 26 ], /* "noemit" */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 27 ] /* emitflag */,
		sym[ 25 ], /* flag */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 27 ] /* emitflag */,
		sym[ 22 ], /* emit */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 30 ] /* emitflag+ */,
		sym[ 30 ], /* emitflag+ */
		sym[ 27 ], /* emitflag */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 30 ] /* emitflag+ */,
		sym[ 27 ], /* emitflag */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 28 ] /* flags */,
		sym[ 29 ], /* '%' */
		sym[ 30 ], /* emitflag+ */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 28 ] /* flags */,
		sym[ 28 ], /* flags */
		sym[ 29 ], /* '%' */
		sym[ 30 ], /* emitflag+ */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 32 ] /* flags? */,
		sym[ 28 ], /* flags */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 32 ] /* flags? */,
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 31 ] /* alternative */,
		sym[ 21 ], /* production */
		sym[ 32 ], /* flags? */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 11 ] /* alternation */,
		sym[ 31 ], /* alternative */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 11 ] /* alternation */,
		sym[ 11 ], /* alternation */
		sym[ 33 ], /* '|' */
		sym[ 31 ], /* alternative */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 34 ] /* nontermflag */,
		sym[ 36 ], /* "lexeme" */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 34 ] /* nontermflag */,
		sym[ 35 ], /* "goal" */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 34 ] /* nontermflag */,
		sym[ 26 ], /* "noemit" */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 37 ] /* nontermemitflag */,
		sym[ 22 ], /* emit */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 37 ] /* nontermemitflag */,
		sym[ 34 ], /* nontermflag */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 39 ] /* nontermemitflag+ */,
		sym[ 39 ], /* nontermemitflag+ */
		sym[ 37 ], /* nontermemitflag */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 39 ] /* nontermemitflag+ */,
		sym[ 37 ], /* nontermemitflag */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 38 ] /* nontermflags */,
		sym[ 29 ], /* '%' */
		sym[ 39 ], /* nontermemitflag+ */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 38 ] /* nontermflags */,
		sym[ 38 ], /* nontermflags */
		sym[ 29 ], /* '%' */
		sym[ 39 ], /* nontermemitflag+ */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 41 ] /* nontermflags? */,
		sym[ 38 ], /* nontermflags */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 41 ] /* nontermflags? */,
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 43 ] /* nontermdef' */,
		sym[ 42 ], /* ':' */
		sym[ 11 ], /* alternation */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 44 ] /* nontermdef'? */,
		sym[ 43 ], /* nontermdef' */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 44 ] /* nontermdef'? */,
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 40 ] /* nontermdef */,
		sym[ 6 ], /* /[A-Z_a-z][0-9A-Z_a-z]*\/ */
		sym[ 41 ], /* nontermflags? */
		sym[ 44 ], /* nontermdef'? */
		sym[ 45 ], /* ';' */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 46 ] /* termflag */,
		sym[ 47 ], /* "ignore" */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 46 ] /* termflag */,
		sym[ 26 ], /* "noemit" */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 48 ] /* termemitflag */,
		sym[ 22 ], /* emit */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 48 ] /* termemitflag */,
		sym[ 46 ], /* termflag */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 50 ] /* termemitflag+ */,
		sym[ 50 ], /* termemitflag+ */
		sym[ 48 ], /* termemitflag */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 50 ] /* termemitflag+ */,
		sym[ 48 ], /* termemitflag */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 49 ] /* termflags */,
		sym[ 29 ], /* '%' */
		sym[ 50 ], /* termemitflag+ */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 49 ] /* termflags */,
		sym[ 49 ], /* termflags */
		sym[ 29 ], /* '%' */
		sym[ 50 ], /* termemitflag+ */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 53 ] /* ident? */,
		sym[ 6 ], /* /[A-Z_a-z][0-9A-Z_a-z]*\/ */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 53 ] /* ident? */,
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 54 ] /* termdef' */,
		sym[ 5 ], /* /\/(\\\\.|[^\/\\\\])*\// */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 54 ] /* termdef' */,
		sym[ 4 ], /* /".*"/ */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 54 ] /* termdef' */,
		sym[ 3 ], /* /'.*'/ */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 55 ] /* termflags? */,
		sym[ 49 ], /* termflags */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 55 ] /* termflags? */,
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 51 ] /* termdef */,
		sym[ 52 ], /* '$' */
		sym[ 53 ], /* ident? */
		sym[ 54 ], /* termdef' */
		sym[ 55 ], /* termflags? */
		sym[ 45 ], /* ';' */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 56 ] /* gflag */,
		sym[ 60 ], /* "rrec" */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 56 ] /* gflag */,
		sym[ 59 ], /* "lrec" */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 56 ] /* gflag */,
		sym[ 58 ], /* "emitnone" */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 56 ] /* gflag */,
		sym[ 57 ], /* "emitall" */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 62 ] /* gflag+ */,
		sym[ 62 ], /* gflag+ */
		sym[ 56 ], /* gflag */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 62 ] /* gflag+ */,
		sym[ 56 ], /* gflag */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 61 ] /* gflags */,
		sym[ 29 ], /* '%' */
		sym[ 62 ], /* gflag+ */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 61 ] /* gflags */,
		sym[ 61 ], /* gflags */
		sym[ 29 ], /* '%' */
		sym[ 62 ], /* gflag+ */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 63 ] /* definition */,
		sym[ 61 ], /* gflags */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 63 ] /* definition */,
		sym[ 51 ], /* termdef */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 63 ] /* definition */,
		sym[ 40 ], /* nontermdef */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 65 ] /* definition+ */,
		sym[ 65 ], /* definition+ */
		sym[ 63 ], /* definition */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 65 ] /* definition+ */,
		sym[ 63 ], /* definition */
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 64 ] /* grammar */,
		sym[ 65 ], /* definition+ */
		(ppsym*)NULL );


}
