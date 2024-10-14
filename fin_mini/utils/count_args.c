/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichokri <hichokri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:09:49 by hichokri          #+#    #+#             */
/*   Updated: 2024/10/13 18:00:01 by hichokri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int count_args(t_command *cmd)
{
    int     count;

    count = 0;
    while (cmd)
    {
        count++;
        cmd = cmd->next;
    }
    return (count);
}