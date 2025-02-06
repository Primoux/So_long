/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:29:18 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/06 20:36:30 by enchevri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"

void	aff_map(t_game game)
{
	int i;

	i = 0;
	while (game.map[i])
	{
		ft_printf("%s\n", game.map[i]);
		i++;
	}
}