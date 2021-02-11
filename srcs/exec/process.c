/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedelfos <jedelfos@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 11:19:42 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/11 15:51:24 by jedelfos         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

static void		child(char *path, char **args, char **env)
{
	int		ret;

	ret = execve(path, args, env);
	get_all_st(NULL)->state = ret;
	exit(ret);
}

static void		father(int child_pid)
{
	int		child_status;

	child_status = 0;
	wait(&child_status);
	if (WIFEXITED(child_status))
		get_all_st(NULL)->state = child_status;
	get_all_st(NULL)->state = WEXITSTATUS(child_status);
	(void)child_pid;
}

int				exec_cmd_parents(char *path, char **args, char **env)
{
	int		pid;

	if ((pid = fork()) == 0)
		child(path, args, env);
	else
		father(pid);
	return (get_all_st(NULL)->state);
}
