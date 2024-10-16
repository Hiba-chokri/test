/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichokri <hichokri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:51:46 by hichokri          #+#    #+#             */
/*   Updated: 2024/10/16 12:28:00 by hichokri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int open_outfiles(t_command *command)
{
    char **out_files;
    int i;
    int fd;

    i = 0;
    out_files = command->output_files;
    if ()
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

int append_files(t_command *command, t_token *token)
{
    char **append_files;
    int i;
    int fd;

    i = 0;
    out_files = command->output_files;
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
    return (fd);
}