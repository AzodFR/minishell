/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piped.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 12:31:25 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/05 12:41:52 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

void    exec_pipe(t_type *cmd, int backfd, int count)
{
    int		fd[2];
	pid_t 	pid;
	
	pipe(fd);
	if ((pid = fork()) == 0)
	{
		dup2(backfd, 0);
		if (count)
			dup2(fd[1], 1);
		close(fd[0]);
		if (count)
			dealt_exec_cmd(root->left);
		else
			dealt_exec_cmd(root);
		exit(get_all_st(NULL)->state);
	}
	close(fd[1]);
	exec_pipe(root->right, count - 1, fd[0]);
	pid = wait(NULL);
}