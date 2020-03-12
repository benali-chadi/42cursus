/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:40:20 by cbenali-          #+#    #+#             */
/*   Updated: 2020/03/12 21:11:46 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <errno.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"

# define INT_MAX 2147483647
# define PI 3.14159265359
# define TWO_PI 6.283118530
# define VAL (PI / 180)

# define FOV (60 * VAL)
# define MINI_MAP 0.2
# define WALL_WIDTH 1
# define TILE_SIZE 64

# define INC_Y_UD (sin(player->direction * VAL) * 2)
# define INC_X_UD (cos(player->direction * VAL) * 2)
# define INC_Y_LR (sin((player->direction + 90 ) * VAL) * 2)
# define INC_X_LR (cos((player->direction + 90 ) * VAL) * 2)

/*
	** Player struct
*/

typedef struct	s_player{
	float		x_p;
	float		y_p;
	float		direction;
	int			x_m;
	int			y_m;
	float		turn_direction;
	float		walk_direction;
}				t_player;

/*
	** Rays structs
*/

typedef struct	s_ray {
	float		ray_angle;
	float		wall_hit_x;
	float		wall_hit_y;
	float		distance;
	int			is_vertical;
	int			is_ray_facing_up;
	int			is_ray_facing_down;
	int			is_ray_facing_left;
	int			is_ray_facing_right;
}				t_rays;

typedef struct	s_ray_hit {
	float		x_inte;
	float		y_inte;
	float		x_step;
	float		y_step;
	float		hit_x;
	float		hit_y;
	int			found_hit;
	int			to_check;
}				t_ray_hit;

/*
	** Paths structure
*/

typedef struct	s_paths {
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*sp;
}				t_paths;

/*
	** Info struct
*/

typedef struct	s_info
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			*img_data;
	int			win_width;
	int			win_height;
	int			map_x;
	int			map_y;
	int			flr_co;
	int			cel_co;
	int			count;
	int			win_x;
	int			win_y;
	int			save;
	t_paths		paths;
}				t_info;

/*
	** Floor and ceiling color struct
*/

typedef struct	s_col{
	int			r;
	int			g;
	int			b;
}				t_col;

/*
	** Textures struct
*/

typedef struct	s_tex
{
	void		*ptr;
	int			*tex;
	int			img_width;
	int			img_height;
	int			bpp;
	int			size_line;
	int			endian;
}				t_tex;

/*
	** Sprites struct
*/

typedef struct	s_spt{
	void		*ptr;
	int			*data;
	float		x;
	float		y;
	int			x_s;
	int			y_s;
	float		distance;
}				t_spt;

/*
	** Draw wall sprite
*/

typedef struct	s_drw_wll {
	float		y;
	float		y_end;
	float		or_x;
	int			x_end;
	int			color;
	int			x_tex;
	int			y_tex;
	int			top_pixel;
	int			t;
}				t_drw_wll;

/*
	** Alloc struct
*/

typedef struct	s_alloc
{
	void	*tmp;
}				t_alloc;

/*
	** Global variables
*/

t_info			g_info;
t_rays			g_rays[5120];
t_tex			g_tex[4];
t_spt			*g_spt;
t_drw_wll		g_drw_wll;
int				g_map[1024][1024];
int				g_sprite;
int				g_count;

/*
	** To move
*/

int				key_destroy(int key, void *ptr);
int				key_press(int key, t_player *player);
int				key_release(int key, t_player *player);
int				move(t_player *player);

/*
	** Drawing
*/

void			init_img(void);
void			put_pix(int x, int y, int color);
void			draw_map(t_player *player);

/*
	** File reading
*/

void			read_file(int fd);
int				check_name(char *str);
int				check_name(char *str);
void			give_col(t_col fc, char c);
int				init_map(char *line);
void			flr(char *line, t_col *f);
void			ceiling(char *line, t_col *c);
void			resolution(char *line);
int				check_map_1(char *line);
void			check_map_2();
int				init_map(char *line);
void			check_ply_pos(int m_v, int *check);
void			init_info(t_col f, t_col c, int count_j);

/*
	** Casting and rendering
*/

void			cast_all_rays(t_player player);
int				has_wall_ray(float y, float x);
float			dist_p(float x1, float y1, float x2, float y2);
void			render_3d(float direction, t_player player);
void			check_wall_dir(float wall_height, int i);
void			draw_wall(int x, float wall_height, int i);
void			update_spr_dis(t_player player);
void			ft_sprite(t_player player, int i);

/*
	** Tools
*/

int				has_wall(float y, float x);
int				has_wall_lr(float y, float x, char o, t_player *player);
float			normalize_angle(float angle);
int				normalize_angle_deg(int angle);
int				num(int n);
void			init_player(t_player *player, int i);
void			ft_exit(char *str);
void			bmp_save(void);
void			add_to_pl(float *x_p, float *y_p, float x_inc, float y_inc);
void			sub_frm_pl(float *x_p, float *y_p, float x_inc, float y_inc);

void			*m_malloc(size_t n);
void			to_free(void);

int				all_n(char *s);
void			check_comma(char *line);

#endif
