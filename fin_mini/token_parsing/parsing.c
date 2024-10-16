/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichokri <hichokri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 11:32:56 by mel-atti          #+#    #+#             */
/*   Updated: 2024/10/16 11:29:38 by hichokri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

cmd_lst *parse(token_lst *tokens) {
    cmd_lst *commands = malloc(sizeof(cmd_lst));
    if (!commands) {
        perror("malloc");
        return (NULL);
    }
    commands->head = NULL;
    commands->tail = NULL;
    commands->count = 0;

    t_command *current_command = malloc(sizeof(t_command));
    if (!current_command) {
        perror("malloc");
        free(commands);
        return (NULL);
    }
    init_command(current_command);

    t_token *token = tokens->head;
    int i = 0;
    while (token) {
        if (!handle_token(commands, &current_command, token)) {
            free_commands(commands);
       
            return (NULL);
        }
        
        // Skip the filename token for redirections
        if (token->type == TOKEN_REDIRECT_IN || token->type == TOKEN_REDIRECT_OUT || 
            token->type == TOKEN_REDIRECT_APPEND || token->type == TOKEN_HEREDOC) {
            token = token->next;
            i++;
        }
        
        token = token->next;
        i++;
    }
    current_command->output_files[current_command->output_file_count] = NULL;
    current_command->args[current_command->arg_count] =  NULL;
    current_command->input_files[current_command->input_file_count] =  NULL;
     current_command->heredoc_delimiters[current_command->heredoc_count] =  NULL;
    return (finalize_parsing(commands, current_command));
}

// Initializes a new Command structure with default values.
void init_command(t_command *command) {
    command->arg_count = 0;
    command->arg_capacity = 10;
    command->args = malloc(command->arg_capacity * sizeof(char *));
    command->input_files = malloc(10 * sizeof(char *));
    command->input_file_count = 0;
    command->output_files = malloc(10 * sizeof(char *));
    command->output_file_count = 0;
    command->heredoc_delimiters = malloc(10 * sizeof(char *));
    command->heredoc_count = 0;
    command->next = NULL;
}


// Processes a single token during parsing, 
// delegating to specific handlers based on token type.
int handle_token(cmd_lst *commands, t_command **current_command, t_token *token) {
    switch (token->type) {
        case TOKEN_WORD:
            return handle_word_token(*current_command, token);
        case TOKEN_PIPE:
            return handle_pipe_token(commands, current_command);
        case TOKEN_REDIRECT_IN:
        case TOKEN_REDIRECT_OUT:
        case TOKEN_REDIRECT_APPEND:
        case TOKEN_HEREDOC:
            return handle_redirection_token(*current_command, token);
        default:
            return (0);
    }
}

// Adds a word token to the current command's arguments.
int handle_word_token(t_command *command, t_token *token) {
    if (command->arg_count >= command->arg_capacity) {
        command->arg_capacity *= 2;
        command->args = realloc(command->args, command->arg_capacity * sizeof(char *)); // this realloc too!
        if (!command->args) {
            perror("realloc");
            return 0;
        }
    }
    command->args[command->arg_count] = expand_variables(token->value);
    command->arg_count++;
    return (1);
}

// Handles a pipe token, creating a new command in the CommandList.
int handle_pipe_token(cmd_lst *commands, t_command **current_command) {
    if ((*current_command)->arg_count == 0) {
        handle_syntax_error("Empty command before pipe");
        return (0);
    }
    commands->count++;
    if (commands->tail) {
        commands->tail->next = *current_command;
    } else {
        commands->head = *current_command;
    }
    commands->tail = *current_command;

    *current_command = malloc(sizeof(t_command));
    if (!*current_command) {
        perror("malloc");
        return (0);
    }
    init_command(*current_command);
    return (1);
}

// Processes input/output redirection tokens, 
// setting up file redirections for the command.

            // Reallocate should be implemented by us
// int handle_redirection_token(t_command *command, t_token *token, int *i, token_lst *tokens) {
int handle_redirection_token(t_command *command, t_token *token) {
    if (!token->next || token->next->type != TOKEN_WORD) {
        handle_syntax_error("Missing filename after redirection");
        return (0);
    }
    
    char *filename = expand_variables(token->next->value);
    
    if (token->type == TOKEN_REDIRECT_OUT || token->type == TOKEN_REDIRECT_APPEND) {
        // For output redirections
        if (command->output_file_count >= 10) {
            // Reallocate should be implemented by us
            command->output_files = realloc(command->output_files, (command->output_file_count + 1) * sizeof(char *));
        }
        command->output_files[command->output_file_count++] = filename;
    } else if (token->type == TOKEN_REDIRECT_IN) {
        // For input redirections
        if (command->input_file_count >= 10) {
            // Reallocate if needed
            command->input_files = realloc(command->input_files, (command->input_file_count + 1) * sizeof(char *));
        }
        command->input_files[command->input_file_count++] = filename;
    } else if (token->type == TOKEN_HEREDOC) {
        if (command->heredoc_count >= 10) {
            // Reallocate if needed
            command->heredoc_delimiters = realloc(command->heredoc_delimiters, (command->heredoc_count + 1) * sizeof(char *));
        }
        command->heredoc_delimiters[command->heredoc_count++] = filename;
    }
    
    return (1);
}

// Completes the parsing process, 
// handling any remaining commands and validating the result.
cmd_lst *finalize_parsing(cmd_lst *commands, t_command *current_command) {
    if (current_command->arg_count > 0) {
        if (commands->tail) {
            commands->tail->next = current_command;
        } else {
            commands->head = current_command;
        }
        commands->tail = current_command;
        commands->count++;
    }
    else if (commands->count == 0) {
        free(current_command);
        free_commands(commands);
        handle_syntax_error("No valid commands");
        return (NULL);
    }
    return (commands);
}