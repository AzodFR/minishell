/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_opener.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 19:23:41 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/11 10:56:27 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

int			open_one_right(char **teub)
{
	int				i;
	int				fd;
	char			*join;

	i = -1;
	while (teub[++i])
	{
		fd = open(teub[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
		{
			join = ft_strjoin(teub[i], ": ");
			ft_dprintf(2,"\033[32mMiShell \033[31m✘ \033[0m");
		    ft_dprintf(2,"%s %s\n", join, strerror(errno));
			get_all_st(NULL)->state = 1;
			wrfree(join);
			return (fd);
		}
	}
	return (fd);
}

int			open_double_right(char **teub)
{
	int				i;
	int				fd;
	char			*join;

	i = -1;
	while (teub[++i])
	{
		fd = open(teub[i], O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd == -1)
		{
			join = ft_strjoin(teub[i], ": ");
			ft_dprintf(2,"\033[32mMiShell \033[31m✘ \033[0m");
		    ft_dprintf(2,"%s %s\n", join, strerror(errno));
			get_all_st(NULL)->state = 1;
			wrfree(join);
			return (fd);
		}
	}
	return (fd);
}

int			open_one_left(char **teub)
{
	int				i;
	int				fd;
	char			*join;

	i = -1;
	while (teub[++i])
	{
		fd = open(teub[i], O_RDONLY);
		if (fd == -1)
		{
			join = ft_strjoin(teub[i], ": ");
			ft_dprintf(2,"\033[32mMiShell \033[31m✘ \033[0m");
		    ft_dprintf(2,"%s %s\n", join, strerror(errno));
			get_all_st(NULL)->state = 1;
			wrfree(join);
			return (fd);
		}
	}
	return (fd);
}

int					create_file(int type, char **file_name)
{
	int				fd;

	fd = -1;
	if (type == 3)
		fd = open_one_right(file_name);
	else if (type == 5)
		fd = open_double_right(file_name);
	else if (type == 4)
		fd = open_one_left(file_name);
	return (fd);
}
