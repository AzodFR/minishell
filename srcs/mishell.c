/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mishell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:13:01 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/12 13:41:00 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

void		loop(int fd)
{
	int		ret;
	char	*line;
	t_all	a;

	ret = 1;
	a.state = 0;
	a.fd[0] = dup(0);
	a.fd[1] = dup(1);
	a.fd[2] = dup(2);
	a.exit = 0;
	get_all_st(&a);
	while (ret)
	{
		get_all_st(NULL)->prog = 0;
		signal(SIGINT, &sig_c);
		signal(SIGQUIT, &sig_quit);
	//	ft_printf("\033[32mMiShell %s", get_tild());
		ret = get_next_line(fd, &line);
		if (ret > 0)
			treat(line);
		wrfree(line);
	}
	if (ret < 0)
		ft_exit(EXIT_FAILED);
	ft_exit(EXIT_SUCCESS);
}

t_all		*get_all_st(t_all *all)
{
	static t_all	*ret = {NULL};

	if (all)
		ret = all;
	return (ret);
}

t_env		*get_env_st(t_env *env)
{
	static t_env	*ret = {NULL};

	if (env)
		ret = env;
	return (ret);
}

int			main(int ac, char **av, char **envp)
{
	t_env	*env;
	int		fd;

	(void)av[ac];
	//welcome(envp);
	fd = 0;
	if (ac == 2)
		fd = open(av[1], O_RDONLY);
	env = init_env(envp);
	env_edit_value(env_find(env, "SHLVL"),
	ft_itoa(ft_atoi(env_find(env, "SHLVL")->value) + 1));
	if (!env_find(env, "OLDPWD"))
	{
		ft_envadd_back(&env, ft_envnew("OLDPWD", ""));
		env_edit_state(env_find(env, "OLDPWD"), 0);
	}
	get_env_st(env);
	loop(fd);
	if (ac == 2)
		close(fd);
	return (EXIT_SUCCESS);
}
