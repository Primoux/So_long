/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:19:48 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/12 18:52:17 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

/*-------------------------------- INCLUDES --------------------------------*/

/* Standard Libraries */
# include <stdlib.h>

/*-------------------------------- DEFINES --------------------------------*/

# define GOOD_CHAR "10CPE"

/*--------------------------------- ENUM ---------------------------------*/

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
	int				screen_width;
	int				screen_height;
	void			*wall;
	void			*floor;
	void			*player;
	void			*exit;
	void			*collect1;
	void			*collect2;
	void			*collect3;
	size_t			pixel_size;
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
	size_t			player_x;
	size_t			player_y;
	size_t			exit_x;
	size_t			exit_y;
	size_t			move_count;
	t_bool			on_exit;
	t_char_count	char_count;
	t_mlx_data		mlx;
	size_t			found_collectibles;
}					t_game;

/*------------------------------- FUNCTIONS -------------------------------*/

/* Map Parsing */
int					parsing(t_game *game);
int					check_walls_left_right(t_game *game);
int					check_walls_up_down(t_game *game);
int					check_line_len(t_game game);
int					check_char(t_game *game);
int					check_map_valid(t_game *game);
char				**create_map(t_game *game);
void				flood_fill(char **map, size_t y, size_t x, t_game *game);
int					check_argv(char *argv);

/* Display and Rendering */
int					init_window(t_game *game);
void				aff_map(t_game game);
void				put_sprite(t_mlx_data *data, char c, size_t x, size_t y);
void				render_game(t_game game);
int					init_mlx_resources(t_game *game, t_mlx_data *mlx);
int					put_on_screen(t_game *game);

/* Player Movement */
int					check_collision(t_game *game, size_t old_x, size_t old_y);
void				update_player_pos(t_game *game, size_t old_x, size_t old_y);
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