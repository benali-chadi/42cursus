#ifndef CUBE3D_H
# define CUBE3D_H

#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include "libft/libft.h"
#include <unistd.h>
#include <stdio.h>

# define INT_MAX 2147483647
# define PI 3.14159265359
# define TWO_PI 6.283118530
# define VAL (PI / 180)

# define FOV_ANGLE (60 * VAL)

# define TILE_SIZE 32
# define MAP_X 24
# define MAP_Y 23

# define WX (MAP_X * TILE_SIZE)
# define WY (MAP_Y * TILE_SIZE)

# define NUM_RAYS 50

# define INCREMENT_Y sin(player->direction * VAL) * 3
# define INCREMENT_X cos(player->direction * VAL) * 3



typedef struct s_player{
    float x_p;
    float y_p;
    // float phi_start;
    // float phi_end;
    int direction;
    int x_m;
    int y_m;
    int color;
    int turn_direction;
    int walk_direction;
}               t_player;

typedef struct  s_ray {
    float   ray_angle;
    float   wall_hit_x;
    float   wall_hit_y;
    float   distance;
    int     is_ray_facing_up;
    int     is_ray_facing_down;
    int     is_ray_facing_left;
    int     is_ray_facing_right;
    int     wall_hit_content;
}               t_rays;

typedef struct  s_ray_hit {
    float   x_intercept;
    float   y_intercept;
    float   x_step;
    float   y_step;
    int     found_hit;
    float   wall_hit_x;
    float   wall_hit_y;
    int     wall_content;

}               t_ray_hit;


void    *mlx_ptr;
void    *win_ptr;
void    *img_ptr;
int    *img_data;
// float ray_dis;
// float ray_angle;
t_rays  rays[WX];
int     count;

int     map[MAP_Y][MAP_X];

int     key_destroy(int key, void * ptr);
int     key_press(int key, t_player *player);
int     key_release(int key, t_player *player);
int     move(t_player *player);

int     has_wall(float y, float x);

void    init_img();
void    put_pix(int x, int y, int color);

void    put_character(t_player player);
void    put_square(t_player player, int color, int zero);
void    draw_map(t_player *player);

int     normalize_angle_deg(int angle);

int   cast_all_rays(t_player player);
// void    cats_ray(float ray_angle, int stripid, t_player player);
// void    give_values(t_ray_hit inter, float ray_angle, int stripid, float distance);
// void    vert_inter(t_ray_hit *vert, t_player player, int stripid, float ray_angle);
// void    horz_inter(t_ray_hit *horz, t_player player, int stripid, float ray_angle);

float   distance_between_points(float x1, float y1, float x2, float y2);
float   normalize_angle(float angle);

#endif