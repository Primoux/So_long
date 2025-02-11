/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:29:18 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/09 15:10:19 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

void	aff_map(t_game game)
{
	int	i;

	i = 0;
	while (game.map[i])
	{
		ft_printf("%s\n", game.map[i]);
		i++;
	}
	printf("\n");
}
