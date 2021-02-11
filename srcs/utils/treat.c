/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 14:32:36 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/11 15:25:46 by thjacque         ###   ########lyon.fr   */
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

void		treat(char *line)
{
	t_type	*begin;

	if (ft_strlen(line) == 0)
	{
		get_all_st(NULL)->state = 0;
		return ;
	}
	if (!(begin = prepare_array(line)))
	{
		get_all_st(NULL)->state = 2;
		return ;
	}
	build_tree(begin);
}

int			is_directory(const char *path)
{
	struct stat statbuf;

	stat(path, &statbuf);
	return (S_ISDIR(statbuf.st_mode));
}
