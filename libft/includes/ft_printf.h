/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 15:48:49 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/14 13:31:44 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "../libft/includes/libft.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>

typedef struct		s_flags
{
	int		minus;
	int		zero;
	int		dot;
	int		star;
	int		len;
	char	type;
}					t_flags;
int					is_a_converter(char c);
t_flags				prepare_flags(const char *format, va_list ap, int *i);
int					set_dot(const char *f, t_flags *flags, int i, va_list ap);
int					set_star(t_flags *flags, int i, va_list ap);
int					set_minus(t_flags *flags, int i);
int					set_zero(t_flags *flags, int i);
int					set_len(const char f, t_flags *flags, int i);
int					prepare_string(const char *format, va_list ap);
int					apply_whitespace(char *str, t_flags flags);
t_flags				initstruct(void);
int					haveflags(t_flags flags);
int					convert(va_list ap, int i, t_flags flags);
int					convert_c(va_list ap, t_flags flags);
int					convert_s(va_list ap, t_flags flags);
int					convert_d_i(va_list ap, t_flags flags);
int					convert_u(va_list ap, t_flags flags);
int					convert_xx(va_list ap, t_flags flags, int small);
int					convert_p(va_list ap, t_flags flags);
int					convert_perc(t_flags flags);
int					print_direct(const char *format);
int					read_format(const char *format, va_list ap);
int					ft_printf(const char *format,
					...) __attribute__((format(printf,1,2)));
#endif
