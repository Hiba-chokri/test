/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichokri <hichokri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 04:55:16 by hichokri          #+#    #+#             */
/*   Updated: 2024/09/28 18:24:04 by hichokri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	env(char **arg, t_env_store *env_list)
{
	t_env_store *tmp;

	if (arg[1])
	{
		write(2, "No such file or directory\n", 26);
	}
    tmp = env_list;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}