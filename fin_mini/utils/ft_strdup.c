

#include "../include/minishell.h"


char	*ft_strdup(const char *s)
{
	char	*ptr;
	char	*put;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	ptr = (char *)s;
	put = (char *)malloc(ft_strlen((char *)s) + 1);
	if (put == NULL)
		return (NULL);
	while (ptr[i])
	{
		put[i] = ptr[i];
		i++;
	}
	put[i] = '\0';
	return (put);
}
