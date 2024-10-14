/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 14:27:23 by mel-atti          #+#    #+#             */
/*   Updated: 2024/10/03 20:23:57 by mel-atti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *expand_variables(char *str) {
    size_t max_len = 4000 + strlen(str);
    char *result = malloc(max_len);
    if (!result) {
        perror("malloc");
        return (NULL);
    }
    char *write_ptr = result;
    int in_single_quotes = 0;
    int in_double_quotes = 0;
    char *read_ptr = str;

    while (*read_ptr && (size_t)(write_ptr - result) < max_len - 1) {
        if (*read_ptr == '\'' && !in_double_quotes) {
            in_single_quotes = !in_single_quotes;
            *write_ptr++ = *read_ptr;
        } else if (*read_ptr == '"' && !in_single_quotes) {
            in_double_quotes = !in_double_quotes;
            *write_ptr++ = *read_ptr;
        } else if (*read_ptr == '$' && !in_single_quotes) {
            size_t remaining = max_len - (write_ptr - result) - 1;

            if (*(read_ptr + 1) == '(') {
                read_ptr = handle_command_substitution(&write_ptr, read_ptr, remaining);
                if (!read_ptr) {
                    free(result);
                    return (NULL);
                }
            } else if (*(read_ptr + 1) == '{') {
                read_ptr = handle_braced_variable(&write_ptr, read_ptr, remaining);
                if (!read_ptr) {
                    free(result);
                    return (NULL);
                }
            } else {
                read_ptr = handle_variable_expansion(&write_ptr, read_ptr, remaining);
            }
        } else {
            *write_ptr++ = *read_ptr;
        }
        read_ptr++;
    }
    *write_ptr = '\0';
    return (result);
}

char *handle_variable_expansion(char **write_ptr, char *read_ptr, size_t max_len) {
    if (*(read_ptr + 1) == '?') {
        int written = snprintf(*write_ptr, max_len, "%d", g_last_exit_status);
        if (written > 0)
            *write_ptr += written;
        return read_ptr + 1;
    } else if (is_valid_variable_char(*(read_ptr + 1))) {
        char var_name[256] = {0};
        int i = 0;
        read_ptr++;
        while (is_valid_variable_char(*read_ptr) && i < 255) 
            var_name[i++] = *read_ptr++;
        read_ptr--;
        char *var_value = getenv(var_name);
        if (var_value) {
            size_t len = strlen(var_value);
            if (len > max_len - 1) len = max_len - 1;
            strncpy(*write_ptr, var_value, len);
            (*write_ptr)[len] = '\0';
            *write_ptr += len;
        }
        return read_ptr;
    } else {
        *(*write_ptr)++ = *read_ptr;
        return (read_ptr);
    }
}

char *handle_command_substitution(char **write_ptr, char *read_ptr, size_t max_len) {
    char cmd[1024] = {0};
    int i = 0;

    if (*read_ptr == '$') 
    {
        read_ptr++;
        if (*read_ptr == '(') {
            read_ptr++;
        }
    }

    while (*read_ptr && *read_ptr != ')' && i < 1023) {
        cmd[i++] = *read_ptr++;
    }
    if (*read_ptr && *read_ptr != ')') {
        handle_syntax_error("Unmatched parenthesis in command substitution");
        return (NULL);
    }

    cmd[i] = '\0';
    char *trim_cmd = trim_white_space(cmd);

    char *var_value = getenv(trim_cmd);
    if (var_value) {
        size_t len = strlen(var_value);
        if (len > max_len - 1) len = max_len - 1;
        strncpy(*write_ptr, var_value, len);
        (*write_ptr)[len] = '\0';
        *write_ptr += len;
    } else {
        size_t len = strlen(trim_cmd);
        if (len > max_len - 1) len = max_len - 1;
        strncpy(*write_ptr, trim_cmd, len);
        (*write_ptr)[len] = '\0';
        *write_ptr += len;
    }
    return (read_ptr);
}

char *trim_white_space(char *str) {
    while (isspace(*str)) 
        str++;
    char *end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) 
        end--;
    *(end + 1) = '\0';
    return (str);
}

char *handle_braced_variable(char **write_ptr, char *read_ptr, size_t max_len) {
    char var_name[1024] = {0};
    int i = 0;

    if (*read_ptr == '$') {
        read_ptr++;
        if (*read_ptr == '{') {
            read_ptr++;
        }
    }

    while (*read_ptr && *read_ptr != '}' && i < 1023) 
        var_name[i++] = *read_ptr++;

    if (*read_ptr && *read_ptr != '}') {
        handle_syntax_error("Unmatched brace in variable expansion");
        return (NULL);
    }

    var_name[i] = '\0';
    char *trim_var = trim_white_space(var_name);

    char *var_value = getenv(trim_var);
    if (var_value) {
        size_t len = strlen(var_value);
        if (len > max_len - 1) len = max_len - 1;
        strncpy(*write_ptr, var_value, len);
        (*write_ptr)[len] = '\0';
        *write_ptr += len;
    } else {
        size_t len = strlen(trim_var);
        if (len > max_len - 1) len = max_len - 1;
        strncpy(*write_ptr, trim_var, len);
        (*write_ptr)[len] = '\0';
        *write_ptr += len;
    }
    return (read_ptr);
}
