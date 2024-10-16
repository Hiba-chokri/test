/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichokri <hichokri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 04:58:12 by hichokri          #+#    #+#             */
/*   Updated: 2024/10/16 00:36:16 by hichokri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// we created the struct to hold the values
t_env_store	*env_node(char *key, char *value)
{
	t_env_store	*env_node;

	env_node = (t_env_store*)malloc(sizeof(t_env_store));
	if (!env_node)
		return (NULL);
	env_node->key = key;
	env_node->value = value;
	env_node->prev = NULL;
	env_node->next = NULL;
	return (env_node);
}
// we created the node for the struct
void add_back_to_env_list(t_env_store **head, t_env_store  *node_to_add)
{
	t_env_store *tmp;

	if (head == NULL || node_to_add == NULL)
		return ;
	if (*head == NULL)
	{
		*head = node_to_add;
	}
	else
	{
		tmp = *head;
		while(tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = node_to_add;
		node_to_add->prev = tmp;
	}
}
// we are creating a double linked list to hold the values of the env
t_env_store *env_var_add(char **env)
{
	char		*key;
	char		*value;
	t_env_store	*new_node;
	int i;
	int j;
	t_env_store *head;
	
	i = 0;
	head = NULL;
	while (env[i])
	{
		j = ft_strchr(env[i], '=') - env[i];
		key = ft_substr(env[i], 0, j);
		value = ft_strdup((env[i] + j) + 1);
		//printf("%s\n", value);
		new_node = env_node(key, value); // we create the node
		add_back_to_env_list(&head, new_node);	// we link the node to the back of the linked list
		i++;
	}
	return(head);
}
int calculate_size(t_env_store *head)
{
	int count;

	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}
char **from_lst_to_array(t_env_store *head)
{
	char **array;
	int size;
	int i;

	i = 0;
	size = calculate_size(head);
	array = (char **)malloc(sizeof(char *) * (size + 1));
	if(!array)
		return (0);
	while (head->next)
	{
		array[i] = ft_strjoin(head->key, "=");
		array[i] = ft_strjoin(array[i], head->value);
		head = head->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
// print the env values stored in the struct

void display_env_values(char **env, t_env_store *head)
{
	t_env_store *tmp;

	head = env_var_add(env);
	tmp = head;
	while (tmp->next)
	{
		printf("%s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}