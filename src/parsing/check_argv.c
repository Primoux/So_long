/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:46:12 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/13 15:08:28 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

int	check_argv(char *argv)
{
	size_t	arg_len;

	arg_len = ft_strlen(argv);
	if (arg_len < 4 || ft_strncmp(&argv[arg_len - 4], ".ber", arg_len - 1) != 0)
		return (1);
	return (0);
}
