#include "cube3d.h"

float   dist_p(float x1, float y1, float x2, float y2)
{
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void    ft_exit(char *msg)
{
    ft_putstr_fd(msg, 1);
    exit(-1);
}