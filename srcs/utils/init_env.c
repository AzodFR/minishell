/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 17:14:19 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/12 12:19:18 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

char	*get_name(char *s)
{
	int		i;
	char	*name;

	i = 0;
	while (s[i] != '=' && s[i])
		i++;
	if (!(name = wrmalloc(i + 1 * sizeof(char))))
		ft_exit(MALLOC);
	i = -1;
	while (s[++i] != '=' && s[i])
		name[i] = s[i];
	if (i && (s[i] && s[i] == '=') && (s[i - 1] && s[i - 1] == '+'))
		name[i - 1] = 0;
	name[i] = 0;
	return (name);
}

char	*get_value(char *s)
{
	int		i;
	int		j;
	char	*value;

	i = -1;
	j = 0;
	while (s[++i] != '=')
		;
	while (s[i + ++j])
		;
	if (!(value = wrmalloc(j + 1 * sizeof(char))))
		ft_exit(MALLOC);
	++i;
	j = -1;
	while (s[i + ++j])
		value[j] = s[i + j];
	value[j] = 0;
	return (value);
}

t_env	*init_env(char **env)
{
	t_env	*lst;
	int		i;

	i = 0;
	if (!(lst = wrmalloc(sizeof(t_env))))
		ft_exit(MALLOC);
	lst = ft_envnew(get_name(env[i]), get_value(env[i]));
	while (env[++i])
		ft_envadd_back(&lst, ft_envnew(get_name(env[i]), get_value(env[i])));
	return (lst);
}

int		too_much(t_type *tmp)
{
	int		i;
	int		j;
	int		type;
	char	set[2];

	i = 0;
	j = 0;
	set[0] = '>';
	set[1] = '<';
	type = 0;
	if (tmp->type == 4)
		type = 1;
	while (tmp->content[i])
		i++;
	while (i > 0 && tmp->content[--i] && tmp->content[i] == set[type])
		j++;
	return (type ? j > 1 : j > 2);
}
