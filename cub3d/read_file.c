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

int		check_no_we(char *line)
{
	if (line[0] == 'N')
	{
		if (line[1] == 'O')
			return (0);
		else
			ft_exit("Eroor\nInvalid name in north texture\n");
	}
	else if (line[0] == 'W')
	{
		if (line[1] == 'E')
			return (1);
		else
			ft_exit("Eroor\nInvalid name in west texture\n");
	}
	return (2);
}

int		check_ea_s(char *line)
{
	if (line[0] == 'E')
	{
		if (line[1] == 'A')
			return (0);
		else
			ft_exit("Eroor\nInvalid name in east texture\n");
	}
	else if (line[0] == 'S')
	{
		if (line[1] == 'O')
			return (1);
		else if (line[1] == ' ' || line[1] == '\t')
			return (2);
		else
			ft_exit("Eroor\nInvalid name in south texture, or sprite texture\n");
	}
	return (3);
}

void	store_paths(char *line)
{
	if (!check_no_we(line))
		g_info.paths.no = ft_strtrim(line + 2, " \t");
	else if (check_no_we(line) == 1)
		g_info.paths.we = ft_strtrim(line + 2, " \t");
	if (!check_ea_s(line))
		g_info.paths.ea = ft_strtrim(line + 2, " \t");
	else if (check_ea_s(line) == 1)
		g_info.paths.so = ft_strtrim(line + 2, " \t");
	else if (check_ea_s(line) == 2)
		g_info.paths.sp = ft_strtrim(line + 1, " \t");
	g_c++;
}

void    read_file(int fd)
{
	char    *line;
	t_col   f;
	t_col   c;
	int     count_j;

	g_c = 0;
	g_count_i = 0;
	while (get_next_line(fd, &line))
	{
		if (line[0] == 'R')
			resolution(line);
		else if (line[0] == 'F')
			flr(line, &f);
		else if (line[0] == 'C')
			ceiling(line, &c);
		else if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E')
			store_paths(line);
		else if (ft_isdigit(line[0]))
			count_j = check_map_1(line);
	}
	if (ft_isdigit(line[0]))
		count_j = init_map(line);
	init_info(f, c, count_j);
	check_map_2();
}