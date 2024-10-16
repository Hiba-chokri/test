/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichokri <hichokri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:51:46 by hichokri          #+#    #+#             */
/*   Updated: 2024/10/16 15:12:49 by hichokri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int open_outfiles(t_command *command, t_token *token)
{
    char **out_files;
    int i;
    int fd;

    i = 0;
    out_files = command->output_files;
    if (token->type == TOKEN_REDIRECT_OUT)
    {
        while (out_files[i])
        {
            // check if it's an infile or outfile and open them
            fd = open(out_files[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd == -1)
        {
            perror("opening outfile error");
            exit(1);
        }
            i++;   
        }
    }
    else if (token->type == TOKEN_REDIRECT_APPEND)
    {
        while (out_files[i])
        {
                // check if it's an infile or outfile and open them
            fd = open(out_files[i], O_CREAT | O_WRONLY | O_APPEND, 0644);
            if (fd == -1)
            {
                perror("opening outfile error");
                exit(1);
            }
            i++;
        }
    }
    return (fd);
}

int open_infiles(t_command *command)
{
    char **in_files;
    int i;
    int fd;

    i = 0;
    in_files = command->input_files;
    while (in_files[i])
    {
        // check if it's an infile or outfile and open them
        fd = open(in_files[i], O_RDONLY);
        if (fd == -1)
	{
		perror("opening file error");
        exit (1);
    }
        i++;   
    }
    return (fd);
}

void open_files(t_command *cmd, t_token *token)
{
    if (cmd->output_file_count >= 10)
    {
        open_outifles(cmd, token);
        cmd = cmd->next;
    }
    else if (cmd->input_file_count >= 10)
    {
        open_infiles(cmd);
        cmd = cmd->next;
    }
}