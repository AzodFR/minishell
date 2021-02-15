/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 11:09:51 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/15 09:59:15 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

/*
**	STATE 2 ="blabla"
**	STATE 1 =""
**	STATE 0 =
*/
typedef struct			s_env
{
	char			*name;
	char			*value;
	int				state;
	struct s_env	*next;
}						t_env;

/*
**	TYPE 8 = space
**	TYPE 7 = "blabla"
**	TYPE 6 = 'blabla'
**	TYPE 5 = >>
**	TYPE 4 = <
**	TYPE 3 = >
**	TYPE 2 = |
**	TYPE 1 = ;
**	TYPE 0 = blabla
*/
typedef struct			s_type
{
	char			type;
	char			*content;
	struct s_type	*next;
	struct s_type	*prev;
}						t_type;
typedef struct			s_tree
{
	t_type			*cmd;
	struct s_tree	*right;
	struct s_tree	*left;
}						t_tree;

typedef struct			s_all
{
	int		state;
	int		flag_quote;
	int		fd[3];
	int		exit;
	int		prog;
	int		pid;
	t_tree	*last_node;
}						t_all;
#endif
