#include "cube3d.h"

// INITIALIZATION // 

void init_pl_map(t_player *player)
{
    player->turn_direction = 0;
    player->walk_direction = 0;
    player->direction = 150;
    player->color = 0x48CFAF;
}

// void	put_pix(int x, int y, int color)
// {
// 	tab[x + y * WX] = color;
// }

// void init_img()
// {
//     int bpp;
// 	int size_line;
// 	int endian;
//     // if (img_ptr)
//     // {
//     //     // mlx_destroy_image(mlx_ptr, img_ptr);
//     //     free(img_ptr);
//     //     free(img_data);
//     // }
// 	img_ptr = mlx_new_image(mlx_ptr, WX, WY);
// 	img_data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
// 	tab = (int *)img_data;
// }


// int has_wall(float y, float x)
// {
//     return (map[(int)y / TILE_SIZE][(int)x / TILE_SIZE] != 0);
// }

// FOR CASTING //

// float distance_between_points(float x1, float y1, float x2, float y2)
// {
//     return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
// }
// float normalize_angle(float angle)
// {
//     angle = remainder(angle, TWO_PI);
//     if (angle < 0)
//     {
//         angle = TWO_PI * angle;
//     }
//     return (angle);
// }

void cast_ray(float ray_angle, int stripid, t_player player)
{
    int is_ray_facing_down;
    int is_ray_facing_up;
    int is_ray_facing_right;
    int is_ray_facing_left;
    float x_intercept, y_intercept;
    float x_step, y_step;

    ray_angle = normalize_angle(ray_angle);
    is_ray_facing_down = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
    is_ray_facing_up = !is_ray_facing_down;
    is_ray_facing_right = ray_angle > 0 && ray_angle < PI;
    is_ray_facing_left = !is_ray_facing_right;

    // HORIZONTAL INTERSECTION //
    int found_horz_hit = 0;
    float horz_wall_hit_x = 0;
    float horz_wall_hit_y = 0;
    int horz_wall_content = 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    y_intercept = floor(player.x_p / TILE_SIZE) * TILE_SIZE;
    y_intercept += is_ray_facing_down ? TILE_SIZE : 0;

    // Find the x-coordinatr of the closest horizontal grid intersection
    x_intercept = player.x_p + (y_intercept - player.y_p) / tan(ray_angle);

    // Calculate the increment x_step and y_step
    y_step = TILE_SIZE;
    y_step *= is_ray_facing_up ? -1 : 1;

    x_step = TILE_SIZE / tan(ray_angle);
    x_step *= (is_ray_facing_left && x_step > 0) ? -1 : 1;
    x_step *= (is_ray_facing_right && x_step < 0) ? -1 : 1;

    float next_horz_touch_x = x_intercept;
    float next_horz_touch_y = y_intercept;

    // Increment x_step and y_step until a wall is found
    while (next_horz_touch_x >= 0 && next_horz_touch_x <= WX && next_horz_touch_y >= 0 && next_horz_touch_y <= WY)
    {
        float x_to_check = next_horz_touch_x;
        float y_to_check = next_horz_touch_y + (is_ray_facing_up ? -1 : 0);

        if(has_wall(x_to_check, y_to_check))
        {
            // Found a wall
            horz_wall_hit_x = next_horz_touch_x;
            horz_wall_hit_y = next_horz_touch_y;
            horz_wall_content = map[(int)y_to_check / TILE_SIZE][(int)x_to_check / TILE_SIZE];
            found_horz_hit = 1;
            break;
        }
        else
        {
            next_horz_touch_x += x_step;
            next_horz_touch_y += y_step;
        }
    }

    // VERTICAL INTERSECTION //
    int found_vert_hit = 0;
    float vert_wall_hit_x = 0;
    float vert_wall_hit_y = 0;
    int vert_wall_content = 0;

    // Find the x-coordinate of the closest vertical grid intersection
    x_intercept = floor(player.x_p / TILE_SIZE) * TILE_SIZE;
    x_intercept += is_ray_facing_right ? TILE_SIZE : 0;

    // Find the y-coordinate of the closest vertical grid intersection
    y_intercept = player.y_p + (x_intercept - player.x_p) * tan(ray_angle);

    // Calculate the increment x_step and y_step
    x_step = TILE_SIZE;
    x_step *= is_ray_facing_left ? -1 : 1;

    y_step = TILE_SIZE * tan(ray_angle);
    y_step *= (is_ray_facing_up && y_step > 0) ? -1 : 1;
    y_step *= (is_ray_facing_down && y_step < 0) ? -1 : 1;

    float next_vert_touch_x = x_intercept;
    float next_vert_touch_y = y_intercept;

    // increment x_step and y_step until we find a wall
    while (next_horz_touch_x >= 0 && next_horz_touch_x <= WX && next_horz_touch_y >= 0 && next_horz_touch_y <= WY)
    {
        float x_to_check_vert = next_vert_touch_x + (is_ray_facing_left ? -1 : 0);
        float y_to_check_vert = next_vert_touch_y;

        if (has_wall(x_to_check_vert, y_to_check_vert))
        {
            // Found a wall hit
            vert_wall_hit_x = next_vert_touch_x;
            vert_wall_hit_y = next_vert_touch_y;
            vert_wall_content = map[(int)y_to_check_vert / TILE_SIZE][(int)x_to_check_vert / TILE_SIZE];
            found_vert_hit = 1;
            break;
        }
        else
        {
            next_vert_touch_x += x_step;
            next_vert_touch_y += y_step;
        }
    }
        // Calculate both horizontal and vertical hit distances and choose the smallest one
        float horz_hit_distance = found_horz_hit
        ? distance_between_points(player.x_p, player.y_p, horz_wall_hit_x, horz_wall_hit_y)
        : INT_MAX;
        float vert_hit_distance = found_vert_hit
        ? distance_between_points(player.x_p, player.y_p, vert_wall_hit_x, vert_wall_hit_y)
        : INT_MAX;
        if (vert_hit_distance < horz_wall_hit_y)
        {
            rays[stripid].distance = vert_hit_distance;
            rays[stripid].wall_hit_x = vert_wall_hit_x;
            rays[stripid].wall_hit_y = vert_wall_hit_y;
            rays[stripid].wall_hit_content = vert_wall_content;
        }
        else
        {
            rays[stripid].distance = horz_hit_distance;
            rays[stripid].wall_hit_x = horz_wall_hit_x;
            rays[stripid].wall_hit_y = horz_wall_hit_y;
            rays[stripid].wall_hit_content = horz_wall_content;
        }
        rays[stripid].ray_angle = ray_angle;
        rays[stripid].is_ray_facing_down = is_ray_facing_down;
        rays[stripid].is_ray_facing_up = is_ray_facing_up;
        rays[stripid].is_ray_facing_left = is_ray_facing_left;
        rays[stripid].is_ray_facing_right = is_ray_facing_right;
}

