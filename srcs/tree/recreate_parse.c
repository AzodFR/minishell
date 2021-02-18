/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recreate_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:16:35 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/17 16:08:00 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

int		is_right_redir(t_type *tmp)
{
	return (tmp->type == 3 || tmp->type == 5);
}

t_type	*add_space_t(t_type *prev)
{
	t_type *space;

	if (!(space = wrmalloc(sizeof(t_type))))
		ft_exit(MALLOC);
	space->prev = prev;
	space->next = NULL;
	space->type = 8;
	space->content = ft_strdup(" ");
	return (space);
}

t_type	*add_file(t_type *prev, t_type *toadd)
{
	t_type *file;

	if (!(file = wrmalloc(sizeof(t_type))))
		ft_exit(MALLOC);
	file->prev = prev;
	file->next = NULL;
	file->type = toadd->type;
	file->content = ft_strdup(toadd->content);
	return (file);
}

int		add_back(t_type **redir, t_type *toadd)
{
	t_type	*begin;

	begin = *redir;
	while (begin->next)
		begin = begin->next;
	begin->next = add_space_t(begin);
	begin = begin->next;
	begin->next = add_file(begin, toadd);
	return (1);
}

t_type	*lastredir(t_type *redir)
{
	t_type *tmp;

	tmp = redir;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
