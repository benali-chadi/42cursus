#include "cube3d.h"

int     key_destroy(int key, void *ptr)
{
    key = (int)ptr;
    mlx_destroy_window(info.mlx_ptr, info.win_ptr);
    exit(0);
}

int     key_press(int key, t_player *player)
{
    if (key == 13)
        player->walk_direction = 1; 
    if (key == 1)
        player->walk_direction = -1;
    if (key == 0)
        player->walk_direction = -2;
    if (key == 2)
        player->walk_direction = 2;
    if (key == 124)
        player->turn_direction = 3;
    if (key == 123)
        player->turn_direction = -3;
    if (key == 53)
    {
        mlx_destroy_window(info.mlx_ptr, info.win_ptr);
        exit(0);
    }
    return (0);
}

int     key_release(int key, t_player *player)
{
    if (key == 1 || key == 13 || key == 2 || key == 0)
        player->walk_direction = 0;
    if (key == 124 || key == 123)
        player->turn_direction = 0;
    return (0);
}

void    render(t_player *player)
{
    init_img();
    cast_all_rays(*player);
    render_3d(player->direction);
    draw_map(player);
    // put_character(*player);
    // draw_rays(*player);
    mlx_put_image_to_window(info.mlx_ptr, info.win_ptr, info.img_ptr, 0, 0);
}

int     move(t_player *player)
{
    if (player->walk_direction == 1)
    {
        if (!has_wall((player->y_p + INCREMENT_Y_UD * 10), (player->x_p + INCREMENT_X_UD * 10)))
        {
            player->y_p += INCREMENT_Y_UD;
            player->x_p += INCREMENT_X_UD; 
        }
    }
    if (player->walk_direction == -1)
    {
        if (!has_wall((player->y_p - INCREMENT_Y_UD * 10), (player->x_p - INCREMENT_X_UD * 10)))
        {
            player->y_p -= INCREMENT_Y_UD;
            player->x_p -= INCREMENT_X_UD; 
        }
    }
    if (player->walk_direction == 2)
        if (!has_wall((player->y_p + INCREMENT_Y_LR * 10), (player->x_p + INCREMENT_X_LR * 10)))
        {
            player->y_p += INCREMENT_Y_LR;
            player->x_p += INCREMENT_X_LR;
        }
    if (player->walk_direction == -2)
        if (!has_wall((player->y_p - INCREMENT_Y_LR * 10), (player->x_p - INCREMENT_X_LR * 10)))
        {
            player->y_p -= INCREMENT_Y_LR;
            player->x_p -= INCREMENT_X_LR;
        }
    player->direction += player->turn_direction;
    // player->direction = normalize_angle_deg(player->direction);
    render(player);
    return (0);
}