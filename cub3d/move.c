#include "cube3d.h"

int key_destroy(int key, void * ptr)
{
    mlx_destroy_window(mlx_ptr, win_ptr);
    exit(0);
}

int key_press(int key, t_player *player)
{
    if (key == 126)
        player->walk_direction = 1; 
    if (key == 125)
        player->walk_direction = -1;
    if (key == 124)
        player->turn_direction = -3;
    if (key == 123)
        player->turn_direction = 3;
    if (key == 53)
    {
        mlx_destroy_window(mlx_ptr, win_ptr);
        exit(0);
    }
    return (0);
}

int key_release(int key, t_player *player)
{
    if (key == 126 || key == 125)
        player->walk_direction = 0;
    if (key == 124 || key == 123)
        player->turn_direction = 0;
    return (0);
}

int move(t_player *player)
{
    if (player->walk_direction == 1)
        if (!has_wall(player->y_p + INCREMENT_Y, player->x_p + INCREMENT_X))
        {
            player->y_p += INCREMENT_Y;
            player->x_p += INCREMENT_X; 
        }
    if (player->walk_direction == -1)
        if (!has_wall(player->y_p - INCREMENT_Y, player->x_p - INCREMENT_X))
        {
            player->y_p -= INCREMENT_Y;
            player->x_p -= INCREMENT_X; 
        }
    player->direction += player->turn_direction;
    player->direction = normalize_angle_deg(player->direction);
    init_img();
    if (count)
        put_character(*player);
    draw_map(player);
    mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
    return (0);
}