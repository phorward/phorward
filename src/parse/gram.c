/* -MODULE----------------------------------------------------------------------
Phorward Foundation Toolkit
Copyright (C) 2006-2016 by Phorward Software Technologies, Jan Max Meyer
http://www.phorward-software.com ++ contact<at>phorward<dash>software<dot>com
All rights reserved. See LICENSE for more information.

File:	gram.c
Usage:	Grammar-specific stuff.
		THIS SOURCE IS UNDER DEVELOPMENT AND EXPERIMENTAL.
----------------------------------------------------------------------------- */

#include "phorward.h"

#define NAMELEN			80
#define DERIVCHAR		'\''

#define T_CCL			PPSYMTYPE_CCL
#define T_STRING		PPSYMTYPE_STRING
#define T_REGEX			PPSYMTYPE_REGEX
#define T_TOKEN			9

#define T_IDENT			10
#define T_INT			11
#define T_FLOAT			12

#define T_FUNCTION		15

#define T_SYMBOL		20

#define T_KLEENE		25
#define T_POSITIVE		26
#define T_OPTIONAL		27

#define T_PRODUCTION	30
#define T_NONTERMDEF	31
#define T_INLINE		32

#define T_TERMDEF		35

#define T_FLAG			40
#define T_GFLAG			41
#define T_EMIT			42
#define T_SEMIT			43

static pboolean traverse_production( ppgram* g, ppsym* lhs, ppast* node,
										pboolean emitall, int* emit_seq );


/* Derive name from basename */
static char* derive_name( ppgram* g, char* base )
{
	int             i;
	static
	char    deriv   [ ( NAMELEN * 2 ) + 1 ];

	sprintf( deriv, "%s%c", base, DERIVCHAR );

	for( i = 0; strlen( deriv ) < ( NAMELEN * 2 ); i++ )
	{
		if( !pp_sym_get_by_name( g, deriv ) )
			return deriv;

		sprintf( deriv + strlen( deriv ), "%c", DERIVCHAR );
	}

	return (char*)NULL;
}

static ppsym* traverse_symbol( ppgram* g, ppsym* lhs, ppast* node,
									pboolean emitall, int* emit_seq )
{
	ppsym*		sym			= (ppsym*)NULL;
	ppast*		child;
	int			type;
	char		name		[ NAMELEN * 2 + 1 ];
	pboolean	emit		= FALSE;

	sprintf( name, "%.*s", node->length, node->start );

	switch( ( type = node->emit ) )
	{
		case T_IDENT:
			if( !( sym = pp_sym_get_by_name( g, name ) ) )
				sym = pp_sym_create( g, PPSYMTYPE_NONTERM, name, (char*)NULL );

			break;

		case T_TOKEN:
			emit = TRUE;
			type = PPSYMTYPE_STRING;
			/* NO break! */

		case T_CCL:
		case T_STRING:
		case T_REGEX:
			name[ pstrlen( name ) - 1 ] = '\0';

			sym = pp_sym_create( g, type, (char*)NULL, name + 1 );

			/* printf( "%d >%s<\n", type, sym->name ); */

			sym->flags |= PPFLAG_DEFINED;

			if( emit )
				sym->emit = ++(*emit_seq);

			break;

		case T_INLINE:
			sym = pp_sym_create( g, PPSYMTYPE_NONTERM,
									derive_name( g, lhs->name ),
										(char*)NULL );
			sym->flags |= PPFLAG_DEFINED;

			for( child = node->child; child; child = child->next )
				if( !traverse_production( g, sym, child->child,
											emitall, emit_seq ) )
					return (ppsym*)NULL;

			break;

		default:
			printf("%d\n", type );
			MISSINGCASE;
			break;
	}

	if( sym )
		sym->flags |= PPFLAG_CALLED;

	return sym;
}


