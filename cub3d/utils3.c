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

void    draw_rays(t_player player)
{
    int i;
    int r;
    int or_x;
    int or_y;

    i = 0;
    or_x = player.x_p;
    or_y = player.y_p;
    while (i < info.win_width)
    {
        r = 0;
        while (r < rays[i].distance)
        {
            player.x_p = or_x + (r * cos(rays[i].ray_angle));
            player.y_p = or_y + (r * sin(rays[i].ray_angle));
            put_pix(MINI_MAP * player.x_p, MINI_MAP * player.y_p, player.color);
            r++;
        }
        i++;
    }
}