void cast_all_rays(t_player player)
{
    float   ray_angle;
    int     strip_id;

    strip_id = 0;
    ray_angle = player.direction * VAL - (FOV_ANGLE / 2);
    while (strip_id < NUM_RAYS)
    {
        cast_ray(ray_angle, strip_id, player);
        ray_angle += FOV_ANGLE / NUM_RAYS;
        strip_id++;
    }
}

// DRAWING //

void draw_rays(t_player player)
{
    int i;
    int or_x;
    int or_y;
    int distance;
    int direction;
    or_x = player.x_p;
    or_y = player.y_p;
    i = 0;
    direction = player.direction * VAL;
    while (i < NUM_RAYS)
    {
        distance = rays[i].distance;
        player.x_p = or_x;
        player.y_p = or_y;
        while (distance)
        {
            player.x_p = or_x + ( distance * sin(rays[i].ray_angle));
            player.y_p = or_y + ( distance * cos(rays[i].ray_angle));
            put_pix(player.x_p, player.y_p, player.color);
            // rays[i].wall_hit_x--;
            // rays[i].wall_hit_y--;
            distance--;
        }
        // direction += 30 * VAL;
        i++;
    }
}

// FOR CHARACTER //

void put_character(t_player player)
{
    int r;
	float phi;
    int or_x;
    int or_y;

    or_x = player.x_p;
    or_y = player.y_p;
	r = 2;
	phi = 0;
	while (phi <= 360)
	{
		player.x_p = or_x + (r * sin(phi * VAL));
		player.y_p = or_y + (r * cos(phi * VAL));
		put_pix(player.x_p, player.y_p, 0xffffff);
		phi += 0.1;
	}

    // DRAW VIEW ANGLE

    // phi = player.phi_start;
    // while (r < 60)
    // {
    //     player.phi_start = phi; 
    //     while (player.phi_start < player.phi_end)
    //     {
    //         player.x_p = or_x + (r * sin(player.phi_start * VAL));
	//     	player.y_p = or_y + (r * cos(player.phi_start * VAL));
    //         mlx_pixel_put(mlx_ptr, win_ptr, player.x_p, player.y_p, player.color);
	//     	player.phi_start += 0.1;
    //     }
    //     r++;
    // }
    while (r < 60)
    {
        put_pix(player.x_p, player.y_p, 0xffffff);
        player.x_p = or_x + (r * sin((player.direction + 30) * VAL));
        player.y_p = or_y + (r * cos((player.direction + 30) * VAL));
        r++;
    }
    // player.x_p = or_x;
    // player.y_p = or_y;

    // CASTING RAYS

    // cast_all_rays(player);
    // draw_rays(player);
}

