/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mishell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:13:01 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/05 14:24:48 by thjacque         ###   ########lyon.fr   */
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
		if(begin && begin->type == 0 && !ft_strlen(begin->content))
				while (begin && begin->type == 0 && !ft_strlen(begin->content))
					begin = begin->next;
		if (!begin)
			break;
		//if (j + 1 == i)
		//	args[last++] = ft_strdup(begin->content);
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
	return (args);
}
void		treat(char *line)
{
	t_type *begin;
	t_tree *root;

	if (!(begin = prepare_array(line)))
	{
		
		get_all_st(NULL)->state = 1;
		return ;
	}
	if (!(root = wrmalloc(sizeof(t_tree))))
		ft_exit(MALLOC);
	build_tree(begin, root);
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
	get_all_st(&a);
	while (ret)
	{
		ft_printf("\033[32mMiShell \033[%dm~ \033[0m", !a.state ? 36 : 31);
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
	env_edit_value(env_find(env, "SHLVL"), ft_itoa(ft_atoi(env_find(env, "SHLVL")->value) + 1));
	get_env_st(env);
	loop(fd);
	if (ac == 2)
		close(fd);
	return (EXIT_SUCCESS);
}
