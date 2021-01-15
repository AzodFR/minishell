/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 14:03:32 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/15 14:14:57 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

char		*sep_blocks(char *s, int *i, char c, char *string, t_all *a)
{
	char	*tmp;
	char	*tmp2;
	int		j;

	j = 0;
	while (s[j])
	{
		if (s[j - 1] == '\\' && s[j] == c)
			j++;
		else if (s[j] == c)
			break ;
		else
			j++;
	}
	if (s[j] != c)
		return (NULL);
	tmp = ft_strndup(s, j);
	if (c == '\"')
		tmp = ft_translate(tmp, get_env_st(NULL), a, -1);
	tmp2 = ft_strjoin(string, tmp);
	wrfree(tmp);
	wrfree(string);
	*i = *i + j + 1;
	return (tmp2);
}

char		*add_one(char *s, char c)
{
	char	new[2];
	char	*tmp;

	new[0] = c;
	new[1] = 0;
	tmp = ft_strjoin(s, new);
	wrfree(s);
	return (tmp);
}

char		*stran(char *s, int *i, t_all *all, char *string)
{
	int		j;
	char	*tmp;
	char	*ret;
	char	state[2];

	j = 1;
	state[1] = 0;
	ret = ft_strdup(string);
	if (!ft_isdigit(s[*i + j]) && s[*i + j] != ' ')
	{
		while (s[*i + j] && (ft_isalnum(s[*i + j]) ||
		(j == 1 && s[*i + j] == '?') || s[*i + j] == '_'))
			if ((j++ == 1 && s[*i + j - 1] == '?'))
				break ;
	}
	else
		++j;
	tmp = ft_strndup(&s[*i + 1], j - 1);
	wrfree(string);
	*i += j;
	if (!ft_strncmp(tmp, "?", 1) && (state[0] = all->state + '0'))
		string = ft_strjoin(ret, state);
	else if (env_find(get_env_st(NULL), tmp))
		string = ft_strjoin(ret, env_find(get_env_st(NULL), tmp)->value);
	else
		string = ft_strjoin(ret, "");
	wrfree(tmp);
	wrfree(ret);
	return (string);
}

void		get_blocks(char **teub, char *s, int *j)
{
	char		*string;
	char		c;
	int			i;
	int			k;
	t_all *a;

	i = *j;
	k = -1;
	a = get_all_st(NULL);
	string = ft_strdup("");
	a->flag_cmd = 0;
	while (s[++i])
	{
		if (i == *j + 1 && !a->flag_cmd && s[i] == ' ' && (a->flag_cmd = 1))
			while (s[++i] == ' ' && s[i])
				;
		if (i > 0 && s[i - 1] == '\\')
			a->flag_esc = 1;
		if (s[i] == '\\' && (a->flag_esc = 1))
			continue ;
		while (!a->flag_esc && s[i] == '$' && s[i + 1] != ' ')
			string = stran(s, &i, a, string);
		if (!s[i])
			break ;
		if (!a->flag_esc && (s[i] == '\'' | s[i] == '\"') && (c = s[i]))
			string = sep_blocks(&s[i + 1], &i, c, string, a);
		else if (s[i] == ' ')
		{
			while (s[i] == ' ' && s[i])
				i++;
			i--;
			teub[++k] = ft_strdup(string);
			wrfree(string);
			string = ft_strdup("");
		}
		else if (!a->flag_esc && s[i] == ';')
		{
			teub[++k] = ft_strdup(string);
			wrfree(string);
			*j = i;
			teub[++k] = 0;
			return ;
		}
		else
		{
			string = add_one(string, s[i]);
			a->flag_esc = 0;
		}
	}
	teub[++k] = ft_strdup(string);
	wrfree(string);
	teub[++k] = 0;
	return ;
}