// void put_square(t_player player, int color, int zero)
// {
//     int d;
//     int d2;
//     int or_x;
//     int or_y;

//     or_y = player.y_m;
//     or_x = player.x_m;
//     d2 = player.y_m + TILE_SIZE;
//     d = player.x_m + TILE_SIZE;
// 	while (player.y_m < d2)
// 	{
//         player.x_m = or_x;
// 		while (player.x_m < d)
// 		{
//             // if (!zero && (player.x_m == or_x || player.x_m == (d -1) || player.y_m == or_y || player.y_m == (d2 - 1)))
// 			//     mlx_pixel_put(mlx_ptr, win_ptr, player.x_m, player.y_m, color);
//             // else if (zero)
//                 put_pix(player.x_m, player.y_m, color);
// 			player.x_m++;
// 		}
// 		player.y_m++;
// 	}
// }

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

// TO MOVE //

// int key_press(int key, t_player *player)
// {
//     if (key == 126 && !has_wall(player->y_p + INCREMENT_Y, player->x_p + INCREMENT_X))
//         player->walk_direction = 1; 
//     if (key == 125 && !has_wall(player->y_p - INCREMENT_Y, player->x_p - INCREMENT_X))
//         player->walk_direction = -1;
//     if (key == 124)
//         player->turn_direction = -1;
//     if (key == 123)
//         player->turn_direction = 1;
//     if (key == 53)
//     {
//         mlx_destroy_window(mlx_ptr, win_ptr);
//         exit(0);
//     }
//     return (0);
// }

// int key_release(int key, t_player *player)
// {
//     if (key == 126 || key == 125)
//         player->walk_direction = 0;
//     if (key == 124 || key == 123)
//         player->turn_direction = 0;
//     return (0);
// }

// int move(int key, t_player *player)
// {
//     if (player->walk_direction == 1)
//     {
//         player->y_p += INCREMENT_Y;
//         player->x_p += INCREMENT_X; 
//     }  
//     if (player->walk_direction == -1)
//     {
//         player->y_p -= INCREMENT_Y;
//         player->x_p -= INCREMENT_X; 
//     }
//     if (player->turn_direction == -1)
//     {
//         // player->phi_start -= 10;
//         // player->phi_end -= 10;
//         player->direction -= 10;
//     }
//     if (player->turn_direction == 1)
//     {
//         // player->phi_start += 10;
//         // player->phi_end += 10;
//         player->direction += 10;
//     }
//     // else if (key == 53)
//     // {
//     //     mlx_destroy_window(mlx_ptr, win_ptr);
//     //     exit(0);
//     // }
//     // mlx_clear_window(mlx_ptr, win_ptr);
//     init_img();
//     put_character(*player);
//     draw_map(player);
//     mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
//     // printf("x = %f, y = %f\n", player->x_p, player->y_p);
//     return (0);
// }

int main()
{
    t_player player;
    count = 0;

    mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WX, WY, "mlx 1337");
    // Initialization
    init_pl_map(&player);
    init_img();
    // Draw first scene
    draw_map(&player);
    put_character(player);
    mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
    // Move
    mlx_hook(win_ptr, 2, 1L << 0, key_press, &player);
    mlx_hook(win_ptr, 3, 1L << 1, key_release, &player);
    // mlx_hook(win_ptr, 2, 0, move, &player);
    // mlx_loop_hook(mlx_ptr, move, &player);
	mlx_loop(mlx_ptr);
    return(0);
}