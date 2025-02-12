/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:20:15 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/12 18:40:21 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <fcntl.h>

char	*get_keyboard(void)
{
	int		fd;
	char	*line;

	fd = open("/etc/default/keyboard", O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error opening the keyboard\n", 2);
		return (1);
	}
	line = get_next_line(fd);
	while (line != NULL && !(ft_strnstr(line, "LAYOUT", ft_strlen(line))))
	{
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			break ;
	}
	if (line)
	{
		if (line[11] == 'u' && line[12] == 's')
			ft_putstr_fd("US\n", 1);
		free(line);
	}
	close(fd);
	return (0);
}
