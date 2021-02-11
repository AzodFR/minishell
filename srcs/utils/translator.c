/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 14:03:32 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/11 15:48:24 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

static	char	*free_ret_char(char *tmp, char *ret, char *string)
{
	wrfree(tmp);
	wrfree(ret);
	return (string);
}

char			*translate(char *s, int *i, t_all *all, char *string)
{
	int		j;
	char	*tmp;
	char	*ret;

	j = 1;
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
	if (!ft_strncmp(tmp, "?", 1))
		string = ft_strjoin(ret, ft_itoa(all->state));
	else if (env_find(get_env_st(NULL), tmp))
		string = ft_strjoin(ret, env_find(get_env_st(NULL), tmp)->value);
	else
		string = ft_strjoin(ret, "");
	return (free_ret_char(tmp, ret, string));
}

char			*add_one(char *s, char c)
{
	char	new[2];
	char	*tmp;

	new[0] = c;
	new[1] = 0;
	tmp = ft_strjoin(s, new);
	wrfree(s);
	return (tmp);
}

char			*check_translation(char *s)
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
			break ;
		while (s[i] == '$' && !esc && s[i + 1] && s[i + 1] != ' ')
			r = translate(s, &i, get_all_st(NULL), r);
		if (!s[i])
			break ;
		r = add_one(r, s[i]);
	}
	return (r);
}
