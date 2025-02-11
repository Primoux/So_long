/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:19:48 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/11 22:29:01 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

/*-------------------------------- INCLUDES --------------------------------*/

/* Standard Libraries */
# include <stdio.h>
# include <stdlib.h>

/*-------------------------------- DEFINES --------------------------------*/

# define GOOD_CHAR "10CPE"

/*--------------------------------- TYPES ---------------------------------*/

typedef enum e_bool
{
	FALSE,
	TRUE
}					t_bool;

/*-------------------------------- STRUCTS --------------------------------*/

typedef struct s_mlx_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*wall;
	void			*floor;
	void			*player;
	void			*exit;
	void			*collect1;
	void			*collect2;
	void			*collect3;
	int				pixel_size;
}					t_mlx_data;

typedef struct s_char_count
{
	size_t			p_count;
	size_t			c_count;
	size_t			e_count;
}					t_char_count;

typedef struct s_game
{
	char			*line;
	char			*map_path;
	char			**map;
	size_t			line_len;
	size_t			count_line;
	int				fd;
	int				player_x;
	int				player_y;
	int				exit_x;
	int				exit_y;
	size_t			move_count;
	t_bool			on_exit;
	t_char_count	char_count;
	t_mlx_data		mlx;
}					t_game;

/*------------------------------- FUNCTIONS -------------------------------*/

/* Map Parsing */
int					parsing(t_game *game);
int					check_walls_left_right(t_game *game);
int					check_walls_up_down(t_game *game);
int					check_line_len(t_game game);
int					check_char(t_game *game);

/* Display and Rendering */
int					init_window(t_game *game);
void				aff_map(t_game game);
void				put_sprite(t_mlx_data *data, char c, int x, int y);
void				render_game(t_game game);
int					init_mlx_resources(t_game *game);

/* Player Movement */
int					check_collision(t_game *game, int old_x, int old_y);
void				update_player_pos(t_game *game, int old_x, int old_y);
void				find_player_pos(t_game *game);
void				find_exit_pos(t_game *game);

/* Event Handling */
int					handle_input(int keysym, t_game *game);
int					handle_destroy(t_game *game);

/* Cleanup */
int					cleanup_mlx(t_mlx_data *data, void *img);
void				cleanup_game(t_game *game);
void				cleanup_images(t_game *game);

#endif