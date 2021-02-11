/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 14:03:32 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/11 11:41:06 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

char		*translate(char *s, int *i, t_all *all, char *string)
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
	wrfree(tmp);
	wrfree(ret);
	return (string);
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
