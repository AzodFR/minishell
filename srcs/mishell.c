/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mishell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:13:01 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/08 17:38:54 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

void	treat(char *line, t_all *all, t_env *env)
{
	char	**args;
	int		i;

	args = trim_args(line, ';');
	i = -1;
	while (args[++i])
		handler(args[i], all, env);
}

void	loop(char **env)
{
	int		ret;
	char	*line;
	t_all	a;
	t_env	*envp;
	
	ret = 1;
	a.state = 1;
	envp = init_env(env);
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

int		main(int ac, char **av, char **envp)
{
	(void)av[ac];
	welcome(envp);
	loop(envp);
	return (EXIT_SUCCESS);
}