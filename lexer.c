/**
 * Tony Givargis
 * Copyright (C), 2023
 * University of California, Irvine
 *
 * CS 238P - Operating Systems
 * lexer.c
 */

#include "lexer.h"

struct lexer {
	uint64_t size;
	struct lexer_token *tokens;
};

static struct lexer_token *
mktoken(struct lexer *lexer, enum lexer_token_op op)
{
	struct lexer_token *token, *tokens;
	size_t n;

	if (0 == (lexer->size % 100)) {// it isused to allocate memory efficiently by block allocation
		n = (lexer->size + 100) * sizeof (tokens[0]);
		if (!(tokens = realloc(lexer->tokens, n))) {
			TRACE("out of memory");
			return NULL;
		}
		lexer->tokens = tokens;
	}
	token = &lexer->tokens[lexer->size++];
	memset(token, 0, sizeof (struct lexer_token));
	token->op = op;
	return token;
}

static int
tokenize(struct lexer *lexer, const char *s)
{
	const char * const OPERATORS = "+-*/()";
	struct lexer_token *token;
	size_t i;
	char *e;

	while (*s) {
		for (i=0; i<safe_strlen(OPERATORS); ++i) {
			if (OPERATORS[i] == (*s)) {
				if (!mktoken(lexer,
					     LEXER_OP_ADD + i)) {
					TRACE(0);
					return -1;̀
				}
				break;
			}
		}
		if (safe_strlen(OPERATORS) > i) {
			++s; // found a match for the operator so we move to the next part of the string 
		}
		else if (isspace(*s)) {//whitespaces are skipped
			++s;
		}
		else {
			if (!(token = mktoken(lexer, LEXER_OP_VAL))) {
				TRACE(0);
				return -1;
			}
			token->val = strtod(s, &e);
			if (s == e) {
				TRACE("lexer");
				return -1;
			}
			s = e; // while converting str to number in the input it will be not followed by operator, operator can't be converted and "e" is pointing to the operator so we assign s to e to further compute
		}
	}
	return 0;
}

struct lexer *
lexer_open(const char *s) // tokenizing the entire string
{
	struct lexer *lexer;

	assert( safe_strlen(s) );

	if (!(lexer = malloc(sizeof (struct lexer)))) {
		TRACE("out of memory");
		return NULL;
	}
	memset(lexer, 0, sizeof (struct lexer));
	if (tokenize(lexer, s)) {
		lexer_close(lexer);
		TRACE(0);
		return NULL;
	}
	return lexer;
}

void
lexer_close(struct lexer *lexer)
{
	if (lexer) {
		FREE(lexer->tokens);
		memset(lexer, 0, sizeof (struct lexer));
	}
	FREE(lexer);
}

uint64_t
lexer_size(const struct lexer *lexer)
{
	assert( lexer );

	return lexer->size;
}

const struct lexer_token *
lexer_lookup(const struct lexer *lexer, uint64_t i)
{
	assert( lexer );
	assert( i < lexer->size );

	return &lexer->tokens[i];
}
