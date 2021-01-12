/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 11:40:46 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/12 15:55:23 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

int		search_cmd_local(t_env *env, char **args)
{
	struct stat	buff;
	char		test[10000];
	char		*tmp;
	char		*tmp2;
	pid_t		prog;

	tmp = ft_strjoin(getcwd(test, 10000), "/");
	tmp2 = ft_strjoin(tmp, args[0]);
	if (!stat(tmp2, &buff))
	{
		if (!(prog = fork()))
			execve(tmp2, args, env_to_tab(env));
		wait(&prog);
		wrfree(tmp2);
		return (1);
	}
	wrfree(tmp2);
	return (-1);
}

int		search_cmd(t_env *env, char **args, int i)
{
	struct stat	buff;
	char		**path;
	char		*tmp;
	char		*tmp2;
	pid_t		prog;

	path = ft_split(env_find(env, "PATH")->value, ':');
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp2 = ft_strjoin(tmp, args[0]);
		wrfree(tmp);
		if (!stat(tmp2, &buff))
		{
			if (!(prog = fork()))
				execve(tmp2, args, env_to_tab(env));
			wait(&prog);
			wrfree(tmp2);
			return (1);
		}
		wrfree(tmp2);
	}
	return (search_cmd_local(env, args));
}

void	underscore(t_env *env, char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		;
	env_edit_value(env_find(env, "_"), args[--i]);
}

int		handler(char *cmd, t_all *all, t_env *env)
{
	int		ret;
	char	**args;

	args = trim_args(cmd, ' ');
	ret = 0;
	if (!args[0])
		return (1);
	underscore(env, args);
	if (!ft_strncmp(args[0], "pwd", 4))
		ret = get_pwd();
	else if (!ft_strncmp(args[0], "env", 4))
		ret = get_env(env);
	else if (!ft_strncmp(args[0], "cd", 3))
		ret = change_dir(env, args);
	else if (!ft_strncmp(args[0], "export", 7))
		ret = export_env(env, args);
	else if (!ft_strncmp(args[0], "unset", 6))
		ret = unset(env, args);
	else if (!ft_strncmp(args[0], "donut",6))
		ret = main_donut();
	else if (!ft_strncmp(args[0], "exit", 6))
		ft_exit(EXIT_SUCCESS);
	else
		ret = search_cmd(env, args, -1);
	if (ret < 0)
	{
		ft_printf("\033[32mMiShell \033[31m✘ \033[0m");
		ft_printf("%s: command not found\n", args[0]);
	}
	all->state = ret;
	return (ret);
}
