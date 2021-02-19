/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 11:41:28 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/19 10:58:36 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

char			*line_pre(char *line)
{
	int		i;
	char	*line_temp;
	int		sk;

	sk = 0;
	i = 0;
	line_temp = wrmalloc(ft_strlen(line) + 1);
	line_temp[i] = '0';
	while (line[i])
	{
		if (line[i] == '\'' && line_temp[i] == '0')
			sk = sk ? 0 : 1;
		if (line[i] == '\\' && line_temp[i] != '1' && sk == 0)
			line_temp[i + 1] = '1';
		else
			line_temp[i + 1] = '0';
		i++;
	}
	line_temp[i] = 0;
	return (line_temp);
}

static t_type	*close_quotes(void)
{
	ft_dprintf(
		2, "\033[32mMiShell \033[31m✘ \033[0mPlease close your quotes.\n");
	return (NULL);
}

char			**prep_line(char *line, char *line_p)
{
	char	**linep;

	linep = wrmalloc(2 * sizeof(char *));
	linep[0] = ft_strdup(line);
	linep[1] = ft_strdup(line_p);
	return (linep);
}

t_type			*prepare_array(char *line)
{
	t_type	*first_type;
	t_type	*tmp;

	if (!(first_type = split_type(prep_line(line, line_pre(line)), 0)))
		return (close_quotes());
	tmp = first_type;
	while (tmp)
	{
		if (tmp->type == 2)
			if (!ft_strncmp(tmp->content, "||", 2) || !tmp->next || no_cmd(tmp))
				return (errornear("|"));
		if (tmp->type == 1)
		{
			if (!ft_strncmp(tmp->content, ";;", 2))
				return (errornear(";;"));
			else if (no_prev(tmp))
				return (errornear(";"));
		}
		if (tmp->type > 2 && tmp->type < 6 && (no_next(tmp) || too_much(tmp)))
			return (errornear(tmp->content));
		tmp = tmp->next;
	}
	return (first_type);
}

void			translate_only(t_type *begin)
{
	t_type	*tmp;

	tmp = begin;
	while (tmp && tmp->type != 1)
	{
		if (tmp->type == 0 || tmp->type == 7)
		{
			if (tmp->type == 0 && tmp->content[0] == '~' && (!tmp->content[1] ||
			tmp->content[1] == '/'))
				tmp->content =
				ft_strjoin(
				env_find(get_env_st(NULL), "HOME")->value, tmp->content + 1);
			tmp->content = check_translation(tmp->content, tmp->type,
			tmp->next);
		}
		tmp = tmp->next;
	}
}
