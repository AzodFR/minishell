/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 11:40:46 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/08 18:07:21 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

int		handler(char *cmd, t_all *all, t_env *env)
{
	int		ret;
	char	**args;
	
	args = trim_args(cmd, ' ');
	ret = 0;
	if (!args[0])
		return (1);
	if (!ft_strncmp(args[0], "pwd", 4))
		ret = get_pwd();
	else if (!ft_strncmp(args[0], "env", 4))
		ret = get_env(env);
	else if (!ft_strncmp(args[0], "cd", 3))
		ret = change_dir(env, args);
	else if (!ft_strncmp(args[0], "exit", 6))
		ft_exit(EXIT_SUCCESS);
	else
		ft_printf("\033[31m➜\033[0m %s: command not found\n", args[0]);
	all->state = ret;
	return (ret);
}