static pboolean traverse_production( ppgram* g, ppsym* lhs, ppast* node,
										pboolean emitall, int* emit_seq )
{
	ppsym*		sym;
	ppsym*		csym;
	ppprod*		prod;
	ppast*		child;
	char*		str;
	char		name		[ NAMELEN * 2 + 1 ];
	char*		semit		= (char*)NULL;
	int			emit_id		= 0;
	pboolean	emit;

	prod = pp_prod_create( g, lhs, (ppsym*)NULL );

	for( ; node; node = node->next )
	{
		switch( node->emit )
		{
			case T_FLAG:
				if( strcmp( name, "noemit" ) == 0 )
					emit = FALSE;

				break;

			case T_EMIT:
				emit = TRUE;

				if( node->child && node->child->emit == T_INT )
					emit_id = atoi( node->child->start );
				else if( node->child && node->child->emit == T_IDENT )
					semit = pstrndup( node->child->start,
										node->child->length );
				break;

			case T_KLEENE:
			case T_POSITIVE:
			case T_OPTIONAL:
				printf("closure\n" );

				sym = traverse_symbol( g, lhs, node->child->child,
										emitall, emit_seq );
				str = sym->name;

				if( node->emit == T_KLEENE || node->emit == T_POSITIVE )
				{
					sprintf( name, "%s%c", str, PPMOD_POSITIVE );

					if( !( csym = pp_sym_get_by_name( g, name ) ) )
					{
						csym = pp_sym_create( g, PPSYMTYPE_NONTERM,
													name, (char*)NULL );

						if( g->flags & PPFLAG_PREVENTLREC )
							pp_prod_create( g, csym, sym, csym, (ppsym*)NULL );
						else
							pp_prod_create( g, csym, csym, sym, (ppsym*)NULL );

						pp_prod_create( g, csym, sym, (ppsym*)NULL );
					}

					sym = csym;
				}

				if( node->emit == T_OPTIONAL || node->emit == T_KLEENE )
				{
					sprintf( name, "%s%c", str, PPMOD_OPTIONAL );

					if( !( csym = pp_sym_get_by_name( g, name ) ) )
					{
						csym = pp_sym_create( g, PPSYMTYPE_NONTERM,
														name, (char*)NULL );

						pp_prod_create( g, csym, sym, (ppsym*)NULL );
						pp_prod_create( g, csym, (ppsym*)NULL );
					}

					sym = csym;
				}

				pp_prod_append( prod, sym );
				break;

			case T_SYMBOL:
				if( !( sym = traverse_symbol( g, lhs, node->child,
												emitall, emit_seq ) ) )
					return FALSE;

				pp_prod_append( prod, sym );
				break;
		}

	}

	if( emit )
	{
		if( emit_id )
		{
			prod->emit = emit_id;

			if( emit_id > *emit_seq )
				*emit_seq = emit_id;
		}
		else if( !emitall || semit )
			prod->emit = ++(*emit_seq);

		if( semit )
			prod->semit = semit;
	}

	return TRUE;
}

