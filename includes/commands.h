/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 15:18:46 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/13 15:20:42 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H
# include "libft.h"

typedef struct		s_cmd
{
	void			*content;
	t_list			*args;
	struct s_cmd	*next;
}					t_cmd;

#endif