/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piped.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 12:31:25 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/17 11:10:00 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

void	exec_pipe(t_tree *root, int count, int backup_fd)
{
	int				fd[2];
	int				pid;

	if (!root)
		return ;
	pipe(fd);
	if ((pid = fork()) == 0)
	{
		dup2(backup_fd, STDIN_FILENO);
		if (count)
			dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		if (count)
			exec_cmd(root->left);
		else
			exec_cmd(root);
		exit(get_all_st(NULL)->state);
	}
	close(fd[1]);
	exec_pipe(root->right, count - 1, fd[0]);
	pid = wait(&(get_all_st(NULL)->state));
	if (get_all_st(NULL)->state > 255)
		get_all_st(NULL)->state -= 255;
	close(fd[0]);
}
