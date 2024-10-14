/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichokri <hichokri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 04:54:28 by hichokri          #+#    #+#             */
/*   Updated: 2024/09/30 21:28:35 by hichokri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//unset bulit-in command
//remove the variable from the environment
//if the variable does not exist, print an error message
//if the variable exists, remove it from the environment
void unset(char **args, char **env)
{
    t_env_store *tmp;
    t_env_store *head;
    // t_env_store *store_node;
    int i;

    i = 1;
    head = env_var_add(env); // adding the env values to a linked list to iterate on it
    while (args[i])
    {
        tmp = head;
        while (tmp)
        {
            // the case of the node bieng at the beg 
            // case of middle or end
            if (strcmp(tmp->key, args[i]) == 0)
                // if (tmp == head)
            {
                tmp->prev->next = tmp->next;
                tmp->next->prev = tmp->prev;
                free_node(tmp);
                i++;
                tmp = tmp->next;
            }
        }
    }
}