static pboolean ast_to_gram( ppgram* g, ppast* ast )
{
	ppsym*		sym;
	ppsym*		nonterm		= (ppsym*)NULL;
	ppast* 		node;
	ppast*		child;
	char		name		[ NAMELEN * 2 + 1 ];
	char		def			[ NAMELEN * 2 + 1 ];
	int			emit_seq	= 0;
	pboolean	emitall		= FALSE;
	char*		semit;
	int			emit_id;
	pboolean	emit;
	pboolean	ignore;

	for( node = ast; node; node = node->next )
	{
		emit_id = 0;
		semit = (char*)NULL;
		emit = emitall;
		ignore = FALSE;

		switch( node->emit )
		{
			case T_GFLAG:
				fprintf( stderr, "GFLAG >%.*s<\n", node->length, node->start );
				if( !strncmp( node->start, "emitall", node->length ) )
					emitall = TRUE;
				else if( !strncmp( node->start, "emitnone", node->length ) )
					emitall = FALSE;
				else if( !strncmp( node->start, "lrec", node->length ) )
					g->flags &= ~PPFLAG_PREVENTLREC;
				else if( !strncmp( node->start, "rrec", node->length ) )
					g->flags |= PPFLAG_PREVENTLREC;

				break;

			case T_NONTERMDEF:
				sprintf( name, "%.*s", node->child->length,
											node->child->start );

				if( !( nonterm = sym = pp_sym_get_by_name( g, name ) ) )
					nonterm = sym = pp_sym_create( g, PPSYMTYPE_NONTERM,
													name, (char*)NULL );

				sym->flags |= PPFLAG_DEFINED;

				for( child = node->child->next; child; child = child->next )
				{
					switch( child->emit )
					{
						case T_PRODUCTION:
							if( !traverse_production( g, sym, child->child,
														emitall, &emit_seq ) )
								return FALSE;

						case T_EMIT:
							emit = TRUE;

							if( child->child && child->child->emit == T_INT )
								emit_id = atoi( child->child->start );
							else if( child->child
										&& child->child->emit == T_IDENT )
								semit = pstrndup( child->child->start,
													child->child->length );

							break;

						case T_FLAG:
							sprintf( name, "%.*s",
								child->length, child->start );

							if( strcmp( name, "goal" ) == 0 )
							{
								if( !g->goal ) /* fixme */
								{
									g->goal = sym;
									sym->flags |= PPFLAG_CALLED;
								}
							}
							else if( strcmp( name, "noemit" ) == 0 )
								emit = FALSE;
							else if( strcmp( name, "ignore" ) == 0 )
								ignore = TRUE;
							else if( strcmp( name, "lexeme" ) == 0 )
								sym->flags |= PPFLAG_LEXEM;

							break;
					}
				}

				if( emit )
				{
					if( emit_id )
					{
						sym->emit = emit_id;

						if( emit_id > emit_seq )
							emit_seq = emit_id;
					}
					else
						sym->emit = ++emit_seq;

					if( semit )
						sym->semit = semit;
				}

				break;

			case T_TERMDEF:
				child = node->child;

				if( child->emit == T_IDENT )
				{
					sprintf( name, "%.*s", child->length, child->start );
					child = child->next;
				}
				else
					*name = '\0';

				sprintf( def, "%.*s", child->length, child->start );

				sym = pp_sym_create( g, PPSYMTYPE_NONTERM,
										*name ? name : (char*)NULL, def );

				sym->flags |= PPFLAG_DEFINED;

				for( child = child->next; child; child = child->next )
				{
					switch( child->emit )
					{
						case T_EMIT:
							emit = TRUE;

							if( child->child && child->child->emit == T_INT )
								emit_id = atoi( child->child->start );
							else if( child->child
										&& child->child->emit == T_IDENT )
								semit = pstrndup( child->child->start,
													child->child->length );
							break;

						case T_FLAG:
							sprintf( name, "%.*s",
										child->length, child->start );

							if( strcmp( name, "noemit" ) == 0 )
								emit = FALSE;
							else if( strcmp( name, "ignore" ) == 0
										|| strcmp( name, "skip" ) == 0 )
								ignore = TRUE;

							break;

						default:
							MISSINGCASE;
							break;
					}
				}

				if( emit )
				{
					if( emit_id )
					{
						sym->emit = emit_id;

						if( emit_id > emit_seq )
							emit_seq = emit_id;
					}
					else
						sym->emit = ++emit_seq;

					if( semit )
						sym->semit = semit;
				}

				break;

		}
	}

	/* If there is no goal, then the last defined nonterm becomes goal symbol */
	if( !g->goal )
		g->goal = nonterm;

	/* Look for unique goal sequence */
	if( plist_count( g->goal->prods ) > 1 )
	{
		nonterm = pp_sym_create( g, PPSYMTYPE_NONTERM,
						derive_name( g, g->goal->name ), (char*)NULL );

		pp_prod_create( g, nonterm, g->goal, (ppsym*)NULL );
		g->goal = nonterm;
	}

	pp_gram_print( g );

	return FALSE;
}


