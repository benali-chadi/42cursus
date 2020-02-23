/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 22:27:21 by cbenali-          #+#    #+#             */
/*   Updated: 2020/02/23 22:27:23 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int		all_n(char *s)
{
	int i;

	i = -1;
	if (!s)
		return (0);
	s = ft_strtrim(s, " \t");
	while (s[++i])
		if (s[i] < 48 || s[i] > 57)
			return (0);
	return (1);
}

void	check_comma(char *line)
{
	int coma;

	coma = 0;
	while (*line)
	{
		if (*line == ',')
		{
			coma++;
			if (coma > 2)
				ft_exit("Eroor\nUse only two commas\n");
		}
		line++;
	}
}
