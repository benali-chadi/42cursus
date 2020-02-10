/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:40:58 by cbenali-          #+#    #+#             */
/*   Updated: 2020/02/07 17:51:14 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int     g_r[2];
int     g_count_i;
int     g_c;

void    resolution(char *line)
{
	int j;

	j = 0;
	while(*line)
	{
		if (ft_isdigit(*line) && *line != '0')
		{
			g_r[j] = ft_atoi(line);
			line += num(g_r[j]);
			j++;
		}
		if(*line)
			line++;
	}
	g_c++;
}

void    init_info(t_col f, t_col c, int count_j)
{
	g_info.map_x = count_j;
	g_info.map_y = g_count_i;
	g_info.win_width = g_r[0];
	g_info.win_height = g_r[1];
	give_col(f, 'f');
	give_col(c, 'c');
	g_info.win_x = g_info.map_x * TILE_SIZE;
	g_info.win_y = g_info.map_y * TILE_SIZE;
}

int     init_map(char *line)
{
	int j;

	j = 0;
	while(*line)
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

void    check_map()
{
	int i;
	int j;

	i = -1;
	while (++i < g_info.map_y)
	{
		j = -1;
		while (++j < g_info.map_x)
		{
			if ((i == 0 || i == g_info.map_y - 1) && g_map[i][j] != 1)
			{
				ft_putstr_fd("Error\nThe map must be surrounded by walls\n", 1);
				exit(-1);
			}
			if ((j == 0 || j == g_info.map_x - 1) && g_map[i][j] != 1)
			{
				ft_putstr_fd("Error\nThe map must be surrounded by walls\n", 1);
				exit(-1);
			}
		}
	}
}

void    read_file(int fd)
{
	char    *line;
	t_col   f;
	t_col   c;
	int     count_j;
	int     i;

	g_c = 0;
	g_count_i = 0;
	while (get_next_line(fd, &line))
	{
		i = 0;
		if (line[0] == 'R')
			resolution(line);
		else if (line[0] == 'F')
		{
			while (!ft_isdigit(line[i]))
				i++;
			flr(line + i, &f);
		}
		else if (line[0] == 'C')
		{
			while (!ft_isdigit(line[i]))
				i++;
			ceiling(line + i, &c);
		}
		else if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E')
			g_c++;
		else if (ft_isdigit(line[0]))
		{
			if (g_c == 8)
				count_j = init_map(line);
			else
			{
				ft_putstr_fd("Eroor\nNo enough info in the file\n", 1);
				exit(-1);
			}
		}
	}
	if (ft_isdigit(line[0]))
		count_j = init_map(line);
	init_info(f, c, count_j);
	check_map();
}
