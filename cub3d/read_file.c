#include "cube3d.h"

typedef struct  s_col{
    int r;
    int g;
    int b;
}               t_col;

int     r[2];
int     count_i;

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
        if (j > 1)
            break;
        line++;
    }
}

void    flr(char *line, t_col *f)
{
    char **split;

    split = ft_split(line, ',');
    f->r = ft_atoi(split[0]);
    f->g = ft_atoi(split[1]);
    f->b = ft_atoi(split[2]);
}

void    ceiling(char *line, t_col *c)
{
    char **split;

    split = ft_split(line, ',');
    c->r = ft_atoi(split[0]);
    c->g = ft_atoi(split[1]);
    c->b = ft_atoi(split[2]);
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
            printf("%d\n", *line);
        }
        line++;
    }
    count_i++;
    return (j);
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