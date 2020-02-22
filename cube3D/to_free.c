/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 00:56:44 by cbenali-          #+#    #+#             */
/*   Updated: 2020/02/18 00:57:14 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_alloc			g_alloc[400];
int				g_all = 0;

void			*m_malloc(size_t n)
{
	void		*tmp;

	if (!(tmp = malloc(n)))
		return (NULL);
	g_alloc[g_all].tmp = tmp;
	g_all++;
	return (tmp);
}

void			to_free(void)
{
	int i;

	i = -1;
	while (++i < g_all)
		free(g_alloc[i].tmp);
}
