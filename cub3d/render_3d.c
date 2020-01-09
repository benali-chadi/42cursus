#include "cube3d.h"

void draw_wall(int x, float wall_height)
{
    int y;
    int y_end;
    int x_end;
    int or_x;

    y = (info.win_height / 2) - (wall_height / 2);
    y_end = y + wall_height;
    x_end = x + WALL_WIDTH;
    or_x = x;

    while (y < y_end)
    {
        x = or_x;
        while (x < x_end)
        {
            put_pix(x, y, 0x14C878);
            x++;
        }
        y++;
    }
}

void    draw_flr()
{
    int y;
    int x;

    y = info.win_height / 2;
    while (y < info.win_height)
    {
        x = 0;
        while (x < info.win_width)
        {
            put_pix(x, y, info.flr_co);
            x++;
        }
        y++;
    }
}

void    draw_cel()
{
    int x;
    int y;
    int y_end;

    y = 0;
    y_end = info.win_height / 2;
    while (y < y_end)
    {
        x = 0;
        while (x < info.win_width)
        {
            put_pix(x, y, info.cel_co);
            x++;
        }
        y++;
    }
}

void    render_3d(float direction)
{
    int i;
    float dist_proj;
    float wall_height;
    float distance;

    draw_flr();
    draw_cel();
    dist_proj = (info.win_width / 2) / tan(FOV_ANGLE / 2);
    i = 0;
    while (i < info.win_width)
    {
        distance = rays[i].distance * cos(rays[i].ray_angle - (direction * VAL));
        wall_height = (info.tile_size_y / distance) * dist_proj;
        draw_wall(i * WALL_WIDTH, wall_height);
        i++;
    }
}