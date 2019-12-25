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
# define VAL PI / 180

# define FOV_ANGLE 60 * VAL

# define TILE_SIZE 40
# define MAP_X 24
# define MAP_Y 23

# define WX MAP_X * TILE_SIZE
# define WY MAP_Y * TILE_SIZE 

# define NUM_RAYS 6

# define INCREMENT_Y cos((player->direction + 30) * VAL) * 5
# define INCREMENT_X sin((player->direction + 30) * VAL) * 5



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
}           t_player;

typedef struct  s_ray {
    float ray_angle;
    float wall_hit_x;
    float wall_hit_y;
    float distance;
    int is_ray_facing_up;
    int is_ray_facing_down;
    int is_ray_facing_left;
    int is_ray_facing_right;
    int wall_hit_content;
}            t_rays;

void    *mlx_ptr;
void    *win_ptr;
void    *img_ptr;
char    *img_data;
int     *tab;
t_rays  rays[NUM_RAYS];
int     count;

int     map[MAP_Y][MAP_X];

int key_destroy(int key, void * ptr);
int key_press(int key, t_player *player);
int key_release(int key, t_player *player);
int move(t_player *player);

int has_wall(float y, float x);

void init_img();
void put_pix(int x, int y, int color);

void put_character(t_player player);
void put_square(t_player player, int color, int zero);
void draw_map(t_player *player);

void cast_rays(t_player player);
float distance_between_points(float x1, float y1, float x2, float y2);
float normalize_angle(float angle);

#endif