#include "cube3d.h"

# define INCREMENT_Y cos((player->phi_start + 30) * VAL) * 5
# define INCREMENT_X sin((player->phi_start + 30) * VAL) * 5;

void    *mlx_ptr;
void    *win_ptr;
int     wx;
int     wy;
int     count;

void init_pl_map(t_player *player)
{
    player->phi_start = 150;
    player->phi_end = 210;
    player->color = 0x48CFAF;
}

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
		mlx_pixel_put(mlx_ptr, win_ptr, player.x_p, player.y_p, player.color);
		phi += 0.1;
	}
    phi = player.phi_start;
    while (r < 60)
    {
        player.phi_start = phi;
        while (player.phi_start < player.phi_end)
        {
            player.x_p = or_x + (r * sin(player.phi_start * VAL));
	    	player.y_p = or_y + (r * cos(player.phi_start * VAL));
            mlx_pixel_put(mlx_ptr, win_ptr, player.x_p, player.y_p, player.color);
	    	player.phi_start += 0.1;
        }
        r++;
    }
}

void put_square(t_player player, int color)
{
    int d;
    int d2;
    int or_x;

    or_x = player.x_m;
    d2 = player.y_m + TILE_SIZE;
    d = player.x_m + TILE_SIZE;
	while (player.y_m < d2)
	{
        player.x_m = or_x;
		while (player.x_m < d)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, player.x_m, player.y_m, color);
			player.x_m++;
		}
		player.y_m++;
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
                put_square(*player, 0x0351C1);
            else if (map[i][j] == 2)
                put_square(*player, 0x00CF91);
            else if (map[i][j] == 3)
                put_square(*player, 0x7367F0);
            else if (map[i][j] == 4)
                put_square(*player, 0xB6BCF2);
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

int has_wall(t_player player, int con)
{
    float fory;
    float forx;

    fory = cos((player.phi_start + 30) * VAL) * 5;
    forx = sin((player.phi_start + 30) * VAL) * 5;
    player.y_p = (con == 1 ? player.y_p + fory : player.y_p - fory);
    player.x_p = (con == 1 ? player.x_p + forx : player.x_p - forx);
    return (map[(int)player.y_p / TILE_SIZE][(int)player.x_p / TILE_SIZE] != 0);
}

int move(int key, t_player *player)
{
    if (key == 126 && !has_wall(*player, 1))
    {
        player->y_p += INCREMENT_Y;
        player->x_p += INCREMENT_X; 
    }  
    else if (key == 125 && !has_wall(*player, 2))
    {
        player->y_p -= INCREMENT_Y;
        player->x_p -= INCREMENT_X; 
    }
    else if (key == 124)
    {
        player->phi_start -= 10;
        player->phi_end -= 10;
    }
    else if (key == 123)
    {
        player->phi_start += 10;
        player->phi_end += 10;
    }
    else if (key == 53)
    {
        mlx_destroy_window(mlx_ptr, win_ptr);
        exit(0);
    }
    mlx_clear_window(mlx_ptr, win_ptr);
    put_character(*player);
    draw_map(player);
    // printf("x = %f, y = %f\n", player->x_p, player->y_p);
    return (0);
}

// int loop(int key, t_player *player)
// {
//     mlx_clear_window(mlx_ptr, win_ptr);
//     draw_map(player);
//     put_character(*player);
//     return(0);
// }

int main()
{
    t_player player;
    count = 0;

    wx = MAP_X * TILE_SIZE;
    wy = MAP_Y * TILE_SIZE;
    mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, wx, wy, "mlx 1337");
    init_pl_map(&player);
    draw_map(&player);
    put_character(player);
    mlx_key_hook(win_ptr, move, &player);
    // mlx_loop_hook(mlx_ptr, move, &player);
	mlx_loop(mlx_ptr);
    return(0);
}