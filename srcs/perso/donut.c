/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   donut.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedelfos <jedelfos@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:11:32 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/11 16:29:06 by jedelfos         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

static t_donut	init_donut(void)
{
	t_donut d;

	d.a = 0;
	d.q = 0;
	d.color = 30;
	return (d);
}

static void		donut2(t_donut *d)
{
	d->c = sin(d->i);
	d->d = cos(d->j);
	d->e = sin(d->a);
	d->f = sin(d->j);
	d->g = cos(d->a);
	d->h = d->d + 2;
	d->w = 1 / (d->c * d->h * d->e + d->f * d->g + 5);
	d->l = cos(d->i);
	d->m = cos(d->q);
	d->n = sin(d->q);
	d->t = d->c * d->h * d->g - d->f * d->e;
	d->x = 40 + 30 * d->w * (d->l * d->h * d->m - d->t * d->n);
	d->y = 12 + 15 * d->w * (d->l * d->h * d->n + d->t * d->m);
	d->o = d->x + 80 * d->y;
	d->s = 8 * ((d->f * d->e - d->c * d->d * d->g) * d->m - d->c * d->d * d->e -
			d->f * d->g - d->l * d->d * d->n);
	if (22 > d->y && d->y > 0 && d->x > 0 && 80 > d->x && d->w > d->z[d->o])
	{
		d->z[d->o] = d->w;
		d->b[d->o] = "0123456789ABCD"[d->s > 0 ? d->s : 0];
	}
	d->i += 0.02;
}

static void		donut3(t_donut *d)
{
	while (1761 > d->k)
	{
		ft_putchar_fd(d->k % 80 ? d->b[d->k] : 10, 1);
		d->k += 1;
	}
	d->a += 0.04;
	d->q += 0.02;
	while (d->theo < 7483647)
		d->theo += 1;
}

static void		donut1(void)
{
	t_donut	*d;
	t_donut	b;
	int		i;

	b = init_donut();
	d = &b;
	ft_printf("\x1b[2J");
	i = 1;
	while (1)
	{
		d->theo = 0;
		ft_memset(d->b, 32, 1760);
		ft_memset(d->z, 0, 7040);
		d->j = 0;
		while (6.28 > d->j)
		{
			d->i = 0;
			while (6.28 > d->i)
				donut2(d);
			d->j += 0.07;
		}
		ft_printf("\x1b[H");
		d->k = 0;
		donut3(d);
	}
}

int				main_donut(void)
{
	pid_t pid;

	signal(SIGINT, &sig_c);
	signal(SIGQUIT, &sig_quit);
	if (!(pid = fork()))
		donut1();
	else
		wait(&pid);
	return (1);
}
