/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 02:05:49 by cbenali-          #+#    #+#             */
/*   Updated: 2020/02/13 02:05:57 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

extern int g_c;
extern int g_count_i;

int		check_map_1(char *line)
{
	int j;

	j = 0;
	if (g_c == 8)
		j = init_map(line);
	else
		ft_exit("Eroor\nNot enough info in the file or extra info\n");
	return (j);
}

void	check_ply_pos(int m_v, int *check)
{
	if (m_v != 'N' && m_v != 'S' && m_v != 'W' && m_v != 'E')
		ft_exit("Error\nInvalid player direction in map\n");
	(*check)++;
	if (*check > 1)
		ft_exit("Error\nMultiple player direction in map\n");
}

void	check_map_2(void)
{
	int i;
	int j;
	int check;

	check = 0;
	i = -1;
	while (++i < g_info.map_y)
	{
		j = -1;
		while (++j < g_info.map_x)
		{
			if (((i == 0 || i == g_info.map_y - 1) && g_map[i][j] != 1) ||
					((j == 0 || j == g_info.map_x - 1) && g_map[i][j] != 1))
				ft_exit("Error\nThe map must be surrounded by walls\n");
			if (ft_isalpha(g_map[i][j]))
				check_ply_pos(g_map[i][j], &check);
		}
	}
	if (!check)
		ft_exit("Error\nNo player direction in map\n");
}

int		init_map(char *line)
{
	int j;

	j = 0;
	while (*line)
	{
		if (ft_isdigit(*line))
		{
			g_map[g_count_i][j] = *line - 48;
			if (g_map[g_count_i][j] == 2)
				g_sprite++;
			j++;
		}
		else if (ft_isalpha(*line))
		{
			g_map[g_count_i][j] = *line;
			j++;
		}
		line++;
	}
	g_count_i++;
	return (j);
}
