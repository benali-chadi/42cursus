#include "cube3d.h"


void    render_spt(int x, int y, int sp_size, int k)
{
    int color;
    int a;
    int i = 0;
    int j;
    int x_s, y_s;
    
    spt[k].ptr = mlx_xpm_file_to_image(info.mlx_ptr, "textures/pillar.xpm", &x_s, &y_s);
    spt[k].data = (int *)mlx_get_data_addr(spt[k].ptr, &a, &a, &a);

    while (i++ < sp_size)
    {
        if (x + i < 0 || x + i > info.win_width)
            continue;
        if(spt[k].distance >= rays[x + i].distance)
            continue;
        j = 0;
        while (j++ < sp_size)
        {
            color = spt[k].data[x_s * (j * y_s / sp_size) + (i * x_s / sp_size)];
            if (color != 0)
                put_pix(x + i, y + j, color);
        }
    }
}

void    ft_sprite(t_player player, int i)
{
    float   sp_size;
    float   x_inter;
    float   y_inter;
    float   sp_angle;
    
    sp_angle = atan2(spt[i].y - player.y_p, spt[i].x - player.x_p);
    while (sp_angle - (player.direction * VAL) > PI)
        sp_angle-= 2 * PI;
    while (sp_angle - (player.direction * VAL) < -PI)
        sp_angle+= 2 * PI;
    if (info.win_height > info.win_width)
        sp_size = (info.win_height / (float)spt[i].distance) * TILE_SIZE;
    else
        sp_size = (info.win_width / (float)spt[i].distance) * TILE_SIZE;
    y_inter = info.win_height / 2 - sp_size / 2;
    x_inter = (sp_angle - player.direction * VAL) / FOV_ANGLE * info.win_width + (info.win_width / 2 - sp_size / 2);
    render_spt(x_inter, y_inter, sp_size, i);
}

void    draw_wall(int x, float wall_height, int i)
{
    float   y;
    float   y_end;
    float   or_x;
    int     x_end;
    int     color;
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
            color = tex[i].tex[x_tex + (y_tex * tex[i].img_width)];
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

void    render_3d(float direction, t_player player)
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
    i = -1;
    while (++i < count)
        ft_sprite(player, i);
}