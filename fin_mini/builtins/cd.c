/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichokri <hichokri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:25:49 by hichokri          #+#    #+#             */
/*   Updated: 2024/10/01 17:07:42 by hichokri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
// cd with only relative and absolute path
// if a working directory is given change the path to it
// if not change it to home
// the return status is 0 if the dir is changed and non zero if not
// to get back to the previous working dir , we get the filename from OLDPWD
int change_dir(char *argv[])
{
    int cd_return;

    if (ft_strcmp("cd", argv[0]))
    {
        return (1);
    }
    if (argv[1])
    {
        cd_return = chdir(argv[1]);
        if (cd_return)
        {
            printf("no such file or directory \n");
            return (1);
        }
    }
    return (0);
}