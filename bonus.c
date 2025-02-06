/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:20:15 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/06 18:20:25 by enchevri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*get_keyboard(void)
{
	int		fd;
	char	*line;

	fd = open("/etc/default/keyboard", O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error opening the keyboard\n");
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
			ft_printf("US\n");
		free(line);
	}
	close(fd);
	return (0);
}
