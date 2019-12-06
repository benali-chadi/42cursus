#include <mlx.h>
#include "libft/libft.h"
#include <unistd.h>

int	deal_key(int key, void *ptr)
{
	ft_putnbr_fd(key, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}

void drawcircle(void *mlx_ptr, void *win_ptr, int xc, int yc, int x, int y)
{
	mlx_pixel_put(mlx_ptr, win_ptr, xc+x, yc+y, 0xff0000);
	mlx_pixel_put(mlx_ptr, win_ptr, xc-x, yc+y, 0xff0000);
	mlx_pixel_put(mlx_ptr, win_ptr, xc+x, yc-y, 0xff0000);
	mlx_pixel_put(mlx_ptr, win_ptr, xc-x, yc-y, 0xff0000);
	mlx_pixel_put(mlx_ptr, win_ptr, xc+y, yc+x, 0xff0000);
	mlx_pixel_put(mlx_ptr, win_ptr, xc-y, yc+x, 0xff0000);
	mlx_pixel_put(mlx_ptr, win_ptr, xc+y, yc-x, 0xff0000);
	mlx_pixel_put(mlx_ptr, win_ptr, xc-y, yc-x, 0xff0000);
}

int main()
{
	void	*mlx_ptr;
	void	*win_ptr;
	int x;
	int y;

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
	int xc;
	int yc;
	int r;
	int d;

	xc = 400;
	yc = 100;
	r = 80;
	x = 0;
	y = r;
	d = r;
	
	drawcircle(mlx_ptr, win_ptr, xc, yc, x, y);
	while (y >= x)
	{
		x++;
		if (d > 0)
		{
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else
			d = d + 4 * x + 6;
		drawcircle(mlx_ptr, win_ptr, xc, yc, x, y);
	}
	mlx_loop(mlx_ptr);
}
