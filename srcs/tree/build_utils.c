/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 10:30:16 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/12 10:31:23 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

void	get_fd_back(int fd[3])
{
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	dup2(fd[2], 2);
}

int		go_next_begin(t_type **begin)
{
	(*begin) = find_next_type((*begin));
	if ((*begin) && (*begin)->type == 1)
	{
		(*begin) = (*begin)->next;
		return (0);
	}
	else if ((*begin))
		(*begin) = (*begin)->next;
	return (1);
}

void	check_exit(void)
{
	int		state;

	if (get_all_st(NULL)->exit == 1)
	{
		state = get_all_st(NULL)->state;
		wrdestroy();
		exit(state);
	}
}

int		not_good_right(t_tree *right)
{
	char **cmd;

	cmd = prep_cmd(right->cmd, 0);
	end_ling(get_all_st(NULL)->state, cmd[0]);
	return (0);
}
