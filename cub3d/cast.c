#include "cube3d.h"

void horz_inter(t_ray_hit *horz, t_player player, int stripid, float ray_angle)
{
    float next_touch_x;
    float next_touch_y;

    horz->y_intercept = floor(player.y_p / TILE_SIZE) * TILE_SIZE;
    horz->y_intercept += rays[stripid].is_ray_facing_down ? TILE_SIZE : -1;
    
    horz->x_intercept = (ray_angle != 0) ? player.x_p - (player.y_p - horz->y_intercept) / tan(ray_angle) : player.x_p - (player.y_p - horz->y_intercept) / tan(0.1);

    horz->y_step = TILE_SIZE;
    horz->y_step *= rays[stripid].is_ray_facing_up ? -1 : 1;

    horz->x_step = (ray_angle != 0) ? horz->y_step / tan(ray_angle) : horz->y_step / tan(0.1);

    next_touch_x = horz->x_intercept;
    next_touch_y = horz->y_intercept;
    while (next_touch_x >= 0 && next_touch_x < (MAP_X * TILE_SIZE) && next_touch_y >= 0 && next_touch_y < (MAP_Y * TILE_SIZE))
    {
        if(has_wall(next_touch_y, next_touch_x))
        {
            horz->wall_hit_x = next_touch_x;
            horz->wall_hit_y = next_touch_y;
            horz->wall_content = map[(int)next_touch_y / TILE_SIZE][(int)next_touch_x / TILE_SIZE];
            horz->found_hit = 1;
            break;
        }
        else
        {
            next_touch_x += horz->x_step;
            next_touch_y += horz->y_step;
        }
    }
}

void vert_inter(t_ray_hit *vert, t_player player, int stripid, float ray_angle)
{
    float next_touch_x;
    float next_touch_y;

    vert->x_intercept = floor(player.x_p / TILE_SIZE) * TILE_SIZE;
    vert->x_intercept += rays[stripid].is_ray_facing_right ? TILE_SIZE : -1;
    
    vert->y_intercept = ray_angle != 0 ? player.y_p - (player.x_p - vert->x_intercept) * tan(ray_angle) : player.y_p - (player.x_p - vert->x_intercept) * tan(0.1);

    vert->x_step = TILE_SIZE;
    vert->x_step *= rays[stripid].is_ray_facing_left ? -1 : 1;

    vert->y_step = ray_angle != 0 ? vert->x_step * tan(ray_angle) : vert->x_step * tan(0.1);

    next_touch_x = vert->x_intercept;
    next_touch_y = vert->y_intercept;
    while (next_touch_x >= 0 && next_touch_x < (MAP_X * TILE_SIZE) && next_touch_y >= 0 && next_touch_y < (MAP_Y * TILE_SIZE))
    {
        if(has_wall(next_touch_y, next_touch_x))
        {
            vert->wall_hit_x = next_touch_x;
            vert->wall_hit_y = next_touch_y;
            vert->wall_content = map[(int)next_touch_y / TILE_SIZE][(int)next_touch_x / TILE_SIZE];
            vert->found_hit = 1;
            break;
        }
        else
        {
            next_touch_x += vert->x_step;
            next_touch_y += vert->y_step;
        }
    }    
}

void    give_values(t_ray_hit inter, float ray_angle, int stripid, float distance)
{
    rays[stripid].distance = distance;
    rays[stripid].wall_hit_x = inter.wall_hit_x;
    rays[stripid].wall_hit_y = inter.wall_hit_y;
    rays[stripid].wall_hit_content = inter.wall_content;
    rays[stripid].ray_angle = ray_angle;
}

void setup(t_ray_hit *vert, t_ray_hit *horz)
{
    vert->found_hit = 0;
    vert->wall_hit_x = 0;
    vert->wall_hit_y = 0;
    vert->wall_content = 0;
    vert->x_intercept = 0;
    vert->y_intercept = 0;
    vert->x_step = 0;
    vert->y_step = 0;

    horz->found_hit = 0;
    horz->wall_hit_x = 0;
    horz->wall_hit_y = 0;
    horz->wall_content = 0;
    horz->x_intercept = 0;
    horz->y_intercept = 0;
    horz->x_step = 0;
    horz->y_step = 0;
}

void    cast_ray(float ray_angle, int stripid, t_player player)
{
    t_ray_hit horz;
    t_ray_hit vert;
    // float horz_hit_distance;
    // float vert_hit_distance;

    rays[stripid].is_ray_facing_down = ray_angle > 0 && ray_angle < PI;
    rays[stripid].is_ray_facing_up = !rays[stripid].is_ray_facing_down;
    rays[stripid].is_ray_facing_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
    rays[stripid].is_ray_facing_left = !rays[stripid].is_ray_facing_right;
    setup(&vert, &horz);
    horz_inter(&horz, player, stripid, ray_angle);
    vert_inter(&vert, player, stripid, ray_angle);
    float horz_hit_distance = horz.found_hit
    ? distance_between_points(player.x_p, player.y_p, horz.wall_hit_x, horz.wall_hit_y)
    : INT_MAX;
    float vert_hit_distance = vert.found_hit
    ? distance_between_points(player.x_p, player.y_p, vert.wall_hit_x, vert.wall_hit_y)
    : INT_MAX;
    if (vert_hit_distance < horz_hit_distance)
        give_values(vert, ray_angle, stripid, vert_hit_distance);
    else
        give_values(horz, ray_angle, stripid, horz_hit_distance); 
}

int    cast_all_rays(t_player player)
{
    int     strip_id;
    int     r;
    float save;
    float ray_angle;

    ray_angle = (player.direction - 30) * VAL;
    // save = (player.direction + 60) * VAL;
    save = normalize_angle_deg(player.direction + 60) * VAL;
    strip_id = 0;
    while (strip_id < WX)
    {        
        ray_angle = normalize_angle(ray_angle);
        cast_ray(ray_angle, strip_id, player);
        ray_angle += FOV_ANGLE / WX;
        strip_id++;
    }
    return (strip_id);
}