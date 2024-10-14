/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichokri <hichokri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 04:53:00 by hichokri          #+#    #+#             */
/*   Updated: 2024/09/30 21:12:37 by hichokri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// pwd builtin command
// print the full name of the current working directory
//getcwd is used to get the current working directory
void pwd(void) 
{
    char buff[PATH_MAX];// buffer to store the path of the current working directory
    char *cwd;

    cwd = getcwd(buff, PATH_MAX);// if succefull getcwd returns a pointer to the buffer where the path is stored
    if (cwd != NULL)
        printf("%s\n", cwd);
    else
        perror("Path not found\n");
}
