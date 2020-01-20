#include "cube3d.h"

void draw_wall(int x, float wall_height, int i)
{
    float   y;
    float   y_end;
    float   or_x;
    int     x_end;
    // int     color;
    int     x_tex;
    int     y_tex;

    y = (info.win_height / 2) - (wall_height / 2);
    int     top_pixel = y;
    y_end = y + wall_height;
    x_end = x + WALL_WIDTH;
    or_x = x;
    if (rays[x].is_vertical)
        x_tex = (int)rays[x].wall_hit_y % TILE_SIZE;
    else
        x_tex = (int)rays[x].wall_hit_x % TILE_SIZE;
    while (y < y_end)
    {
        x = or_x;
        y_tex = (y - top_pixel) * ((float)tex[i].img_height / wall_height);
        while (x < x_end)
        {
            int color = tex[i].tex[x_tex + (y_tex * tex[i].img_width)];
            if (x >= 0 && x < info.win_width && y >= 0 && y < info.win_height)
                put_pix(x, y, color);
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
            if (x >= 0 && x < info.win_width && y >= 0 && y < info.win_height)
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
            if (x >= 0 && x < info.win_width && y >= 0 && y < info.win_height)
                put_pix(x, y, info.cel_co);
            x++;
        }
        y++;
    }
}

void    init_tex(int i)
{
    if (tex[i].ptr)
        mlx_destroy_image(info.mlx_ptr, tex[i].ptr);
    if (i == 0)
        tex[i].ptr = mlx_xpm_file_to_image(info.mlx_ptr, "textures/mossy.xpm", &tex[i].img_width, &tex[i].img_height);
    else if (i == 1)
        tex[i].ptr = mlx_xpm_file_to_image(info.mlx_ptr, "textures/colorstone.xpm", &tex[i].img_width, &tex[i].img_height);
    else if (i == 2)
        tex[i].ptr = mlx_xpm_file_to_image(info.mlx_ptr, "textures/eagle.xpm", &tex[i].img_width, &tex[i].img_height);
    else if (i == 3)
        tex[i].ptr = mlx_xpm_file_to_image(info.mlx_ptr, "textures/redbrick.xpm", &tex[i].img_width, &tex[i].img_height);
    tex[i].tex = (int *)mlx_get_data_addr(tex[i].ptr, &tex[i].bpp, &tex[i].size_line, &tex[i].endian);
}

void    render_3d(float direction)
{
    int i;
    float dist_proj;
    float wall_height;
    float distance;

    draw_flr();
    draw_cel();
    i = -1;
    while (++i < 4)
        init_tex(i);
    dist_proj = (info.win_width / 2) / tan(FOV_ANGLE / 2);
    i = 0;
    while (i < info.win_width)
    {
        distance = rays[i].distance * cos(rays[i].ray_angle - (direction * VAL));
        wall_height = (TILE_SIZE / distance) * dist_proj;
        if (rays[i].is_ray_facing_up && !rays[i].is_vertical)
            draw_wall(i * WALL_WIDTH, wall_height, 0);
        else if (rays[i].is_ray_facing_down && !rays[i].is_vertical)
            draw_wall(i * WALL_WIDTH, wall_height, 1);
        else if (rays[i].is_ray_facing_left && rays[i].is_vertical)
            draw_wall(i * WALL_WIDTH, wall_height, 2);
        else if (rays[i].is_ray_facing_right && rays[i].is_vertical)
            draw_wall(i * WALL_WIDTH, wall_height, 3);
        i++;
    }
}