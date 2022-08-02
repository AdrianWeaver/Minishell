/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 10:10:48 by aweaver           #+#    #+#             */
/*   Updated: 2022/08/02 13:10:51 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdbool.h>

# if defined (__APPLE__)
#  define PTR_NULL "0x0"
# elif __linux__
#  define PTR_NULL "(nil)"
# endif

# ifndef CONVERSION
#  define CONVERSION "cspdiuoxX%"
# endif

# ifndef NOTINSUBJECT
#  define NOTINSUBJECT "hlLqjzZteEfFgGaACSPnm"
# endif

typedef struct s_list_printf
{
	int		i;
	int		ret;
	bool	flag_zero;
	bool	flag_hyphen;
	bool	flag_precision;
	int		precision_width;
	bool	flag_hashtag;
	bool	flag_space;
	bool	flag_plus;
	int		width;
}			t_list_printf;

# ifndef FT_FLAG_HYPHEN
#  define FT_FLAG_HYPHEN

void			ft_flag_hyphen(t_list_printf *list);

# endif

# ifndef FT_EFLAG_HYPHEN
#  define FT_EFLAG_HYPHEN

void			ft_eflag_hyphen(t_list_printf *list, char **output);

# endif

# ifndef FT_PRINTF
#  define FT_PRINTF

int				ft_printf(const char *str, ...);
# endif

# ifndef FT_PRINTF_C
#  define FT_PRINTF_C

void			ft_printf_c(int c, t_list_printf *list);
# endif
# ifndef FT_PRINTF_S
#  define FT_PRINTF_S

void			ft_printf_s(char *str, t_list_printf *list);
# endif

# ifndef FT_PRINTF_P
#  define FT_PRINTF_P

void			ft_printf_p(unsigned long int addr, t_list_printf *list);

# endif

# ifndef FT_PRINTF_U
#  define FT_PRINTF_U

void			ft_printf_u(unsigned int unbr, t_list_printf *list);

# endif

# ifndef FT_PRINTF_ID
#  define FT_PRINTF_ID

void			ft_printf_id(int unbr, t_list_printf *list);

# endif

# ifndef FT_PRINTF_X
#  define FT_PRINTF_X

void			ft_printf_x(unsigned int unbr, t_list_printf *list,
					const char *src);

# endif

# ifndef FT_PRINTF_O
#  define FT_PRINTF_O

void			ft_printf_o(unsigned int unbr, t_list_printf *list,
					const char *src);

# endif

# ifndef FT_PRINTF_PUTNBR
#  define FT_PRINTF_PUTNBR

void			ft_printf_putnbr(int nbr, t_list_printf *list);
# endif

# ifndef FT_PRINTF_PUTNBR_BASE
#  define FT_PRINTF_PUTNBR_BASE

void			ft_printf_putnbr_base(int64_t nbr, int64_t base, int caps,
					t_list_printf *list);
# endif

# ifndef FT_PRINTF_UHEX
#  define FT_PRINTF_UHEX

void			ft_printf_uhex(unsigned long int nbr, unsigned long int base,
					int addr_flag, int caps);

# endif

# ifndef FT_CHECK_FLAGS
#  define FT_CHECK_FLAGS

void			ft_printf_check_flags(t_list_printf *list);

# endif

# ifndef FT_PRINTF_PARSE
#  define FT_PRINTF_PARSE

void			ft_printf_parse(const char *str, t_list_printf *list,
					va_list params);

# endif

# ifndef FT_LSTRESET
#  define FT_LSTRESET

void			ft_lstreset(t_list_printf *list);
# endif

# ifndef FT_ECHECK_PERCENT
#  define FT_ECHECK_PERCENT

void			ft_echeck_percent(const char *str,
					t_list_printf *list, va_list params, char **output);

# endif

int				ft_eprintf_conversion(const char *str,
					t_list_printf *list, va_list params, char **output);
# ifndef FT_EPRINTF
#  define FT_EPRINTF

int				ft_eprintf(const char *str, ...);

# endif
# ifndef FT_EPRINTF_C
#  define FT_EPRINTF_C

void			ft_eprintf_c(int c, t_list_printf *list, char **output);

# endif

# ifndef FT_EPRINTF_ID
#  define FT_EPRINTF_ID

void			ft_eprintf_id(int nbr, t_list_printf *list, char **output);

# endif

# ifndef FT_EPRINTF_O
#  define FT_EPRINTF_O

void			ft_eprintf_o(unsigned int unbr,
					t_list_printf *list, const char *src, char **output);
# endif

# ifndef FT_EPRINTF_P
#  define FT_EPRINTF_P

void			ft_eprintf_p(unsigned long int addr, t_list_printf *list, char
					**output);

# endif

# ifndef FT_EPRINTF_S
#  define FT_EPRINTF_S

void			ft_eprintf_s(char *str, t_list_printf *list, char **output);

# endif

# ifndef FT_EPRINTF_U
#  define FT_EPRINTF_U

void			ft_eprintf_u(unsigned int unbr, t_list_printf *list,
					char **output);

# endif

# ifndef FT_EPRINTF_X
#  define FT_EPRINTF_X

void			ft_eprintf_x(unsigned int unbr,
					t_list_printf *list, const char *src, char **output);

# endif
#endif
