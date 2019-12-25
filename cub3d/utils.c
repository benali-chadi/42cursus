#include "cube3d.h"

void	put_pix(int x, int y, int color)
{
	tab[x + y * WX] = color;
}

void init_img()
{
    int bpp;
	int size_line;
	int endian;
    if (img_ptr)
    {
        // mlx_destroy_image(mlx_ptr, img_ptr);
        free(img_ptr);
        free(img_data);
    }
	img_ptr = mlx_new_image(mlx_ptr, WX, WY);
	img_data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	tab = (int *)img_data;
}

void put_square(t_player player, int color, int zero)
{
    int d;
    int d2;
    int or_x;
    int or_y;

    or_y = player.y_m;
    or_x = player.x_m;
    d2 = player.y_m + TILE_SIZE;
    d = player.x_m + TILE_SIZE;
	while (player.y_m < d2)
	{
        player.x_m = or_x;
		while (player.x_m < d)
		{
            // if (!zero && (player.x_m == or_x || player.x_m == (d -1) || player.y_m == or_y || player.y_m == (d2 - 1)))
			//     mlx_pixel_put(mlx_ptr, win_ptr, player.x_m, player.y_m, color);
            // else if (zero)
                put_pix(player.x_m, player.y_m, color);
			player.x_m++;
		}
		player.y_m++;
	}
}

int has_wall(float y, float x)
{
    return (map[(int)y / TILE_SIZE][(int)x / TILE_SIZE] != 0);
}

// FOR CASTING //

float distance_between_points(float x1, float y1, float x2, float y2)
{
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
float normalize_angle(float angle)
{
    angle = remainder(angle, TWO_PI);
    if (angle < 0)
    {
        angle = TWO_PI * angle;
    }
    return (angle);
}