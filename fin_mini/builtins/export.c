/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichokri <hichokri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:58:06 by hichokri          #+#    #+#             */
/*   Updated: 2024/10/11 11:27:49 by hichokri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
// sort env variables before displying them
// add variables
// append if there is a +,overwrite if there is =
// function to look for +
// add declare + x
// typedef struct s_env_store
//  {
//     char *key;
//     char *value;
//     struct s_env_store *next;
//     struct s_env_store *prev;
// } t_env_store;
static t_env_store *env_var_add2(char **envp)
{
	char		*key;
	char		*value;
	t_env_store	*new_node;
	int i;
	int j;
	t_env_store *head;
	
	i = 0;
	head = NULL;
	while (envp[i])
	{
        j = ft_strchr(envp[i], '=') - envp[i];
		key = ft_substr(envp[i], 0, j);
		value = ft_strdup((envp[i] + j) + 1);
		new_node = env_node(key, value); // we create the node
		add_back_to_env_list(&head, new_node);	// we link the node to the back of the linked list
		i++;
	}
	return(head);
}

t_env_store 	*env_var_add_export(char **env, char *argv[])
{
    t_env_store *tmp;
    char		*key;
	char		*value;
	t_env_store	*new_node;
    t_env_store *head;
	int i;
	int j;
    int found;
    	
    head = env_var_add2(env);
    tmp = head;
	i = 1;
    // first add env variables
    
    while(argv[i])
    {
        j = ft_strchr(argv[i], '=') - argv[i];
		key = ft_substr(argv[i], 0, j);
		value = ft_strdup((argv[i] + j) + 1);
        tmp = head;
        found = 0;
        while(tmp)
        {
            // checks if the key ends with "+" to append , else overwrite the value
                if (ft_strcmp(tmp->key, key) == 0)
                {
                    found = 1;
                    if (key[ft_strlen(key) - 1] == '+')
                    {
                        // remove + from the key so it wont be treated differently
                        // i should add the prev pointer value as well 
                        tmp->key = ft_strndup(key, ft_strlen(key) - 1);
                        tmp->value = ft_strjoin(tmp->value, value);
                        free(value);
                    }
                    else
                    {
                        free(tmp->value);
                        tmp->value = value;
                        free(key);
                    }
                }
                // if we have a complete new key and new value
                if (!found)
                {
                    // key = env_node(ft_strdup(argv[i]), NULL);
                    new_node = env_node(key, value);
                    add_back_to_env_list(&head, new_node);
                }
                tmp = tmp->next;
        }
        i++;
    }
    return (head);
}

// add multiple variables with their values
// add variables with no values
// if example x=3 add it as x ="3"
// sort the values
// add declare -x and print the values
// we should add a manual condition if we unset env 
int sort_export_vars(char **env, char *argv[], t_env_store *head)
{
    // sort the values of export in ascii order
    int i;
    t_env_store *tmp;
    char *swap_val;
    char *swap_val2;
    char *swap;
    t_env_store *ptr;
    int swapped;
    
    i = 0;
    head = env_var_add_export(env, argv);
    tmp = head;
    swapped = 1;
    while (swapped)
    {
        swapped = 0;
        ptr = tmp->next;
            while (tmp && tmp->next)
        {
            if (ft_strcmp(tmp->key, ptr->key) > 0)
            {
                // swap the keys
                swap = tmp->key;
                tmp->key = ptr->key;
                ptr->key = swap;
                // swap the values as well
                swap_val = tmp->value;
                tmp->value = ptr->value;
                ptr->value = swap_val;
                swapped = 1;
            }
            else
                tmp = tmp->next;
        }
    }
}

void print_exp_vars(char **env, char *argv[])
{
    // print the variables of export
    t_env_store *head;
    t_env_store *tmp;

    head = env_var_add_export(env, argv);
    tmp = head;
    if (head)
    {
            while (tmp->next)
        {
            printf("declare -x ");
            printf("%s=\"%s\"\n", tmp->key, tmp->value);
            tmp = tmp->next;
        }
    }
    
}

void add_values_exp(char **env, char **argv, t_env_store **head)
{
    int i;
    t_env_store *tmp;

    i = 0;
    tmp = *head;
    // check if the arg is just export alone to display the args
    if (argv[1] && !argv[2])
    {
        display_env_values(env, *head);
    }
    else
    {
        // display the add values with the env
        print_exp_vars(env, argv);
    }
}