/** Prepares the grammar //g// by computing all necessary stuff required for
runtime and parser generator.

The preparation process includes:
- Setting up final symbol and productions IDs
- Nonterminals FIRST-set computation
- Marking of left-recursions
- The 'lexem'-flag pull-trough the grammar.
-

This function is only run internally.
Don't call it if you're unsure ;)... */
pboolean pp_gram_prepare( ppgram* g )
{
	plistel*	e;
	plistel*	er;
	plistel*	ep;
	ppprod*		p;
	ppprod*		cp;
	ppsym*		s;
	pboolean	nullable;
	plist*		call;
	plist*		done;
	int			id;
	int			cnt;
	int			pcnt;

	if( !g )
	{
		WRONGPARAM;
		return FALSE;
	}

	if( !g->goal )
	{
		/* No such goal! */
		return FALSE;
	}

	/* Redefine list of whitespace symbols */
	plist_erase( g->ws );

	/* Set ID values for symbols and productions */
	for( id = 0, e = plist_first( g->symbols ); e; e = plist_next( e ), id++ )
	{
		s = (ppsym*)plist_access( e );
		s->id = id;

		if( s->type == PPSYMTYPE_NONTERM )
		{
			/* Erase first sets */
			plist_erase( s->first );

			/* Turn called but undefined nonterminals into string symbols */
			if( s->flags & PPFLAG_CALLED
				&& !( s->flags & PPFLAG_DEFINED )
					&& plist_count( s->prods ) == 0 )
			{
				s->type = PPSYMTYPE_STRING;

				s->str = pstrdup( s->name );
				s->flags |= PPFLAG_NAMELESS;

				s->prods = plist_free( s->prods );
				plist_push( s->first, s );
			}
		}

		if( s->flags & PPFLAG_WHITESPACE )
			plist_push( g->ws, s );
	}

	for( id = 0, e = plist_first( g->prods ); e; e = plist_next( e ), id++ )
	{
		p = (ppprod*)plist_access( e );
		p->id = id;

		if( !p->emit )
			p->emit = p->lhs->emit;
	}

	/* Compute FIRST sets and mark left-recursions */
	cnt = 0;
	call = plist_create( 0, PLIST_MOD_PTR | PLIST_MOD_RECYCLE );
	done = plist_create( 0, PLIST_MOD_PTR | PLIST_MOD_RECYCLE );

	do
	{
		pcnt = cnt;
		cnt = 0;

		plist_for( g->prods, e )
		{
			cp = (ppprod*)plist_access( e );
			plist_push( call, cp );

			while( plist_pop( call, &p ) )
			{
				plist_push( done, p );

				plist_for( p->rhs, er )
				{
					s = (ppsym*)plist_access( er );

					nullable = FALSE;

					if( s->type == PPSYMTYPE_NONTERM )
					{
						/* Union first set */
						plist_union( cp->lhs->first, s->first );

						/* Put prods on stack */
						plist_for( s->prods, ep )
						{
							p = (ppprod*)plist_access( ep );

							if( plist_count( p->rhs ) == 0 )
							{
								nullable = TRUE;
								continue;
							}

							if( p == cp )
							{
								p->lhs->flags |= PPFLAG_LEFTREC;
								p->flags |= PPFLAG_LEFTREC;
							}
							else if( !plist_get_by_ptr( done, p ) )
								plist_push( call, p );
						}
					}
					/* Extend first set if required */
					else if( !plist_get_by_ptr( cp->lhs->first, s ) )
						plist_push( cp->lhs->first, s );

					if( !nullable )
						break;
				}

				/* Flag nullable */
				if( !er )
				{
					cp->flags |= PPFLAG_NULLABLE;
					cp->lhs->flags |= PPFLAG_NULLABLE;
				}

				cnt += plist_count( cp->lhs->first );
			}

			plist_erase( done );
		}
	}
	while( pcnt < cnt );

	plist_clear( call );
	plist_clear( done );

	/* Pull-trough all lexem symbols */
	plist_for( g->symbols, e )
	{
		s = (ppsym*)plist_access( e );

		if( s->type != PPSYMTYPE_NONTERM
				|| !( s->flags & PPFLAG_LEXEM ) )
			continue;

		plist_push( call, s );
	}

	while( plist_pop( call, &s ) )
	{
		plist_push( done, s );

		plist_for( s->prods, e )
		{
			p = (ppprod*)plist_access( e );
			plist_for( p->rhs, er )
			{
				s = (ppsym*)plist_access( er );
				s->flags |= PPFLAG_LEXEM;

				if( s->type == PPSYMTYPE_NONTERM )
				{
					if( !plist_get_by_ptr( done, s )
						&& !plist_get_by_ptr( call, s ) )
						plist_push( call, s );
				}
			}
		}
	}

	/* Clear all lists */
	plist_free( call );
	plist_free( done );

	return TRUE;
}

