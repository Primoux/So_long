/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 20:15:07 by enchevri          #+#    #+#             */
/*   Updated: 2025/01/25 23:29:30 by enchevri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "./mlx/mlx.h"
#include <stdlib.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		x_max;
	int		y_max;
	int		x;
	int		y;
	int		i;

	i = 0;
	y_max = 1080;
	x_max = 1920;
	x = x_max / 2;
	y = y_max / 2;
	mlx = mlx_init();
	if (!mlx)
		return (EXIT_FAILURE);
	mlx_win = mlx_new_window(mlx, 1920, 720, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 720);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	while (i < x_max)
	{
		if (x < x_max && y < y_max)
		{
			my_mlx_pixel_put(&img, x, y, 0x0000FF00);
			mlx_put_image_to_window(mlx, mlx_win, img.img, x, y);
			x++;
			y++;
			ft_printf("1\n");
		}
		ft_printf("%d : x= %d, y = %d\n", i, x, y);
		i++;
	}
	mlx_loop(mlx);
	return (EXIT_SUCCESS);
}
