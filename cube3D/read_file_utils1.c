/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:42:06 by cbenali-          #+#    #+#             */
/*   Updated: 2020/02/14 23:50:32 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

extern int g_c;
extern int g_r[2];

void	flr(char *line, t_col *f)
{
	char	**s;

	line = ft_strtrim(line + 1, " /t");
	check_comma(line);
	s = ft_split(line, ',');
	if (all_n(s[0]) && all_n(s[1]) && all_n(s[2]) && !s[3])
	{
		if (ft_atoi(s[0]) >= 0 && ft_atoi(s[0]) < 256 && ft_atoi(s[1]) >= 0 &&
			ft_atoi(s[1]) < 256 && ft_atoi(s[2]) >= 0 && ft_atoi(s[2]) < 256)
		{
			f->r = ft_atoi(s[0]);
			f->g = ft_atoi(s[1]);
			f->b = ft_atoi(s[2]);
		}
		else
			ft_exit("Error\nInvalid floor colors values\n");
	}
	else
		ft_exit("Error\nInvalid floor colors values\n");
	g_c++;
}

void	ceiling(char *line, t_col *c)
{
	char	**s;
	
	line = ft_strtrim(line + 1, " /t");
	check_comma(line);
	s = ft_split(line, ',');
	if (all_n(s[0]) && all_n(s[1]) && all_n(s[2]) && !s[3])
	{
		if (ft_atoi(s[0]) >= 0 && ft_atoi(s[0]) < 256 && ft_atoi(s[1]) >= 0 &&
			ft_atoi(s[1]) < 256 && ft_atoi(s[2]) >= 0 && ft_atoi(s[2]) < 256)
		{
			c->r = ft_atoi(s[0]);
			c->g = ft_atoi(s[1]);
			c->b = ft_atoi(s[2]);
		}
		else
			ft_exit("Error\nInvalid ceiling colors values\n");
	}
	else
		ft_exit("Error\nInvalid ceiling colors values\n");
	g_c++;
}

int		check_name(char *str)
{
	char **split;

	split = ft_split(str, '.');
	if (ft_strncmp(split[1], "cub", 20))
		return (0);
	if (split[2] != 0)
		return (0);
	return (1);
}

void	give_col(t_col fc, char c)
{
	if (c == 'f')
	{
		g_info.flr_co = fc.r;
		g_info.flr_co = (g_info.flr_co << 8) + fc.g;
		g_info.flr_co = (g_info.flr_co << 8) + fc.b;
	}
	else if (c == 'c')
	{
		g_info.cel_co = fc.r;
		g_info.cel_co = (g_info.cel_co << 8) + fc.g;
		g_info.cel_co = (g_info.cel_co << 8) + fc.b;
	}
}

void	resolution(char *line)
{
	int j;

	j = 0;
	while (*line)
	{
		if (ft_isdigit(*line) && *line)
		{
			if (j == 0)
				g_r[j] = (ft_atoi(line) > 2560) ? 2560 : ft_atoi(line);
			else if (j == 1)
				g_r[j] = (ft_atoi(line) > 1440) ? 1440 : ft_atoi(line);
			line += num(ft_atoi(line));
			j++;
		}
		if (*line)
			line++;
	}
	if (j != 2)
		ft_exit("Eroor\nNo or more than enough resolution data\n");
	g_c++;
}
