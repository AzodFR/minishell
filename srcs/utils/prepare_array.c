/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedelfos <jedelfos@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 11:41:28 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/27 17:00:49 by jedelfos         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

void	fill_teub(char **teub, char *line, t_all *a)
{
	static	int		j = -1;

	a->flag_quote = 0;
	a->flag_esc = 0;
	a->flag_cmd = 0;
//	ft_printf("reset\n");
	get_blocks(teub, line, &j);
}

void	set_value(char ***teub, int cmds, int *i, int *j)
{
	teub[cmds] = 0;
	*i = -1;
	*j = -1;
}

int		create_struc(char *line, int i, char type, t_type *str_type)
{
	int y;
	t_type	*temp;

	y = 0;
	temp = wrmalloc(sizeof(t_type));
	temp->content = wrmalloc(sizeof(char) * (i + 2));
	while (y <= i)
	{
		temp->content[y] = line[y];
		y++;
	}
	temp->content[y] = 0;
	temp->type = type;
	ft_printf("-+-|%s|-+- %i\n",temp->content,temp->type);

	if (str_type != NULL)
		str_type->next = temp;
	return (i);
}

int		split_type(char *line)
{
	int i;
	int j;
	t_type	*str_type;

	str_type = NULL;
	int u;
	u = -1;
	j = 0;
	i = 0;
	while (line[i])
	{

		if (j != 0 && line[i] == j)
			j = 0;
		else if (line[i] == '\"' || line[i] == '\'')
			j = line[i];
		else if (j == 0 && (line[i] == '>' && line[i + 1] == '>'))
			u = create_struc(line + u, i - u, 5, str_type);
*/		else if (j == 0 && line[i] == '<')
			u = create_struc(line + u + 1, i - u - 1, 4, str_type) + u + 1;	
		else if (j == 0 && line[i] == '>')
			u = create_struc(line + u + 1, i - u - 1, 3, str_type) + u + 1;
		else if (j == 0 && line[i] == '|')
			u = create_struc(line + u + 1, i - u - 1, 2, str_type) + u + 1;
		else if (j == 0 && line[i] == ';')
			u = create_struc(line + u + 1, i - u - 1, 1, str_type) + u + 1;
//			create_struc(line + u, i - u, 1, str_type);
		i++;
	}
	if (((i - 1) - u) > 0 && line[u + 1] )
		create_struc(line + u + 1, (i - 2) - u, 4, 0);

	ft_printf("\n");
	return (0);
}

char	***prepare_array(char *line, t_all *all)
{
	char	***teub;
	int		cmds;
	int		i;
	int		j;
	int		args;

	if ((cmds = splitter_counter_cmd(line, all, -1)) < 0)
		return (NULL);
	if (!(teub = wrmalloc((cmds + 1) * sizeof(char**))))
		ft_exit(MALLOC);
	if (!(teub[cmds] = wrmalloc(1 * sizeof(char*))))
		ft_exit(MALLOC);
	set_value(teub, cmds, &i, &j);
	while (++i < cmds)
	{
		if ((args = splitter_counter_args(line, all, &j)) < 0)
			return (NULL);
		if (!(teub[i] = wrmalloc((args + 1) * sizeof(char**))))
			ft_exit(MALLOC);
		if (!(teub[i][args] = wrmalloc(1 * sizeof(char*))))
			ft_exit(MALLOC);
		teub[i][args] = 0;

		split_type(line);

		fill_teub(teub[i], line, all);
		handler(teub[i], all, get_env_st(NULL), 0);
	}
	return (teub);
}
