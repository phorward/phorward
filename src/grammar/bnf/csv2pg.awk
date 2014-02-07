#!/bin/sh
# -SCRIPT-----------------------------------------------------------------------
# Phorward Foundation Toolkit
# Copyright (C) 2006-2014 by Phorward Software Technologies, Jan Max Meyer
# http://www.phorward-software.com ++ contact<at>phorward<dash>software<dot>com
# All rights reserved. See LICENSE for more information.
#
# File:		csv2pg.awk
# Usage: 	Generates pggrammar C code from a csv-styled input
# ------------------------------------------------------------------------------

BEGIN			{
					FS=":"

					grammar = "g"

					var[ "a" ]	= "A_"
					var[ "t" ]	= "T_"
					var[ "n" ]	= "N_"
					var[ "p" ]	= "P_"

					cch[ "%" ] = "percent"
					cch[ "+" ] = "plus"
					cch[ "-" ] = "minus"
					cch[ "*" ] = "star"
					cch[ "/" ] = "slash"
					cch[ "\\" ] = "backslash"
					cch[ "@" ] = "at"
					cch[ "?" ] = "quest"
					cch[ "|" ] = "pipe"
					cch[ ";" ] = "semicolon"
					cch[ ":" ] = "colon"
					cch[ "#" ] = "hash"
					cch[ "&" ] = "amp"
					cch[ "$" ] = "dollar"
					cch[ "!" ] = "exclam"
					cch[ "^" ] = "circumflex"
					cch[ ">" ] = "greater"
					cch[ "<" ] = "lower"
					cch[ "=" ] = "equal"
					cch[ "~" ] = "tilde"
					cch[ "[" ] = "lbracket"
					cch[ "]" ] = "rbracket"
					cch[ "(" ] = "lparen"
					cch[ ")" ] = "rparen"
					cch[ "{" ] = "lcurly"
					cch[ "}" ] = "rcurly"
					cch[ " " ] = "_"
					cch[ "\t" ] = "____"
				}

END				{
					# Declarations
					for( s in terminals )
						printf "pgterminal*	%s%s;\n", \
							var[ "t" ], to_cname( s )

					for( n in nonterminals )
						printf "pgnonterminal*	%s%s;\n", \
							var[ "n" ], to_cname( n )

					for( n in nonterminals )
					{
						for( i = 1; i <= nonterminals[ n ]; i++ )
						{
							printf "pgproduction*	%s%s_%d;\n", \
								var[ "p" ], to_cname( n ), i
						}
					}

					for( a in asttypes )
						printf "pgasttype*	%s%s;\n", \
							var[ "a" ], asttypes[ a ]

					# Objects
					printf "\n/* Terminals */\n"

					for( s in terminals )
						printf \
						"%s%s = pg_terminal_create( %s, \"%s\", %s );\n", \
							var[ "t" ], to_cname( s ), grammar,
								s, terminals[ s ] == s ? "(char*)NULL" : \
									"\"" terminals[ s ] "\""

					printf "\n/* Nonterminals */\n"

					for( n in nonterminals )
					{
						printf \
						"%s%s = pg_nonterminal_create( %s, \"%s\" );\n", \
							var[ "n" ], to_cname( n ), grammar, n
					}

					first = 1

					for( a in asttypes )
					{
						if( first )
						{
							printf "\n/* AST-Types */\n"
							first = 0
						}

						printf "%s%s = pg_asttype_create( %s, \"%s\" );\n", \
							var[ "a" ], asttypes[ a ], grammar, \
								asttypes[ a ]
					}


					for( n in nonterminals )
					{
						printf "\n/* Productions for %s */\n", n

						for( i = 1; i <= nonterminals[ n ]; i++ )
						{
							printf "%s%s_%d = pg_production_create( %s%s", \
								var[ "p" ], to_cname( n ), i, \
									var[ "n" ], to_cname( n )

							for( j = 1; productions[ n ][ i ][ j ] != ""; j++ )
							{
								printf ", "
									
								sym = productions[ n ][ i ][ j ]

								if( substr( sym, 1, 1 ) == "@" )
									printf "%s%s", var[ "t" ], \
										to_cname( substr( sym, 2 ) )
								else
									printf "%s%s", var[ "n" ], to_cname( sym )
							}

							printf ", (pgsymbol*)NULL );\n"
						}

						print ""

						for( i = 1; i <= nonterminals[ n ]; i++ )
						{
							if( prodast[ n ][ i ] != "" )
								printf "pg_production_set_asttype( " \
									"%s%s_%d, %s%s );\n", \
										var[ "p" ], to_cname( n ), i, \
											var[ "a" ], \
												to_cname( prodast[ n ][ i ] )
						}
					}
				}

/^#/			{	next	}

/^@/			{
					term = substr( $1, 2 )

					if( terminals[ term ] != "" )
					{
						printf "Warning: Terminal '%s' already defined\n", term 
						next
					}

					if( term == "colon" )
						$2 = ":"

					if( $2 != "" )
					{
						gsub( /"/, "\\\"", $2 )
						terminals[ term ] = $2
					}
					else
						terminals[ term ] = term

					next
				}

				{
					if( $0 == "" )
						next

					if( substr( $1, 1, 1 ) == "%" ) 
					{
						ast = substr( $1, 2 )
						if( ast == "" )
							ast = $2

						asttypes[ ast ] = ast 
						i = 2
					}
					else
					{
						ast = ""
						i = 1
					}

					nt = $i
					
					idx = ( nonterminals[ nt ] = nonterminals[ nt ] + 1 )

					j = 1
					for( i++; i <= NF; i++ )
					{
						sym = $i
						if( substr( sym, 1, 1 ) == "@" )
						{
							sym = substr( sym, 2, length( sym ) )

							if( terminals[ sym ] == "" )
								terminals[ sym ] = sym

							sym = "@" sym
						}

						productions[ nt ][ idx ][ j++ ] = sym
					}

					prodast[ nt ][ idx ] = ast
				}

function to_cname( name )
{
	cname = ""
	for( x = 1; x <= length( name ); x++ )
	{
		ch = substr( name, x, 1 )
		if( cch[ ch ] != "" )
			cname = cname cch[ ch ]
		else
			cname = cname ch
	}

	return cname
}
