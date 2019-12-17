#include <mlx.h>
#include <math.h>
#include "libft/libft.h"
#include <unistd.h>
#include <stdio.h>
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

int main()
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 800, 800, "mlx 1337");
	mlx_key_hook(win_ptr, deal_key, (void *)0);

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
	int x;
	int y;
	int r;
	float pi;
	float phi;
	float val;
	int color;


	r = 200;
	phi = 0;
	pi = 3.14159265359;
	val = pi / 180;
	color = 0xffffff;
	while (r)
	{
		phi = 0;
		while (phi <= 360)
		{
			x = 400 + (r * sin(phi * val));
			y = 400 + (r * cos(phi * val));
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
			phi += 0.1;
			color += 12;
		}
		r--;
	}
	mlx_loop(mlx_ptr);
}
