/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 19:30:50 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/07 11:47:29 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

void			exec_redirection(t_tree *root, int fd, int redirection)
{
	int				child_status;

	child_status = 0;
	if (fork() == 0)
	{
		dup2(fd, redirection);
		close(fd);
		exec_cmd(root->left);
		exit(get_all_st(NULL)->state);
	}
	else
	{
		wait(&child_status);
		get_all_st(NULL)->state = WEXITSTATUS(child_status);
	}
	get_all_st(NULL)->state = child_status;
}

void				redirections(t_tree *root)
{
	int				fd;
	int				redirection;

    redirection = ft_atoi(root->cmd->content);
    if (!redirection)
        redirection = 1;
	if (root->cmd->type == 4)
		redirection = 0;
	fd = create_file(root->cmd->type, prep_cmd(root->right->cmd, 0));
	if (fd == -1)
		return ;
	exec_redirection(root, fd, redirection);
}