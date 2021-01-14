/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mishell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:13:01 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/14 18:05:14 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

void		treat(char *line, t_all *all, t_env *env)
{
	char	***args;
	int		i;
	
	args = prepare_array(line, all);
	i = -1;
	while (args[++i])
		handler(args[i], all, env, 0);
}

void		loop(t_env *envp)
{
	int		ret;
	char	*line;
	t_all	a;

	ret = 1;
	a.state = 1;
	while (ret)
	{
		ft_printf("\033[32mMiShell \033[%dm~ \033[0m", a.state ? 36 : 31);
		ret = get_next_line(0, &line);
		if (ret > 0)
			treat(line, &a, envp);
		wrfree(line);
	}
	if (ret < 0)
		ft_exit(EXIT_FAILED);
	ft_exit(EXIT_SUCCESS);
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

	(void)av[ac];
	welcome(envp);
	env = init_env(envp);
	get_env_st(env);
	loop(env);
	return (EXIT_SUCCESS);
}
