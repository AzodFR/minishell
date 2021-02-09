/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 11:40:46 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/09 12:15:46 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

char 	*search_cmd_local(char **args)
{
	struct stat	buff;
	char		test[10000];
	char		*tmp;
	char		*tmp2;

	tmp = ft_strjoin(getcwd(test, 10000), "/");
	tmp2 = ft_strjoin(tmp, args[0]);
	if (!stat(tmp2, &buff))
		return (tmp2);
	wrfree(tmp2);
	return (NULL);
}

void			child(char *path, char **args, char**env)
{
	int			ret;
	ret = execve(path, args, env);
	get_all_st(NULL)->state = ret;
	exit(ret);
}

void			father(int child_pid)
{
	int			child_status;

	child_status = 0;
	signal(SIGINT, SIG_IGN);
	wait(&child_status);
	if (WIFSIGNALED(child_status) && ft_printf("\n"))
		get_all_st(NULL)->state = 130;
	if (WIFEXITED(child_status))
		get_all_st(NULL)->state = child_status;
	get_all_st(NULL)->state = WEXITSTATUS(child_status);
	(void)child_pid;
}

int	exec_cmd_parents(char *path, char **args, char**env)
{
	int pid;

	if ((pid = fork()) == 0)
		child(path, args, env);
	else
		father(pid);
	return (get_all_st(NULL)->state);
}

int is_directory(const char *path)
{
   struct stat statbuf;
   
	stat(path, &statbuf);
	return S_ISDIR(statbuf.st_mode);
}

void		search_cmd(t_env *env, char **args, int i)
{
	struct stat	buff;
	char		**path;
	char		*tmp;
	char		*tmp2;

	if (is_directory(args[0]))
	{
		if (!ft_strncmp(args[0], "..", 3))
			get_all_st(NULL)->state = 127;
		else
			get_all_st(NULL)->state = 126;
			return ;
	}
	path = ft_split(env_find(env, "PATH")->value, ':');
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp2 = ft_strjoin(tmp, args[0]);
		wrfree(tmp);
		if (!stat(tmp2, &buff))
		{
			get_all_st(NULL)->state = exec_cmd_parents(tmp2, args, env_to_tab(env));
			wrfree(tmp2);
			return ;
		}
		wrfree(tmp2);
	}
	if ((tmp2 = search_cmd_local(args)))
	{
			get_all_st(NULL)->state = exec_cmd_parents(tmp2, args, env_to_tab(env));
			wrfree(tmp2);
			return ;
	}
	else
			get_all_st(NULL)->state = 127;
	return ;
}

char *find_path(char *s, t_env *env)
{
	char **path;
	char *tmp;
	char *tmp2;
	struct stat	buff;
	int i;
	
	i = -1;
	path = ft_split(env_find(env, "PATH")->value, ':');
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp2 = ft_strjoin(tmp, s);
		wrfree(tmp);
		if (!stat(tmp2, &buff))
			return (tmp2);
		wrfree(tmp2);
	}
	return (s);
}

void	underscore(t_env *env, char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		;
		--i;
	env_edit_value(env_find(env, "_"), find_path(args[i], env));
}

int		end_ling(int ret, char *s)
{
	if (ret == 32257 || ret == 127)
	{
		get_all_st(NULL)->state = 127;
		ft_dprintf(2, "\033[32mMiShell \033[31m✘ \033[0m");
		ft_dprintf(2, "%s: command not found\n", s);
	}
	if (ret == 126)
	{
		ft_dprintf(2, "\033[32mMiShell \033[31m✘ \033[0m");
		ft_dprintf(2, "%s: is a directory\n", s);
	}
	if (ret == 256)
		get_all_st(NULL)->state = 1;
	return (ret);
}

void	dot(char **args)
{
	if (!args[1])
	{
		ft_dprintf(2, "\033[32mMiShell \033[31m✘ \033[0m");
		ft_dprintf(2, ".: not enough arguments\n");
		get_all_st(NULL)->state = 2;
	}
	else
	{
		ft_dprintf(2, "\033[32mMiShell \033[31m✘ \033[0m");
		ft_dprintf(2, ".: no such file or directory: %s\n", args[1]);
		get_all_st(NULL)->state = 1;
	}
}

int		handler(char **args, t_env *env)
{
	t_all *all;

	all = get_all_st(NULL);
	if (!args[0])
		return (1);
	underscore(env, args);
	if (!ft_strncmp(ft_tolowers(args[0]), "pwd", 4))
		get_pwd();
	else if (!ft_strncmp(ft_tolowers(args[0]), "env", 4))
		get_env(env);
	else if (!ft_strncmp(ft_tolowers(args[0]), "cd", 3))
		change_dir(env, args);
	else if (!ft_strncmp(ft_tolowers(args[0]), "export", 7))
		export_env(env, args);
	else if (!ft_strncmp(ft_tolowers(args[0]), "unset", 6))
		unset(env, args);
	else if (!ft_strncmp(ft_tolowers(args[0]), "echo", 5))
		do_echo(args);
	else if (!ft_strncmp(ft_tolowers(args[0]), "donut", 6))
		get_all_st(NULL)->state = main_donut();
	else if (!ft_strncmp(ft_tolowers(args[0]), "exit", 6))
		ft_exit(EXIT_SUCCESS);
	else if ((!ft_strncmp(ft_tolowers(args[0]), ".", 2)))
		dot(args);
	else
		search_cmd(env, args, -1);
	return (end_ling(get_all_st(NULL)->state, args[0]));
}
