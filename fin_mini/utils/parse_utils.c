/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichokri <hichokri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 12:44:37 by mel-atti          #+#    #+#             */
/*   Updated: 2024/10/11 11:13:46 by hichokri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void handle_syntax_error(const char *message) {
    fprintf(stderr, "Syntax error: %s\n", message);
}

// Checks if a character is valid for use in a variable name.
int is_valid_variable_char(char c) {
    return isalnum(c) || c == '_';
}

// Frees memory allocated for a token_lst.
void free_tokens(token_lst *tokens) 
{
    t_token *current = tokens->head;
    while (current) {
        t_token *next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
    free(tokens);
}

// Frees memory allocated for a CommandList.
void free_commands(cmd_lst *commands) {
    if (commands == NULL) {
        return;
    }

    t_command *current = commands->head;
    t_command *next;

    while (current != NULL) {
        next = current->next;

        // Free argument strings
        if (current->args != NULL) {
            for (int i = 0; i < current->arg_count; i++) {
                free(current->args[i]);
            }
            free(current->args);
        }

        // Free input files
        if (current->input_files != NULL) {
            for (int i = 0; i < current->input_file_count; i++) {
                free(current->input_files[i]);
            }
            free(current->input_files);
        }

        // Free output files
        if (current->output_files != NULL) {
            for (int i = 0; i < current->output_file_count; i++) {
                free(current->output_files[i]);
            }
            free(current->output_files);
        }

        if (current->heredoc_delimiters != NULL) {
            for (int i = 0; i < current->heredoc_count; i++) {
                free(current->heredoc_delimiters[i]);
            }
            free(current->heredoc_delimiters);
        }

        // Free the command structure itself
        free(current);

        current = next;
    }

    // Free the command list structure
    free(commands);
}