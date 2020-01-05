#include "cube3d.h"

int     map[MAP_Y][MAP_X] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, // 0
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 1
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 2
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 3
    {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1}, // 4
    {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 5
    {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1}, // 6
    {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 7
    {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1}, // 8
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 9
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 10
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 11
    {1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1}, // 12
    {1,0,0,0,0,0,'N',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 13
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 14
    // {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 15
    {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 16
    {1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 17
    {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 18
    {1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 19
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 20
    {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 21
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} // 22
};

void init_pl_map(t_player *player)
{
    player->turn_direction = 0;
    player->walk_direction = 0;
    player->direction = 20;
    player->color = 0x48CFAF;
}

// void cast_ray(float ray_angle, int stripid, t_player player)
// {
//     int is_ray_facing_down;
//     int is_ray_facing_up;
//     int is_ray_facing_right;
//     int is_ray_facing_left;
//     float x_intercept, y_intercept;
//     float x_step, y_step;

//     // ray_angle = normalize_angle(ray_angle);
//     is_ray_facing_down = ray_angle > 0 && ray_angle < PI;
//     is_ray_facing_up = !is_ray_facing_down;
//     is_ray_facing_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
//     is_ray_facing_left = !is_ray_facing_right;

//     // HORIZONTAL INTERSECTION //
//     int found_horz_hit = 0;
//     float horz_wall_hit_x = 0;
//     float horz_wall_hit_y = 0;
//     int horz_wall_content = 0;

//     // Find the y-coordinate of the closest horizontal grid intersection
//     y_intercept = floor(player.y_p / TILE_SIZE) * TILE_SIZE;
//     y_intercept += is_ray_facing_down ? TILE_SIZE : -1;

//     // Find the x-coordinatr of the closest horizontal grid intersection
//     x_intercept = /*(ray_angle != 0) ? */player.x_p - (player.y_p - y_intercept) / tan(ray_angle)/* : player.x_p - (player.y_p - y_intercept) / tan(0.1)*/;

//     // Calculate the increment x_step and y_step
//     y_step = TILE_SIZE;
//     y_step *= is_ray_facing_up ? -1 : 1;

//     x_step = /*(ray_angle != 0) ? */y_step / tan(ray_angle)/* : y_step / tan(0.1)*/;

//     float next_horz_touch_x = x_intercept;
//     float next_horz_touch_y = y_intercept;
//     // Increment x_step and y_step until a wall is found
//     while (next_horz_touch_x >= 0 && next_horz_touch_x < (MAP_X * TILE_SIZE) && next_horz_touch_y >= 0 && next_horz_touch_y < (MAP_Y * TILE_SIZE))
//     {
//             if(has_wall(next_horz_touch_y, next_horz_touch_x))
//             {
                
//                 // Found a wall
//                 horz_wall_hit_x = next_horz_touch_x;
//                 horz_wall_hit_y = next_horz_touch_y;
//                 horz_wall_content = map[(int)next_horz_touch_y / TILE_SIZE][(int)next_horz_touch_x / TILE_SIZE];
//                 found_horz_hit = 1;
//                 break;
//             }
//             else
//             {
//                 next_horz_touch_x += x_step;
//                 next_horz_touch_y += y_step;
//             }
//     }
//     // VERTICAL INTERSECTION //
//     int found_vert_hit = 0;
//     float vert_wall_hit_x = 0;
//     float vert_wall_hit_y = 0;
//     int vert_wall_content = 0;

//     // Find the x-coordinate of the closest vertical grid intersection
//     x_intercept = floor(player.x_p / TILE_SIZE) * TILE_SIZE;
//     x_intercept += is_ray_facing_right ? TILE_SIZE : -1;

//     // Find the y-coordinate of the closest vertical grid intersection
//     y_intercept = player.y_p - (player.x_p - x_intercept) * tan(ray_angle);

//     // Calculate the increment x_step and y_step
//     x_step = TILE_SIZE;
//     x_step *= is_ray_facing_left ? -1 : 1;

//     y_step = x_step * tan(ray_angle);

//     float next_vert_touch_x = x_intercept;
//     float next_vert_touch_y = y_intercept;

//     // increment x_step and y_step until we find a wall
//     while (next_vert_touch_x >= 0 && next_vert_touch_x < (MAP_X * TILE_SIZE)  && next_vert_touch_y >= 0 && next_vert_touch_y < (MAP_Y * TILE_SIZE))
//     {
//             if (has_wall(next_vert_touch_y, next_vert_touch_x))
//             {
//                 // Found a wall hit
//                 vert_wall_hit_x = next_vert_touch_x;
//                 vert_wall_hit_y = next_vert_touch_y;
//                 vert_wall_content = map[(int)next_vert_touch_y / TILE_SIZE][(int)next_vert_touch_x / TILE_SIZE];
//                 found_vert_hit = 1;
//                 break;
//             }
//             else
//             {
//                 next_vert_touch_x += x_step;
//                 next_vert_touch_y += y_step;
//             }
//     }
//         // Calculate both horizontal and vertical hit distances and choose the smallest one
//         float horz_hit_distance = found_horz_hit > 0
//         ? distance_between_points(player.x_p, player.y_p, horz_wall_hit_x, horz_wall_hit_y)
//         : INT_MAX;
//         float vert_hit_distance = found_vert_hit > 0
//         ? distance_between_points(player.x_p, player.y_p, vert_wall_hit_x, vert_wall_hit_y)
//         : INT_MAX;
//         if (vert_hit_distance < horz_hit_distance)
//         {
//             rays[stripid].distance = vert_hit_distance;
//             rays[stripid].wall_hit_x = vert_wall_hit_x;
//             rays[stripid].wall_hit_y = vert_wall_hit_y;
//             rays[stripid].wall_hit_content = vert_wall_content;
//         }
//         else if (horz_hit_distance <= vert_hit_distance)
//         {
//             rays[stripid].distance = horz_hit_distance;
//             rays[stripid].wall_hit_x = horz_wall_hit_x;
//             rays[stripid].wall_hit_y = horz_wall_hit_y;
//             rays[stripid].wall_hit_content = horz_wall_content;
//         }
//         rays[stripid].ray_angle = ray_angle;
//         rays[stripid].is_ray_facing_down = is_ray_facing_down;
//         rays[stripid].is_ray_facing_up = is_ray_facing_up;
//         rays[stripid].is_ray_facing_left = is_ray_facing_left;
//         rays[stripid].is_ray_facing_right = is_ray_facing_right;
// }

// void cast_all_rays(t_player player)
// {
//     int     strip_id;
//     int     r;
//     float save;
//     float ray_angle;

//     ray_angle = (player.direction * VAL);
//     save = ray_angle;
//     strip_id = 0;
//     while (ray_angle < save + (60 * VAL))
//     {
//         // r = 0;        
//         ray_angle = normalize_angle(ray_angle);
//         cast_ray(ray_angle, strip_id, player);
//         ray_angle += FOV_ANGLE / WX;
//         strip_id++;
//     }
//         // printf("ray angle [%f]\n", ray_angle);
// }

// FOR CHARACTER //

void put_character(t_player player)
{
    int r;
    float save;
	float phi;
    int or_x;
    int or_y;

    or_x = player.x_p;
    or_y = player.y_p;
	r = 2;
	phi = 0;
    // ray_angle  = (player.direction * VAL);
    save = player.direction * VAL;
	while (phi <= 360)
	{
		player.x_p = or_x + (r * cos(phi * VAL));
		player.y_p = or_y + (r * sin(phi * VAL));
		put_pix(player.x_p, player.y_p, 0xffffff);
		phi += 0.1;
	}
   
    while (r < 60)
    {
        put_pix(player.x_p, player.y_p, 0xff0000);
        player.x_p = or_x + (r * cos(player.direction * VAL));
        player.y_p = or_y + (r * sin(player.direction * VAL));
        r++;
    }
    player.x_p = or_x;
    player.y_p = or_y;
    
    // Cast drawing

    int i = 0;
    // printf("save [%f]\n", save + (60 * VAL));
    // printf("Inc [%f]\n", FOV_ANGLE / 50);
    int end = cast_all_rays(player);
    // while (rays[i].ray_angle <= save + (20 * VAL))
    while (i < end)
    {
        r = 0;
        while (r < rays[i].distance)
        {
            player.x_p = or_x + (r * cos(rays[i].ray_angle));
            player.y_p = or_y + (r * sin(rays[i].ray_angle));
            put_pix(player.x_p, player.y_p, 0xffffff);
            r++;
        }
        // printf("ray angle [%f] distance [%f]\n", rays[i].ray_angle, rays[i].distance);
        i++;
    }
}

void draw_map(t_player *player)
{
    int i;
    int j;

    i = 0;
    j = 0;
    player->x_m = 0;
    player->y_m = 0;
    while (i < MAP_Y)
    {
        j = 0;
        while(j < MAP_X)
        {
            if(map[i][j] == 1)
                put_square(*player, 0x0351C1, 1);
            else if (map[i][j] == 2)
                put_square(*player, 0x00CF91, 1);
            else if (map[i][j] == 3)
                put_square(*player, 0x7367F0, 1);
            else if (map[i][j] == 4)
                put_square(*player, 0xB6BCF2, 1);
            else if (map[i][j] == 'N' && !count)
            {
                player->x_p = player->x_m;
                player->y_p = player->y_m;
                put_character(*player);
                count++;
            }
            player->x_m += TILE_SIZE;
            j++;
        }
        player->x_m = 0;
        player->y_m += TILE_SIZE;
        i++;
    }
}

int main()
{
    t_player player;
    count = 0;

    mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WX, WY, "mlx 1337");
    img_ptr = mlx_new_image(mlx_ptr, WX, WY);
    // Initialization
    // printf("%d\n", normalize_angle_deg(370));
    init_pl_map(&player);
    // Move
    mlx_hook(win_ptr, 2, 1L<<0, key_press, &player);
    mlx_hook(win_ptr, 3, 1L<<1, key_release, &player);
    mlx_hook(win_ptr, 17, 0L, key_destroy, (void *)0);
    mlx_loop_hook(mlx_ptr, move, &player);
	mlx_loop(mlx_ptr);
    return(0);
}