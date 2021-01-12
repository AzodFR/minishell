/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:57:02 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/12 14:20:00 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

char	*recreate(char *s, int *i, char *r, int j)
{
	char	*tmp;
	char	*ret;
	
	s[*i] = 0;
	tmp = ft_strjoin(s, r);
	s[*i] = '$';
	ret = ft_strjoin(tmp, &s[*i + j]);
	*i = ft_strlen(tmp) - 1;
	wrfree(s);
	wrfree(tmp);
	return (ret);
}

char	*ft_translate(char *s, t_env *env, t_all *all)
{
	int		i;
	int		j;
	char	*tmp;
	char	state[2];

	i = -1;
	state[1] = 0;
	while (s[++i])
	{
		if (s[i] == '$')
		{
			j = 1;
			while (s[i + j] && (ft_isalnum(s[i + j]) ||
			(j == 1 && s[i + j] == '?') || s[i + j] == '_'))
				if	((j++ == 1 && s[i + j - 1] == '?'))
					break;
			j--;
			tmp = ft_strndup(&s[i + 1], j);
			if (!ft_strncmp(tmp, "?", 1) && (state[0] = all->state + '0'))
				s = recreate(s, &i, state, j + 1);
			else if (env_find(env, tmp))
				s = recreate(s, &i, env_find(env, tmp)->value, j + 1);
			else
				s = recreate(s, &i, "", j + 1);
			wrfree(tmp);
		}
	}
	return (s);
}