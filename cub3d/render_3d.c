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
            put_pix(x, y, 0xffffff);
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