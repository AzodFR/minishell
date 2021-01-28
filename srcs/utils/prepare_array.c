/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedelfos <jedelfos@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 11:41:28 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/28 16:49:05 by jedelfos         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

void	fill_teub(char **teub, char *line, t_all *a)
{
	static	int		j = -1;

	a->flag_quote = 0;
	a->flag_esc = 0;
	a->flag_cmd = 0;
	get_blocks(teub, line, &j);
}

void	set_value(char ***teub, int cmds, int *i, int *j)
{
	teub[cmds] = 0;
	*i = -1;
	*j = -1;
}

t_type	*create_struc(char *line, int i, char type, t_type *str_type)
{
	int		y;
	t_type	*temp;
	t_type	*save_first;

	save_first = str_type;
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
	temp->next = NULL;
	if (str_type == NULL)
		return (temp);
	while (str_type->next != NULL)
		str_type = str_type->next;
	str_type->next = temp;
	return (save_first);
}

char	check_type(char *str, int i, char c)
{
	if (c == '1')
		return (0);
	if (str[i] == '>' && str[i + 1] == '>')
		return (5);
	else if (i > 0 && (str[i] == '>' && str[i - 1] == '>'))
		return (5);
	else if (str[i] == '<')
		return (4);
	else if (str[i] == '>')
		return (3);
	else if (str[i] == '|')
		return (2);
	else if (str[i] == ';')
		return (1);
	return (0);
}

int		jump_cote(char *line, int i, char *line_p)
{
	char	c;

	if ((line[i] == '\'' || line[i] == '\"') && line_p[i] == '0')
	{
		c = line[i];
		i++;
		while (line[i] && (!(line[i] == c && line_p[i] == '0')))
			i++;
		if (!(line[i]))
			return (-1);
	}
	return (i);
}

t_type	*split_type(char *line, char *line_p)
{
	t_type	*f_type;
	int		i;
	char	type;
	int		u;

	f_type = NULL;
	u = 0;
	i = 0;
	type = check_type(line, 0, '0');
	while (line[0] && line[i])
	{
		type = check_type(line, i, line_p[i]);
		if ((i = jump_cote(line, i + 1, line_p)) == -1)
			return (0);
		if (line_p[i] == '0' && check_type(line, i, '0') != type)
		{
			f_type = create_struc(line + u, i - u - 1,
				check_type(line, i - 1, '0'), f_type);
			u = i;
		}
	}
	if (u != i)
		create_struc(line + u, i - u - 1, check_type(line, i - 1, '0'), f_type);
	wrfree(line_p);
	return (f_type);
}

char	*line_pre(char *line)
{
	int		i;
	char	*line_temp;

	i = 0;
	line_temp = wrmalloc(ft_strlen(line) + 1);
	line_temp[i] = '0';
	while (line[i])
	{
		if (line[i] == '\\' && line_temp[i] != '1')
			line_temp[i + 1] = '1';
		else
			line_temp[i + 1] = '0';
		i++;
	}
	line_temp[i] = 0;
	return (line_temp);
}

char	***prepare_array(char *line, t_all *all)
{
	char	***teub;
	int		cmds;
	int		i;
	int		j;
	int		args;


//	LAUCHER DE MA FONCTION
	t_type	*first_type;

	first_type = split_type(line, line_pre(line));
	while (first_type)
	{
		ft_printf("%s               %i\n", first_type->content, first_type->type);
		first_type = first_type->next;
	}
// RESET DE LINE
	line = strdup("");


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
		fill_teub(teub[i], line, all);
		handler(teub[i], all, get_env_st(NULL), 0);
	}
	return (teub);
}
