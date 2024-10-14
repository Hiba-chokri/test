/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichokri <hichokri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 05:03:47 by hichokri          #+#    #+#             */
/*   Updated: 2024/09/27 16:37:25 by hichokri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*substr;
	size_t			str_len;

	if (!s)
		return (ft_strdup(""));
	i = 0;
	str_len = ft_strlen(s);
	if (start > str_len)
		return (ft_strdup(""));
	if (start + len > str_len)
		len = str_len - start;
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	i = start;
	j = 0;
	while (j < len && s[start + j])
		substr[j++] = s[i++];
	substr[j] = '\0';
	return (substr);
}