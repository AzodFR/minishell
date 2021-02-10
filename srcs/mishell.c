/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mishell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:13:01 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/10 15:06:57 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

t_type		*find_next_type(t_type *begin)
{
	t_type *tmp;
	
	tmp = begin;
	while (tmp)
	{
		if (tmp->type > 0 && tmp->type < 6)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

char		**prep_cmd(t_type *begin, int i)
{
	t_type *tmp;
	char 	**args;
	int		j;
	int		last;

	tmp = begin;
	while (tmp)
	{
		++i;
		if (tmp->type  > 0 && tmp->type < 6)
			break;
		tmp = tmp->next;
	}
	if (!(args = wrmalloc((i + 1) * sizeof(char *))))
		ft_exit(MALLOC);
	if (!(args[i] = wrmalloc(1 * sizeof(char))))
		ft_exit(MALLOC);
	args[i] = 0;
	j = -1;
	last = 0;
	get_all_st(NULL)->flag_quote = 0;
	while (++j < i && begin)
	{
		if (begin->type == 3 || begin->type == 5)
			break;
		if(begin && begin->type == 0 && !ft_strlen(begin->content))
				while (begin && begin->type == 0 && !ft_strlen(begin->content))
					begin = begin->next;
		if (!begin)
			break;
		else if ((begin->type < 1 || (begin->type < 8 && begin->type > 5)))
		{
			if (begin->next && ((begin->next->type > 5 && begin->next->type < 8) || begin->next->type < 1) && ++j)
			{
				args[++last - 1] = ft_strjoin(begin->content, begin->next->content);
				begin = begin->next;
				while (begin->next && ((begin->next->type > 5 && begin->next->type < 8) || begin->next->type < 1) && ++j)
				{
					args[last - 1] = ft_strjoin(args[last - 1], begin->next->content);
					begin = begin->next;
				}
			}
			else
				args[last++] = ft_strdup(begin->content);
		}
		if (j + 1 == i && begin->type >= 6)
			get_all_st(NULL)->flag_quote = 1;
		begin = begin->next;
	}
	args[last] = 0;
	j = -1;
//	while (args[++j])
		//printf("args: %s\n", args[j]);
	return (args);
}
void		treat(char *line)
{
	t_type *begin;
	
	if (ft_strlen(line) == 0)
	{
		get_all_st(NULL)->state = 0;
		return ;
	}
	if (!(begin = prepare_array(line)))
	{
		get_all_st(NULL)->state = 2;
		return ;
	}
	build_tree(begin);
}



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
	a.path = NULL;
	a.exit = 0;
	get_all_st(&a);
	while (ret)
	{
		signal(SIGINT, &sig_c);
		signal(SIGQUIT, SIG_IGN);
		//ft_printf("\033[32mMiShell %s", get_tild());
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
	env_edit_value(env_find(env, "SHLVL"), ft_itoa(ft_atoi(env_find(env, "SHLVL")->value) + 1));
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
