/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 20:17:32 by cbenali-          #+#    #+#             */
/*   Updated: 2020/02/14 20:41:14 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

unsigned char	g_bmpfileheader[14] = {
	'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0
};
unsigned char	g_bmpinfoheader[40] = {
	40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0
};
unsigned char	g_bmppad[3] = {0, 0, 0};
int				g_w;
int				g_h;

void	init_fl_inf_head(int filesize)
{
	g_bmpfileheader[2] = (unsigned char)(filesize);
	g_bmpfileheader[3] = (unsigned char)(filesize >> 8);
	g_bmpfileheader[4] = (unsigned char)(filesize >> 16);
	g_bmpfileheader[5] = (unsigned char)(filesize >> 24);
	g_bmpinfoheader[4] = (unsigned char)(g_w);
	g_bmpinfoheader[5] = (unsigned char)(g_w >> 8);
	g_bmpinfoheader[6] = (unsigned char)(g_w >> 16);
	g_bmpinfoheader[7] = (unsigned char)(g_w >> 24);
	g_bmpinfoheader[8] = (unsigned char)(g_h);
	g_bmpinfoheader[9] = (unsigned char)(g_h >> 8);
	g_bmpinfoheader[10] = (unsigned char)(g_h >> 16);
	g_bmpinfoheader[11] = (unsigned char)(g_h >> 24);
}

void	give_img(int fd, int padd)
{
	int i;
	int j;

	i = -1;
	while (++i < g_h)
	{
		j = -1;
		while (++j < g_w)
			write(fd, g_info.img_data + (j + (g_h - i) * g_w), 3);
		write(fd, g_bmppad, padd);
	}
}

void	bmp_save(void)
{
	int				filesize;
	int				fd;
	int				padd;

	g_w = g_info.win_width;
	g_h = g_info.win_height;
	filesize = 54 + 3 * g_w * g_h;
	padd = (4 - (g_w * 3) % 4) % 4;
	init_fl_inf_head(filesize);
	fd = open("first_img.bmp", O_CREAT | O_RDWR);
	write(fd, g_bmpfileheader, 14);
	write(fd, g_bmpinfoheader, 40);
	give_img(fd, padd);
	free(g_info.img_data);
}
