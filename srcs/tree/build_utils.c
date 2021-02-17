/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 10:30:16 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/17 11:10:12 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

void	get_fd_back(int fd[3])
{
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd[2], STDERR_FILENO);
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

void	check_left_redir(t_type **tmp)
{
	if ((*tmp)->type == 4)
	{
		if (get_all_st(NULL)->flag_quote)
			(*tmp)->type = 8;
		get_all_st(NULL)->flag_quote = 1;
	}
}
