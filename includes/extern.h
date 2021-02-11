/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 11:11:12 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/11 11:14:27 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTERN_H
# define EXTERN_H
# include "ft_printf.h"
# include "donut.h"
# include "struct.h"
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <curses.h>
# include <term.h>
# include <unistd.h>
# include <fcntl.h>
# define EXIT_SUCCESS 0
# define EXIT_FAILED 1
# define SUCCESS 0
# define FAILED 1
# define MALLOC 2
# define QUIT 3
# define BAD_ENV 4
# define QUOTE 5
#endif