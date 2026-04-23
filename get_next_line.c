/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschyns <mano.schyns@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 07:37:02 by mschyns           #+#    #+#             */
/*   Updated: 2026/04/23 09:04:34 by mschyns          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_buffer(t_buffer *data, int *start, char **dest, int *end)
{
	int	flag;
	int	ret;

	flag = read(data->fd, data->buffer + *start, BUFFER_SIZE - *start);
	*end = *start + flag;
	if (flag < 0)
		return (-2);
	if (flag == 0 && *start == 0)
		return (-1);
	ret = find_retour(data->buffer, *end);
	if (ret >= 0)
	{
		*dest = ft_strjoin(data->buffer, ret, *dest, 1);
		*start = ret + 1;
		return (1);
	}
	*start = 0;
	*dest = ft_strjoin(data->buffer, *end, *dest, 0);
	return (0);
}

char	*read_line(t_buffer *data, int *start)
{
	char	*dest;
	int		flag;
	int		end;

	dest = NULL;
	flag = read_buffer(data, start, &dest, &end);
	if (flag == -2)
		return (NULL);
	while (flag == 0)
	{
		flag = read_buffer(data, start, &dest, &end);
		if (flag == -1)
			return (dest);
		if (flag == -2)
			return (NULL);
	}
	if (flag == 1)
	{
		ft_memmove(data->buffer, data->buffer + *start, end - *start);
		*start = end - *start;
	}
	return (dest);
}

char	*get_next_line(int fd)
{
	static int		size;
	static t_buffer	data;

	data.fd = fd;
	if (data.fd < 0)
		return (NULL);
	return (read_line(&data, &size));
}

/*#include <stdio.h>
#include <fcntl.h>
#include <string.h>
int main(void)
{
    int fd = open("test.txt", O_RDONLY);
	//int fd = 1;
    char *buffer;

    //if (fd < 0)
    //    return (1);
    buffer = get_next_line(fd);
	if (buffer == NULL)
		printf("Erreur -> pas d'ouverture ?");
	while (buffer != NULL)
    {
        printf("%s", buffer);
        free(buffer);
        buffer = get_next_line(fd);
    }
    close(fd);
    return (0);
}*/