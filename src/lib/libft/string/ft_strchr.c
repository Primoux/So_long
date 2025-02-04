/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:40:05 by enchevri          #+#    #+#             */
/*   Updated: 2025/01/22 14:49:47 by enchevri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int srch_char)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)srch_char)
		{
			return ((char *)&str[i]);
		}
		i++;
	}
	if (str[i] == (char)srch_char)
		return ((char *)&str[i]);
	return (0);
}
