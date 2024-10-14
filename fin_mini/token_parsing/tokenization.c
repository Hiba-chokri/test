/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:08:21 by mel-atti          #+#    #+#             */
/*   Updated: 2024/10/03 20:24:35 by mel-atti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Breaks the input string into tokens (words, operators, etc.) 
// and returns a token_lst.
token_lst *tokenize(char *input) {
    token_lst *tokens;
    char *current_token;
    init_tokenize(&tokens, &current_token);
    if (!tokens) // || !current_token
        return NULL;

    char *token_end = input;
    int in_quotes = 0;
    char quote_char = '\0';
    int current_token_len = 0;

    while (*token_end != '\0') {
///////////////////////////////////////////////////////////////:
        if (*token_end == '$')
        {
            while ((*token_end) != ')' && *token_end)
            {
                current_token[(current_token_len)] = *token_end;
                current_token_len++;
                token_end++;
            }
            if ((*token_end) == ')' && *token_end) // ESPECIALLY THIS PIECE
            {
                current_token[(current_token_len)] = *token_end;
                current_token_len++;
                token_end++;
            }
            // token_end++;
            add_token(tokens, current_token, &current_token_len, TOKEN_WORD, NULL);
            // printf("***** %s ******\n", current_token);
        }
    ///////////////////////////////////////////////////////////////:

        if (!in_quotes && (isspace(*token_end) || strchr("|<>", *token_end))) {
            if (current_token_len > 0) 
                add_token(tokens, current_token, &current_token_len, TOKEN_WORD, NULL);
            if (!isspace(*token_end)) 
                handle_special_char(tokens, &token_end, current_token, &current_token_len);
        } else 
            handle_character(&in_quotes, &quote_char, &token_end, current_token, &current_token_len);
        token_end++;
    }

    return (finalize_tokenization(tokens, current_token, current_token_len, in_quotes));
}

// Initializes the tokenization process, 
// allocating memory for token_lst and current token.
void init_tokenize(token_lst **tokens, char **current_token) {
    *tokens = malloc(sizeof(token_lst));
    if (!*tokens) {
        perror("malloc");
        return;
    }
    (*tokens)->head = NULL;
    (*tokens)->tail = NULL;
    (*tokens)->count = 0;
    *current_token = malloc(256); // Start with a small buffer
    if (!*current_token) {
        perror("malloc");
        free(*tokens);
        *tokens = NULL;
    }
}

// Adds a new token to the token_lst.
void add_token(token_lst *tokens, char *current_token, int *current_token_len, token_type type, const char *value) {
    t_token *new_token = malloc(sizeof(t_token));
    if (!new_token) {
        perror("malloc");
        return;
    }
    if (type == TOKEN_WORD) {
        current_token[*current_token_len] = '\0';
        new_token->type = type;
        new_token->value = strdup(current_token);
    } else {
        new_token->type = type;
        new_token->value = strdup(value);
    }
    new_token->next = NULL;

    if (tokens->tail) {
        tokens->tail->next = new_token;
    } else {
        tokens->head = new_token;
    }
    tokens->tail = new_token;
    tokens->count++;
    *current_token_len = 0;
}

// Processes special characters (|, <, >) during tokenization.
void handle_special_char(token_lst *tokens, char **token_end, char *current_token, int *current_token_len) {
    if (**token_end == '|')
        add_token(tokens, current_token, current_token_len, TOKEN_PIPE, "|");
    else if (**token_end == '<') {
        if (*(*token_end + 1) == '<') {
            add_token(tokens, current_token, current_token_len, TOKEN_HEREDOC, "<<");
            (*token_end)++;
        } else {
            add_token(tokens, current_token, current_token_len, TOKEN_REDIRECT_IN, "<");
        }
    } else if (**token_end == '>') {
        if (*(*token_end + 1) == '>') {
            add_token(tokens, current_token, current_token_len, TOKEN_REDIRECT_APPEND, ">>");
            (*token_end)++;
        } else {
            add_token(tokens, current_token, current_token_len, TOKEN_REDIRECT_OUT, ">");
        }
    }
}

// Processes a single character during tokenization,
// handling quotes and building tokens.
void handle_character(int *in_quotes, char *quote_char, char **token_end, char *current_token, int *current_token_len) {
    if (**token_end == '\'' || **token_end == '"') {
        if (!*in_quotes) {
            *in_quotes = 1;
            *quote_char = **token_end;
        } else if (**token_end == *quote_char) {
            *in_quotes = 0;
        }
    }
    current_token[(*current_token_len)++] = **token_end;
    if (*current_token_len % 256 == 0) {
        current_token = realloc(current_token, *current_token_len + 256); // this realloc should be implemented by us
        if (!current_token) {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
    }
}

// Completes the tokenization process, 
// handling any remaining tokens and unclosed quotes.
token_lst *finalize_tokenization(token_lst *tokens, char *current_token, int current_token_len, int in_quotes) {
    if (in_quotes) {
        handle_syntax_error("Unclosed quotes");
        free(current_token);
        free_tokens(tokens);
        return NULL;
    }
    if (current_token_len > 0) 
        add_token(tokens, current_token, &current_token_len, TOKEN_WORD, NULL);
    free(current_token);
    return (tokens);
}