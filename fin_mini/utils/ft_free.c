

#include "../include/minishell.h"

void ft_free(char **str)
{
    int i;

    i = 0;
    if (!str)
        return ;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}