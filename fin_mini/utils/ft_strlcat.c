/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichokri <hichokri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:32:27 by hichokri          #+#    #+#             */
/*   Updated: 2024/07/27 17:33:06 by hichokri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	len_dest;
	size_t	len_src;

	if (dest == NULL && size == 0)
		return (0);
	len_src = ft_strlen(src);
	len_dest = ft_strlen(dest);
	i = 0;
	if (size == 0 || size <= len_dest)
		return (len_src + size);
	while (src[i] != '\0' && i < size - len_dest - 1)
	{
		dest[len_dest + i] = src[i];
		i++;
	}
	dest[len_dest + i] = '\0';
	return (len_src + len_dest);
}