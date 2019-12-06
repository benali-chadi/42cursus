#include <mlx.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <unistd.h>

void    *mlx_ptr;
void    *win_ptr;
int     **map;

void put_square(int x, int y, int size, int color)
{
    int d;
    int d2;
    int or_x;

    or_x = x;
    d2 = y + size;
    d = x + size;
	while (y < d2)
	{
        x = or_x;
		while (x < d)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
			x++;
		}
		y++;
	}
}

void init_map(int x, int y)
{
    int i;
    int j;

    i = 0;
    map = malloc(y * sizeof(int *));
    while (i < y)
    {
        j = 0;
        map[i] = malloc(x * sizeof(int));
        while (j < x)
        {
            if (i == 0 || i == y - 1 || j == 0 || j == x - 1)
                map[i][j] = 1;
            else
                map[i][j] = 0;
            j++;
        }
        i++;
    }
}

void draw_map(int x, int y)
{
    int i;
    int j;
    int size;

    i = 0;
    j = 0;
    size = 50;
    while (i < 10)
    {
        j = 0;
        while(j < 10)
        {
            if(map[i][j] == 1)
                put_square(x, y, size, 0x55aadd);
            x += size;
            j++;
        }
        x = 0;
        y += size;
        i++;
    }
}

int move(int key, int *cord)
{
    int x = cord[0];
    int y = cord[1];
    int color = 0x55aadd;

    if (key == 126 && y > 50)
    {
        put_square(x, y - 20, 60, color);
        *(cord + 1) -= 20;
    }  
    else if (key == 125 && y < 390)
    {
        put_square(x, y + 20, 60, color);
        *(cord + 1) += 20;
    }
    else if (key == 123 && x > 50)
    {
        put_square(x - 20, y, 60, color);
        *(cord) -= 20;
    }
    else if (key == 124 && x < 390)
    {
        put_square(x + 20, y, 60, color);
        *(cord) += 20;
    }
    else
        put_square(x, y, 60, color);
    mlx_clear_window(mlx_ptr, win_ptr);
    draw_map(0 , 0);
    return (0);
}

int main()
{
    int x;
    int y;   

    mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "mlx 1337");
    x = 0;
    y = 0;   
    init_map(10, 10);
    draw_map(x, y);
    x = 250;
    y = 250;
    put_square(x, y, 60, 0x55aadd);
    int cord[2];
    cord[0] = x;
    cord[1] = y;
    mlx_key_hook(win_ptr, move, cord);
	mlx_loop(mlx_ptr);
    return(0);
}