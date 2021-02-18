/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 14:32:36 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/18 11:11:00 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

t_type		*find_next_type(t_type *begin)
{
	t_type	*tmp;

	tmp = begin;
	while (tmp)
	{
		if (tmp->type > 0 && tmp->type < 6)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int			check_white(char *line)
{
	int		i;

	i = -1;
	while (line[++i])
		if (line[i] != '\t' || line[i] != ' ')
			return (1);
	return (0);
}

int			isallspace(t_type *begin)
{
	t_type *tmp;

	tmp = begin;
	while (tmp)
	{
		if (tmp->type != 8)
		{
			tmp = begin;
			while ((tmp) && (tmp)->next)
				(tmp) = (tmp)->next;
			while ((tmp) && (tmp)->type == 8)
			{
				if ((tmp)->prev)
					(tmp)->prev->next = NULL;
				(tmp) = (tmp)->prev;
			}
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void		treat(char *line)
{
	t_type	*begin;

	if (ft_strlen(line) == 0 || !check_white(line))
	{
		get_all_st(NULL)->state = 0;
		return ;
	}
	if (!(begin = prepare_array(line)))
	{
		get_all_st(NULL)->state = 2;
		return ;
	}
	if (isallspace(begin))
	{
		get_all_st(NULL)->state = 0;
		return ;
	}
	build_tree(begin);
}

int			is_directory(const char *path)
{
	struct stat statbuf;

	statbuf.st_mode = 0;
	stat(path, &statbuf);
	return (S_ISDIR(statbuf.st_mode));
}
