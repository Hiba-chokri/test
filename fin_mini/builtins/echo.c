/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichokri <hichokri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 04:59:18 by hichokri          #+#    #+#             */
/*   Updated: 2024/10/11 15:11:41 by hichokri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// echo -n buitin command
// check for the existence of the -n flag
// if it exists, do not print a newline
// if it does not exist, print a newline
void echo_n(char **arg) {
    int i; 
    int n_flag ;
    
    i = 1;// initialize i to 1 to skip the command name
    n_flag = 0;
    while (arg[i] != NULL) {
        if (ft_strcmp(arg[i], "-n") == 0) {
            n_flag = 1;
        }
        i++;
    }
    i = 1;
    while (arg[i] != NULL) {
        if (ft_strcmp(arg[i], "-n") != 0) {
            printf("%s", arg[i]);
            if (arg[i + 1] != NULL) {
                printf(" ");
            }
        }
        i++;
    }
    if (n_flag == 0) 
    {
        printf("\n");
    }
}