#include <mlx.h>
#include <math.h>
#include "libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include "cube3d.h"

void    *mlx_ptr;
void    *win_ptr;
void    *img_ptr;
char    *img_data;
int		*tab;
// int		count;

int	deal_key(int key, void *ptr)
{
	printf("%d\n", key);
	// ft_putnbr_fd(key, 1);
	// ft_putchar_fd('\n', 1);
	return (0);
}
// void drawcircle(void *mlx_ptr, void *win_ptr, int xc, int yc, int x, int y)
// {
// 	mlx_pixel_put(mlx_ptr, win_ptr, xc+x, yc+y, 0xff0000);
// 	mlx_pixel_put(mlx_ptr, win_ptr, xc-x, yc+y, 0xff0000);
// 	mlx_pixel_put(mlx_ptr, win_ptr, xc+x, yc-y, 0xff0000);
// 	mlx_pixel_put(mlx_ptr, win_ptr, xc-x, yc-y, 0xff0000);
// 	mlx_pixel_put(mlx_ptr, win_ptr, xc+y, yc+x, 0xff0000);
// 	mlx_pixel_put(mlx_ptr, win_ptr, xc-y, yc+x, 0xff0000);
// 	mlx_pixel_put(mlx_ptr, win_ptr, xc+y, yc-x, 0xff0000);
// 	mlx_pixel_put(mlx_ptr, win_ptr, xc-y, yc-x, 0xff0000);
// }

void	draw_img(int x, int y, int color)
{
	tab[x + y * WX] = color;
}

void	put_square(t_player player, int color, int zero)
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
                draw_img(player.x_m, player.y_m, 0xffffff);
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
                put_square(*player, 0x0351C1, 1);
            else if (map[i][j] == 2)
                put_square(*player, 0x00CF91, 1);
            else if (map[i][j] == 3)
                put_square(*player, 0x7367F0, 1);
            else if (map[i][j] == 4)
                put_square(*player, 0xB6BCF2, 1);
            // else if (map[i][j] == 'N' && !count)
            // {
            //     player->x_p = player->x_m;
            //     player->y_p = player->y_m;
            //     put_character(*player);
            //     count++;
            // }
            player->x_m += TILE_SIZE;
            j++;
        }
        player->x_m = 0;
        player->y_m += TILE_SIZE;
        i++;
    }
}

void init_img()
{
	int bpp;
	int size_line;
	int endian;

	img_ptr = mlx_new_image(mlx_ptr, WX, WY);
	img_data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	tab = (int *)img_data;
	draw_img(WX / 2, WY / 2, 0xffffff);
}

int main()
{
	t_player player;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WX, WY, "mlx 1337");
	// mlx_key_hook(win_ptr, deal_key, (void *)0);
	init_img();
	draw_map(&player);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	//draw square || triangle || rectangle

	// int d;
	// int r;
	// int count;

	// d = 300;
	// x = 200;
	// y = 400;
	// // r = 100;
	// while (y > 200)
	// {
	// 	x = 200;
	// 	while (x < d)
	// 	{
	// 		mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xff0000);
	// 		x++;
	// 	}
	// 	// x = r++;
	// 	d--;
	// 	y--;
		
	// }
	
	// draw circle
	// int xc;
	// int yc;
	// int r;
	// int d;

	// xc = 400;
	// yc = 100;
	// r = 80;
	// x = 0;
	// y = r;
	// d = r;
	//ber... algo
	// drawcircle(mlx_ptr, win_ptr, xc, yc, x, y);
	// while (y >= x)
	// {
	// 	x++;
	// 	if (d > 0)
	// 	{
	// 		y--;
	// 		d = d + 4 * (x - y) + 10;
	// 	}
	// 	else
	// 		d = d + 4 * x + 6;
	// 	drawcircle(mlx_ptr, win_ptr, xc, yc, x, y);
	// }

	// draw circle 2 :
	// int x;
	// int y;
	// int r;
	// float pi;
	// float phi;
	// float val;
	// int color;


	// r = 200;
	// phi = 0;
	// pi = 3.14159265359;
	// val = pi / 180;
	// color = 0xffffff;
	// while (r)
	// {
	// 	phi = 0;
	// 	while (phi <= 360)
	// 	{
	// 		x = 400 + (r * sin(phi * val));
	// 		y = 400 + (r * cos(phi * val));
	// 		mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
	// 		phi += 0.1;
	// 		color += 12;
	// 	}
	// 	r--;
	// }
	mlx_loop(mlx_ptr);
}
