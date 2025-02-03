#include "./mlx/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	float	scale;
}			t_data;

int	close_window(int keycode, t_data *data)
{
	if (keycode == 65307) // ESC key
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(0);
	}
	return (0);
}

int	mouse_hook(int button, int x, int y, t_data *data)
{
	int	new_width;
	int	new_height;
	int	x_pos;
	int	y_pos;

	(void)x;
	(void)y;
	if (button == 4) // Scroll up
		data->scale *= 1.1;
	else if (button == 5) // Scroll down
		data->scale /= 1.1;
	// Clear the window
	mlx_clear_window(data->mlx, data->win);
	// Calculate new dimensions
	new_width = data->width * data->scale;
	new_height = data->height * data->scale;
	// Center the image
	x_pos = (800 - new_width) / 2;
	y_pos = (600 - new_height) / 2;
	// Draw the scaled image
	mlx_put_image_to_window(data->mlx, data->win, data->img, x_pos, y_pos);
	return (0);
}

int	main(void)
{
	t_data	data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 800, 600, "Resizable Image");
	data.scale = 1.0;
	// Load your image (replace "path_to_your_image.xpm" with your actual image path)
	int width, height;
	data.img = mlx_xpm_file_to_image(data.mlx, "cursor.xpm", &width,
			&height);
	if (!data.img)
	{
		fprintf(stderr, "Error loading image\n");
		return (1);
	}
	data.width = width;
	data.height = height;
	mlx_mouse_hook(data.win, mouse_hook, &data);
	mlx_key_hook(data.win, close_window, &data);
	// Initial draw
	mlx_put_image_to_window(data.mlx, data.win, data.img, (800 - width) / 2,
		(600 - height) / 2);
	mlx_loop(data.mlx);
	return (0);
}
