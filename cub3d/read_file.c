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
    info.tile_size_x = info.win_width / info.map_x;
    info.tile_size_y = info.win_height / info.map_y;
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
            // printf("lien = %d map = %d\n", *line, map[count_i][j]);
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

// int     main(int ac, char **av)
// {
    
//     int     fd;
//     int     i;

//     if (ac < 2)
//     {
//         perror("Error");
//         exit(-1);
//     }
//     fd = open(av[1], O_RDONLY);
//     if (!check_name(av[1]) || fd == -1)
//     {
//         perror("Error");
//         exit(-1);
//     }
//     // int count_j = give_values(fd);
//     // i = 0;
//     // int j;
//     // printf("rx : %d\try : %d\nfr : %d\tfg : %d\tfb : %d\ncr : %d\tcg : %d\tcb : %d\n", r[0], r[1], f.r, f.g, f.b, c.r, c.g, c.b);
//     // printf("THE MAP :\n");
//     // while (i < count_i)
//     // {
//     //     j = 0;
//     //     while (j < count_j)
//     //     {
//     //         printf("map[%d][%d] : %d\n", i, j, map[i][j]);
//     //         j++;
//     //     }
//     //     i++;
//     // }
//     return (0);
// }