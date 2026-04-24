/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschyns <mano.schyns@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 07:35:13 by mschyns           #+#    #+#             */
/*   Updated: 2026/04/24 11:39:46 by mschyns          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct s_buffer
{
	char	buffer[BUFFER_SIZE];
	int		fd;
}	t_buffer;

char	*get_next_line(int fd);
char	*ft_memmove(char *dest, const char *src, int n);
int		find_retour(char *buffer, int len);
char	*ft_strjoin(char *buffer, int len, char *src, int found);

#endif