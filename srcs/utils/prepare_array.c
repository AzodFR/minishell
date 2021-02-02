/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 11:41:28 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/02 14:32:24 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

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
	temp->prev = NULL;
	if (str_type == NULL)
		return (temp);
	while (str_type->next != NULL)
		str_type = str_type->next;
	temp->prev = str_type;
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

int		jump_cote(char *line, int i, char *line_p, t_type **str_type, int *u)
{
	char	c;
	int		y;

	y = i;
	if ((line[i] == '\'' || line[i] == '\"') && line_p[i] == '0')
	{
		c = line[i];
		if (i > u[0])
			str_type[0] = create_struc(&line[u[0]], i - 1 - u[0],
				check_type(line, 0, '0'), str_type[0]);
		i++;
		while (line[i] && (!(line[i] == c && line_p[i] == '0')))
			i++;
		if (!(line[i]))
			return (-1);
		else if (line[i] == '\"')
			str_type[0] = create_struc(line + y, i - y, 7, str_type[0]);
		else
			str_type[0] = create_struc(line + y, i - y, 6, str_type[0]);
		u[0] = i + 1;
	}
	return (i + 1);
}

int		moov_type(int u, char *line)
{
	int y;

	y = u;
	if (line[y] == '>')
	{
		while (y > 0 && line[y] == '>')
			y--;
		while (y > 0 && ft_isalnum(line[y]))
			y--;
		if (y > 0 && line[y] == ' ')
			return (y + 1);
	}
	return (u);
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
	while (line[i])
	{
		type = check_type(line, i, line_p[i]);
		if ((i = jump_cote(line, i, line_p, &f_type, &u)) == -1)
			return (0);
		if (line_p[i] == '0' && check_type(line, i, '0') != type)
		{
			f_type = create_struc(line + moov_type(u, line), moov_type(i, line)
				- moov_type(u, line) - 1, check_type(line, i - 1, '0'), f_type);
			u = i;
		}
	}
	if (u != i)
		f_type = create_struc(line + moov_type(u, line), moov_type(i, line)
			- moov_type(u, line) - 1, check_type(line, i - 1, '0'), f_type);
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

char	*check_translation(char *s)
{
	int		i;
	char	*r;
	int		esc;

	i = -1;
	r = ft_strdup("");
	while (s[++i])
	{
		esc = 0;
		if (s[i] == '\\')
		{
			esc = 1;
			++i;
		}
		if (!s[i])
			break;
		if (s[i] == '$' && !esc)
			r = stran(s, &i, get_all_st(NULL), r);
		if (!s[i])
			break;
		r = add_one(r, s[i]);
	}
	return (r);
}

t_type *prepare_array(char *line)
{
//	LAUCHER DE MA FONCTION
	t_type	*first_type;
	t_type	*tmp;

	first_type = split_type(line, line_pre(line));
	tmp = first_type;
	while (tmp)
	{
		//ft_printf("%s               %i\n", tmp->content, tmp->type);
		if (tmp->type == 0 || tmp->type == 7)
			tmp->content =  check_translation(tmp->content);
		//ft_printf("-----------------------\n");
		tmp = tmp->next;
	}
	tmp = first_type;
	return (first_type);
}