/** Creates a new ppgram-object. */
ppgram* pp_gram_create( void )
{
	ppsym*		s;
	ppgram*		g;

	/* Setup grammar description */
	g = (ppgram*)pmalloc( sizeof( ppgram ) );

	g->symbols = plist_create( sizeof( ppsym ), PLIST_MOD_RECYCLE
													| PLIST_MOD_EXTKEYS
														| PLIST_MOD_UNIQUE );
	g->prods = plist_create( sizeof( ppprod ), PLIST_MOD_RECYCLE );

	g->ws = plist_create( sizeof( ppsym* ), PLIST_MOD_PTR );
	g->eof = pp_sym_create( g, PPSYMTYPE_SPECIAL, "eof", (char*)NULL );

	return g;
}

/** Compiles a grammar definition into a grammar.

//g// is the grammar that receives the result of the parse.
//bnf// is the BNF definition string that defines the grammar.
*/
pboolean pp_gram_from_bnf( ppgram* g, char* bnf )
{
	ppgram*		bnfgram;
	char*		s = bnf;
	char*		e;
	ppast*		ast;

	if( !( g && bnf ) )
	{
		WRONGPARAM;
		return FALSE;
	}

	/* Define grammar for BNF */
	bnfgram = pp_gram_create();
	pp_bnf_define( bnfgram );
	pp_gram_prepare( bnfgram );

	if( !pp_lr_parse( &ast, bnfgram, s, &e ) )
	{
		pp_gram_free( bnfgram );
		return FALSE;
	}

	fprintf(stderr, "I AM HERE\n" );
	pp_ast_printnew( ast );

	/* pp_ast_simplify( a ); */

	if( !ast_to_gram( g, ast ) )
		return FALSE;

	pp_gram_free( bnfgram );
	pp_ast_free( ast );

	return TRUE;
}

/** Dumps the grammar //g// to stdout. */
void pp_gram_print( ppgram* g )
{
	plistel*	e;
	plistel*	f;

	ppprod*		p;
	ppsym*		s;
	int			maxlhslen	= 0;

	plist_for( g->symbols, e )
	{
		s = (ppsym*)plist_access( e );
		if( s->type == PPSYMTYPE_NONTERM && pstrlen( s->name ) > maxlhslen )
			maxlhslen = pstrlen( s->name );
	}

	plist_for( g->prods, e )
	{
		p = (ppprod*)plist_access( e );
		printf( "%2d %2d %s%s%s%s%s %-*s : ",
			p->lhs->emit,
			p->emit,
			g->goal == p->lhs ? "G" : " ",
			p->flags & PPFLAG_LEFTREC ? "L" : " ",
			p->flags & PPFLAG_NULLABLE ? "N" : " ",
			p->lhs->flags & PPFLAG_LEXEM ? "X" : " ",
			p->lhs->flags & PPFLAG_WHITESPACE ? "W" : " ",
			maxlhslen, p->lhs->name );

		plist_for( p->rhs, f )
		{
			s = (ppsym*)plist_access( f );

			if( f != plist_first( p->rhs ) )
				printf( " " );

			printf( "%s", pp_sym_to_str( s ) );
		}

		printf( "\n" );
	}

	printf( "\n" );

	plist_for( g->symbols, e )
	{
		s = (ppsym*)plist_access( e );
		if( s->type != PPSYMTYPE_NONTERM )
			continue;

		printf( "FIRST %-*s {", maxlhslen, s->name );
		plist_for( s->first, f )
		{
			s = (ppsym*)plist_access( f );
			printf( " " );
			printf( "%s", pp_sym_to_str( s ) );
		}

		printf( " }\n" );
	}
}

/** Frees grammar //g// and all its related memory. */
ppgram* pp_gram_free( ppgram* g )
{
	plistel*	e;
	ppsym*		s;
	ppprod*		p;

	if( !g )
		return (ppgram*)NULL;

	/* Erase symbols */
	plist_for( g->symbols, e )
	{
		s = (ppsym*)plist_access( e );

		pfree( s->name );

		pfree( s->str );
		p_ccl_free( s->ccl );
		pregex_free( s->re );

		plist_free( s->prods );
		plist_free( s->first );
	}

	/* Erase productions */
	plist_for( g->prods, e )
	{
		p = (ppprod*)plist_access( e );
		plist_free( p->rhs );
	}

	plist_free( g->symbols );
	plist_free( g->prods );
	plist_free( g->ws );
	pfree( g );

	return (ppgram*)NULL;
}
