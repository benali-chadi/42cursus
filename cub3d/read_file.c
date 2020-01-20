#include "cube3d.h"

int     r[2];
int     count_i;


void    resolution(char *line)
{
    int j;

    j = 0;
    while(*line)
    {
        if (ft_isdigit(*line))
        {
            r[j] = ft_atoi(line);
            line += num(r[j]);
            j++;
        }
        line++;
    }
}

void    init_info(t_col f, t_col c, int *r, int count_j)
{
    info.map_x = count_j;
    info.map_y = count_i;
    info.win_width = r[0];
    info.win_height = r[1];
    give_col(f, 'f');
    give_col(c, 'c');
    // info.tile_size_x = info.win_width / info.map_x;
    // info.tile_size_y = info.win_height / info.map_y;
    info.win_x = info.map_x * TILE_SIZE;
    info.win_y = info.map_y * TILE_SIZE;
}

int     init_map(char *line)
{
    int j;

    j = 0;
    while(*line)
    {
        if (ft_isdigit(*line))
        {
            map[count_i][j] = *line - 48;
            j++;
        }
        else if (ft_isalpha(*line))
        {
            map[count_i][j] = *line;
            j++;
        }
        line++;
    }
    count_i++;
    return (j);
}

void    read_file(int fd)
{
    char    *line;
    t_col   f;
    t_col   c;
    int     count_j;
    int     i;
       
    count_i = 0;
    while (get_next_line(fd, &line))
    {
        i = 0;
        if (line[0] == 'R')
            resolution(line);
        if (line[0] == 'F')
        {
            while (!ft_isdigit(line[i]))
                i++;
            flr(line + i, &f);
        }
        if (line[0] == 'C')
        {
            while (!ft_isdigit(line[i]))
                i++;
            ceiling(line + i, &c);
        }
        if (ft_isdigit(line[0]))
            count_j = init_map(line);
    }
    if (ft_isdigit(line[0]))
        count_j = init_map(line);
    init_info(f, c, r, count_j);
}