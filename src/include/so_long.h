/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:45:04 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/06 20:37:29 by enchevri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>

typedef struct s_game
{
	char	*line;
	char	*map_path;
	char	**map;
	size_t	line_len;
	int		count_line;
	int		fd;
	int		mlx;
	int		win;
}			t_game;

void		aff_map(t_game game);

#endif