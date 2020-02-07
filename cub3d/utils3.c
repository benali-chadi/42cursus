/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:42:06 by cbenali-          #+#    #+#             */
/*   Updated: 2020/02/05 16:42:08 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void    flr(char *line, t_col *f)
{
    char **split;

    split = ft_split(line, ',');
    f->r = ft_atoi(split[0]);
    f->g = ft_atoi(split[1]);
    f->b = ft_atoi(split[2]);
}

void    ceiling(char *line, t_col *c)
{
    char **split;

    split = ft_split(line, ',');
    c->r = ft_atoi(split[0]);
    c->g = ft_atoi(split[1]);
    c->b = ft_atoi(split[2]);
}

int     check_name(char *str)
{
    char **split;

    split = ft_split(str, '.');
    if (ft_strncmp(split[1], "cub", 20))
        return (0);
    if (split[2] != 0)
        return (0);
    return (1);
}

void    give_col(t_col fc, char c)
{
    if (c == 'f')
    {
        info.flr_co = fc.r;
        info.flr_co = (info.flr_co << 8) + fc.g;
        info.flr_co = (info.flr_co << 8) + fc.b;
    }
    else if (c == 'c')
    {
        info.cel_co = fc.r;
        info.cel_co = (info.cel_co << 8) + fc.g;
        info.cel_co = (info.cel_co << 8) + fc.b;
    }
}
