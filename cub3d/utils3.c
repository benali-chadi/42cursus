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