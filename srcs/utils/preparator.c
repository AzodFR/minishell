/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 13:45:31 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/12 14:51:44 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

static int			prep_args2(int last, t_type **begin, char **args, int *k)
{
	int		j;

	j = *k;
	if ((*begin)->next && (((*begin)->next->type > 5 &&
		(*begin)->next->type < 8)
	|| (*begin)->next->type < 1) && ++j)
	{
		args[++last - 1] = ft_strjoin((*begin)->content,
			(*begin)->next->content);
		(*begin) = (*begin)->next;
		while ((*begin)->next && (((*begin)->next->type > 5 &&
				(*begin)->next->type < 8)
		|| (*begin)->next->type < 1) && ++j)
		{
			args[last - 1] = ft_strjoin(args[last - 1],
				(*begin)->next->content);
			(*begin) = (*begin)->next;
		}
	}
	else
		args[last++] = ft_strdup((*begin)->content);
	*k = j;
	return (last);
}

static int			prep_args(int i, t_type **begin, char **args, int last)
{
	int		j;

	j = -1;
	while (++j < i && (*begin))
	{
		if ((*begin)->type == 3 || (*begin)->type == 5)
			break ;
		if ((*begin) && (*begin)->type == 0 && !ft_strlen((*begin)->content))
			while ((*begin) && (*begin)->type == 0 &&
				!ft_strlen((*begin)->content))
				(*begin) = (*begin)->next;
		if (!(*begin))
			break ;
		else if (((*begin)->type < 1 || ((*begin)->type < 8 &&
			(*begin)->type > 5)))
			last = prep_args2(last, begin, args, &j);
		if (j + 1 == i && (*begin)->type >= 6)
			get_all_st(NULL)->flag_quote = 1;
		(*begin) = (*begin)->next;
	}
	return (last);
}

char				**prep_cmd(t_type *begin, int i)
{
	t_type	*tmp;
	char	**args;
	int		last;

	tmp = begin;
	while (tmp)
	{
		++i;
		if (tmp->type > 0 && tmp->type < 6)
			break ;
		tmp = tmp->next;
	}
	if (!(args = wrmalloc((i + 1) * sizeof(char *))))
		ft_exit(MALLOC);
	if (!(args[i] = wrmalloc(1 * sizeof(char))))
		ft_exit(MALLOC);
	args[i] = 0;
	get_all_st(NULL)->flag_quote = 0;
	last = prep_args(i, &begin, args, 0);
	args[last] = 0;
	return (args);
}

int					get_mpid(void)
{
	char	*c;
	int		fd;
	char	*line;

	c = ft_strdup(
		"ps | grep minishell | head -1 | xargs -n 1 | head -1 > wjwfklcnldknv");
	treat(c);
	fd = open("wjwfklcnldknv", O_RDONLY);
	get_next_line(fd, &line);
	wrfree(c);
	c = ft_strdup("rm wjwfklcnldknv");
	treat(c);
	return (ft_atoi(line));
}
