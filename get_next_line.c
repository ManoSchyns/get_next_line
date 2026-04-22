/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschyns <mano.schyns@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 07:37:02 by mschyns           #+#    #+#             */
/*   Updated: 2026/04/22 16:07:00 by mschyns          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

//lire le fichier pour la buffer size
//chercher le \n -> si \n on arrete tout

//copie les caracteres de la sources dans la destination. Pour n caracteres
//ici ca va principalement déplacé le buffer
char	*ft_memmove(char *dest, const char *src, int n)
{
	int i;

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

//cherche un retour a la ligne dans le buffer. 
//partant du début jusqu'a la len
//retourn l'index de ou se trouve le \n
//retourn -1 si pas trouvé
int	find_retour(char *buffer, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (buffer[i] == '\n')
			return (i);
		i ++;
	}
	return(-1);
}


char *ft_strjoin(char *buffer, int len, char *src, int found)
{
	int i;
	int j;
	char *dest;

	i = 0;
	while (src && src[i] != '\0')
		i ++;
	if (found)
		len += 1;
	dest = malloc((i + len  + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (src && src[i] != '\0')
	{
		dest[i] = src[i];
		i ++;
	}
	j = 0;
	while (j < len)
	{
		dest[i] = buffer[j];
		i ++;
		j ++;
	}
	if (src)
		free(src);
	dest[i] = '\0';
	return(dest);
}

//lit le fichier
//ajoute au buffer à partir de l'indice indice. Jusqua bout de celui-ci
// si erreur ou que le buffer et fichier est vide -> retourne -1
//si on trouve un /n, -> on met dans dest, dest de base + buffer jusqu'a \name
//return 1 on dit qu'on l'a trouvé.
// si non, on ajoute tout le buffer dans la dest;
int	read_buffer(int fd, char *buffer, int *start, char **dest, int *end)
{
	int flag;
	int ret;

	flag = read(fd, buffer + *start, BUFFER_SIZE - *start);
	*end = *start + flag;
	if (flag < 0)
		return (-1);
	if (flag == 0 && *start == 0)
		return (-1);
	ret = find_retour(buffer, *end);
	if (ret >= 0)
	{
		*dest = ft_strjoin(buffer, ret , *dest, 1);
		*start = ret + 1;
		return (1);
	}
	*start = 0;
	*dest = ft_strjoin(buffer, *end, *dest, 0);
	return (0);
}

//indice = indice jusqu'ou aller, c'est une len
char *read_line(int fd, char *buffer, int *start)
{
	char *dest;
	int flag;
	int end;

	dest = NULL;
	flag = read_buffer(fd, buffer, start, &dest, &end);
	while (flag == 0)
	{
		flag = read_buffer(fd, buffer, start, &dest, &end);
		if (flag == -1)
			return (dest);
	}
	if (flag == 1)
	{
		ft_memmove(buffer, buffer + *start, end - *start);
		*start = end - *start;
	}
	//printf("\ntes--->%s, %d, \n destinetion : %s\n\n", buffer, *start, dest);
	return (dest);
	
	
}

char	*get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE];
	static int size;

	if (fd < 0)
		return (NULL);
	return (read_line(fd, buffer, &size));

}

#include <fcntl.h>
int main(void)
{
    int fd = open("test_gnl.txt", O_RDONLY);
    char *buffer;

    if (fd < 0)
        return (1);

    buffer = get_next_line(fd);
    while (buffer != NULL)
    {
        printf("%s", buffer);
        free(buffer);
        buffer = get_next_line(fd);
    }
    close(fd);
    return (0);
}