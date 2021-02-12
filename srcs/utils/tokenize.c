/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:35:37 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/12 11:06:33 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

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
	else if (str[i] == ' ' || str[i] == '\t')
		return (8);
	return (0);
}

int		jump_cote(char **line, int i, t_type **str_type, int *u)
{
	char	c;
	int		y;

	y = i + 1;
	if ((line[0][i] == '\'' || line[0][i] == '\"') && line[1][i] == '0')
	{
		c = line[0][i];
		if (i > u[0])
			str_type[0] = create_struc(&line[0][u[0]], i - 1 - u[0],
				check_type(line[0], 0, '0'), str_type[0]);
		i++;
		while (line[0][i] && (!(line[0][i] == c && line[1][i] == '0')))
			i++;
		if (!(line[0][i]))
			return (-1);
		else if (line[0][i] == '\"')
			str_type[0] = create_struc(line[0] + y, i - y - 1, 7, str_type[0]);
		else
			str_type[0] = create_struc(line[0] + y, i - y - 1, 6, str_type[0]);
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
		while (y > 0 && ft_isdigit(line[y]))
			y--;
		if (y > 0 && line[y] == ' ')
			return (y + 1);
	}
	return (u);
}

t_type	*split_type(char **linep, int u)
{
	t_type	*f_type;
	int		i;
	char	type;

	f_type = NULL;
	i = 0;
	while (linep[0][i])
	{
		type = check_type(linep[0], i, linep[1][i]);
		if ((i = jump_cote(linep, i, &f_type, &u)) == -1)
			return (0);
		if (linep[1][i] == '0' && check_type(linep[0], i, '0') != type)
		{
			f_type = create_struc(linep[0] + moov_type(u, linep[0]),
				moov_type(i, linep[0]) - moov_type(u, linep[0]) - 1,
					check_type(linep[0], i - 1, '0'), f_type);
			u = i;
		}
	}
	if (u != i)
		f_type = create_struc(linep[0] + moov_type(u, linep[0]),
		moov_type(i, linep[0]) - moov_type(u, linep[0]) - 1,
		check_type(linep[0], i - 1, '0'), f_type);
	wrfree(linep[1]);
	return (f_type);
}
