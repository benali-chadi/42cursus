#include "cube3d.h"

void	put_pix(int x, int y, int color)
{
    if (x >= 0 && x < info.win_width && y >= 0 && y < info.win_height)
        info.img_data[x + (y * info.win_width)] = color;
}

int has_wall(float y, float x)
{
    if (y > 0 && y < info.win_height && x > 0 && x < info.win_width)
        return (map[(int)y / info.tile_size_y][(int)x / info.tile_size_x] != 0 && 
        !ft_isalpha(map[(int)y / info.tile_size_y][(int)x / info.tile_size_x]));
    return (1);
}

float dist_p(float x1, float y1, float x2, float y2)
{
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

float normalize_angle(float angle)
{
    angle = remainder(angle, TWO_PI);
    angle += (angle < 0) ? TWO_PI : 0;
    return (angle);
}

int normalize_angle_deg(int angle)
{
    angle = angle % 360;
    angle += (angle < 0) ? 360 : 0;
    return (angle);
}