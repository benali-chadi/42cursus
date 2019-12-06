#include <mlx.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <unistd.h>

void    *mlx_ptr;
void    *win_ptr;
int     **map;

void put_square(void *mlx_ptr, void *win_ptr, int x, int y, int size, int color)
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

int **init_map(int x, int y)
{
//    int **map;
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
    return (map);
}

void draw_map(/*int **map, */int x, int y)
{
    int i;
    int j;
    int size;

    i = 0;
    j = 0;
    size = 50;
    while (i < 12)
    {
        j = 0;
        while(j < 12)
        {
            if(map[i][j] == 1)
                put_square(mlx_ptr, win_ptr, x, y, size, 0xffdddd);
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
    if (key == 126)
    {
        mlx_clear_window(mlx_ptr, win_ptr);
        draw_map(0 , 0);
        put_square(mlx_ptr, win_ptr, x, y - 20, 60, 0xffdddd);
        *(cord + 1) -= 20;
    }
    if (key == 125)
    {
        mlx_clear_window(mlx_ptr, win_ptr);
        draw_map(0 , 0);
        put_square(mlx_ptr, win_ptr, x, y + 20, 60, 0xffdddd);
        *(cord + 1) += 20;
    }
    if (key == 123)
    {
        mlx_clear_window(mlx_ptr, win_ptr);
        draw_map(0 , 0);
        put_square(mlx_ptr, win_ptr, x - 20, y, 60, 0xffdddd);
        *(cord) -= 20;
    }
    if (key == 124)
    {
        mlx_clear_window(mlx_ptr, win_ptr);
        draw_map(0 , 0);
        put_square(mlx_ptr, win_ptr, x + 20, y, 60, 0xffdddd);
        *(cord) += 20;
    }
    return (0);
}

int main()
{
//    int **map = 
    int x;
    int y;   

    mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 600, 600, "mlx 1337");
    x = 0;
    y = 0;
    // drawing map
    
    init_map(12, 12);
    draw_map(x, y);
    x = 450;
    y = 450;
    put_square(mlx_ptr, win_ptr, x, y, 60, 0xffdddd);
    int cord[2];
    cord[0] = x;
    cord[1] = y;
    mlx_key_hook(win_ptr, move, cord);
	mlx_loop(mlx_ptr);
}