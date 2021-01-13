/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 14:03:32 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/13 16:49:49 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

char		*sep_blocks(char *s, int *i, char c, char *string)
{
	char	*tmp;
	char	*tmp2;
	int		j;
	
	j = 1;
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

void	splitter(char *s, t_all *a)
{
	t_list		*cmds;
	char		*string;
	char		c;
	int			i;

	i = -1;
	if (!(cmds = wrmalloc(sizeof(t_list))))
		ft_exit(MALLOC);
	string = ft_strdup("");
	a->flag_quote = 0;
	a->flag_esc = 0;
	a->flag_cmd = 0;
	while (s[++i])
	{
		if ( i > 0 && s[i - 1] == '\\')
			a->flag_esc = 1;
		if (s[i] == '\\')
			continue ;
		if (!a->flag_esc && (s[i] == '\'' | s[i] == '\"') && (c = s[i]))
		{
			if (!(string = sep_blocks(&s[i + 1], &i, c, string)))
				if ((a->flag_quote = 1))
					break ;
		}
		else if (!a->flag_esc && s[i] == ';')
		{
			if (!a->flag_cmd && (a->flag_cmd = 1))
				cmds = ft_lstnew(ft_strdup(string));
			else
				ft_lstadd_back(&cmds, ft_lstnew(ft_strdup(string)));
			wrfree(string);
			string = ft_strdup("");
		}
		else
		{
			string = add_one(string, s[i]);
			a->flag_esc = 0;
		}
		
	}
	
	if (a->flag_quote)
	{
		ft_printf("\033[32mMiShell \033[31m✘ \033[0m");
		ft_printf("You need to close your quotes\n");
		return ;
	}
	if (!a->flag_cmd && (a->flag_cmd = 1))
				cmds = ft_lstnew(ft_strdup(string));
	else
		ft_lstadd_back(&cmds, ft_lstnew(ft_strdup(string)));
	wrfree(string);
	while (cmds)
	{
		ft_printf("|%s|\n", cmds->content);
		cmds = cmds->next;
	}
	return ;
}