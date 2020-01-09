#include "cube3d.h"

void init_img()
{
    int bpp;
	int size_line;
	int endian;
    
    mlx_destroy_image(info.mlx_ptr, info.img_ptr);
    mlx_clear_window(info.mlx_ptr, info.win_ptr);
    info.img_ptr = mlx_new_image(info.mlx_ptr, info.win_width, info.win_height);
	info.img_data = (int *)mlx_get_data_addr(info.img_ptr, &bpp, &size_line, &endian);
}

void put_square(t_player player, int color, int num)
{
    int d;
    int d2;
    int or_x;
    int or_y;

    or_y = player.y_m;
    or_x = player.x_m;
    d2 = player.y_m + info.tile_size_y;
    d = player.x_m + info.tile_size_x;
	while (player.y_m < d2)
	{
        player.x_m = or_x;
		while (player.x_m < d)
		{
            if ((player.y_m == or_y || player.y_m == d2 - 1 || player.x_m == or_x || player.x_m == d - 1) && num == 1)
                put_pix(MINI_MAP * player.x_m, MINI_MAP * player.y_m, color);
            else if (num == 1)
                put_pix(MINI_MAP * player.x_m, MINI_MAP * player.y_m, color);
            else if ((player.y_m == or_y || player.y_m == d2 - 1 || player.x_m == or_x || player.x_m == d - 1) && num == 0)
                put_pix(MINI_MAP * player.x_m, MINI_MAP * player.y_m, 0x0);
            else if (num == 0)
                put_pix(MINI_MAP * player.x_m, MINI_MAP * player.y_m, 0xffffff);
			player.x_m++;
		}
		player.y_m++;
	}
}

int	num(int n)
{
	int i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int     check_name(char *str)
{
    char **split;

    split = ft_split(str, '.');
    if (ft_strncmp(split[1], "cub", 20))
        return (0);
    if (split[2] != 0)
        return (0);
    return (1);
}

void    give_col(t_col fc, char c)
{
    if (c == 'f')
    {
        info.flr_co = fc.r;
        info.flr_co = (info.flr_co << 8) + fc.g;
        info.flr_co = (info.flr_co << 8) + fc.b;
    }
    else if (c == 'c')
    {
        info.cel_co = fc.r;
        info.cel_co = (info.cel_co << 8) + fc.g;
        info.cel_co = (info.cel_co << 8) + fc.b;
    }
}