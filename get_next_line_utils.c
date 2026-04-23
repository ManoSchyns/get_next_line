/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschyns <mano.schyns@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 07:36:57 by mschyns           #+#    #+#             */
/*   Updated: 2026/04/23 09:04:47 by mschyns          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_memmove(char *dest, const char *src, int n)
{
	int	i;

	i = 0;
	if (dest < src)
	{
		while (i < n)
		{
			dest[i] = src[i];
			i ++;
		}
	}
	else if (dest > src)
	{
		while (n > 0)
		{
			dest[n - 1] = src[n - 1];
			n --;
		}
	}
	return (dest);
}

int	find_retour(char *buffer, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (buffer[i] == '\n')
			return (i);
		i ++;
	}
	return (-1);
}

static int	cpy_on(char *dest, char *buffer, int start, int len)
{
	int	j;

	j = 0;
	while (j < len)
	{
		dest[start] = buffer[j];
		start ++;
		j ++;
	}
	return (start);
}

char	*ft_strjoin(char *buffer, int len, char *src, int found)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	while (src && src[i] != '\0')
		i ++;
	if (found)
		len += 1;
	dest = malloc((i + len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (src && src[i] != '\0')
	{
		dest[i] = src[i];
		i ++;
	}
	i = cpy_on(dest, buffer, i, len);
	if (src)
		free(src);
	dest[i] = '\0';
	return (dest);
}
