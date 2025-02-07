/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:45:04 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/07 18:52:20 by enchevri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>

# define GOOD_CHAR "10CPE"

typedef struct s_char_count
{
	size_t			player_count;
	size_t			colectible_count;
	size_t			exit_count;

}					t_char_count;

typedef struct s_game
{
	char			*line;
	char			*map_path;
	char			**map;
	size_t			line_len;
	size_t			count_line;
	int				fd;
	t_char_count	char_count;
}					t_game;

//----------------------parsing--------------------------------------
int					parsing(t_game *game);
int					check_walls_left_right(t_game *game);
int					check_walls_up_down(t_game *game);
int					check_line_len(t_game game);
int					check_char(t_game *game);
//--------------------------------------------------------------------
void				aff_map(t_game game);

#endif