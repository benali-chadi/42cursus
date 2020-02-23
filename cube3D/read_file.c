/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:40:58 by cbenali-          #+#    #+#             */
/*   Updated: 2020/02/13 23:18:28 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int		g_r[2];
int		g_count_i;
int		g_c;

int		check_no_we(char *line)
{
	if (line[0] == 'N')
	{
		if (line[1] == 'O')
			return (0);
		else
			ft_exit("Eroor\nInvalid name in no texture\n");
	}
	else if (line[0] == 'W')
	{
		if (line[1] == 'E')
			return (1);
		else
			ft_exit("Eroor\nInvalid name in we texture\n");
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
			ft_exit("Eroor\nInvalid name in ea texture\n");
	}
	else if (line[0] == 'S')
	{
		if (line[1] == 'O')
			return (1);
		else if (line[1] == ' ' || line[1] == '\t')
			return (2);
		else
			ft_exit("Eroor\nInvalid name in so or sp texture\n");
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

void	check_fl(char *line, int *j, t_col *f, t_col *c)
{
	if (line[0] == 'R' && (line[1] == ' ' || line[1] == '\t'))
		resolution(line);
	else if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
		flr(line, f);
	else if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
		ceiling(line, c);
	else if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W'
			|| line[0] == 'E')
		store_paths(line);
	else if (ft_isdigit(line[0]))
		*j = check_map_1(line);
	else if (line[0] != '\0')
		ft_exit("Eroor\nInvalid symbol\n");
}

void	read_file(int fd)
{
	char	*line;
	t_col	f;
	t_col	c;
	int		count_j;

	g_c = 0;
	g_count_i = 0;
	while (get_next_line(fd, &line))
	{
		check_fl(line, &count_j, &f, &c);
		free(line);
	}
	if (ft_isdigit(line[0]))
		count_j = init_map(line);
	free(line);
	init_info(f, c, count_j);
	check_map_2();
}
