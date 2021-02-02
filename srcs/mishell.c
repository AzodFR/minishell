/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mishell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:13:01 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/02 12:51:10 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

t_type		*find_next_type(t_type *begin)
{
	t_type *tmp;
	
	tmp = begin;
	while (tmp)
	{
		if (tmp->type > 1 && tmp->type < 6)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void		treat(char *line)
{
	t_type *begin;

	
	begin = prepare_array(line);

	
}

void		loop(int fd)
{
	int		ret;
	char	*line;
	t_all	a;

	ret = 1;
	a.state = 1;
	get_all_st(&a);
	while (ret)
	{
		ft_printf("\033[32mMiShell \033[%dm~ \033[0m", a.state ? 36 : 31);
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
	welcome(envp);
	fd = 0;
	if (ac == 2)
		fd = open(av[1], O_RDONLY);
	env = init_env(envp);
	get_env_st(env);
	loop(fd);
	if (ac == 2)
		close(fd);
	return (EXIT_SUCCESS);
}
