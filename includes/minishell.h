/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 09:18:31 by aweaver           #+#    #+#             */
/*   Updated: 2022/06/20 15:17:29 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define TOKEN_INFILE 0
# define TOKEN_HEREDOC 1
# define TOKEN_CMD 2
# define TOKEN_PIPE 3
# define TOKEN_QUOTE 4
# define TOKEN_DQUOTE 5
# define TOKEN_OUTFILE 6
# define TOKEN_APPENDOUT 7

# define FREE 0
# define MALLOC 1
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdarg.h>
# include "minishell_struct.h"
# include "minishell_parsing.h"
# include "libft.h"
# include "libftprintf.h"

/* ************************************************************************ */
/*								PARSING										*/
/* ************************************************************************ */

/* ************************************ */
/*              ARGS TOOLS              */
/* ************************************ */

t_arg	*ft_newarg(char *argv);
t_arg	*ft_lastarg(t_arg *arg);
void	ft_addarg_back(t_arg **argl, t_arg *new);
void	ft_clear_arg(t_arg *arg);
int		ft_argsize(t_arg *arg);

/* ************************************ */
/*              ARGS TOOLS              */
/* ************************************ */

t_mlc	*ft_newmlc(void *adr);
t_mlc	*ft_lastmlc(t_mlc *mlc);
void	ft_addmlc_back(t_mlc **mlcl, t_mlc *new);
void	ft_clearmlc(t_mlc *mlc);
int		ft_mlcsize(t_mlc *mlc);

t_arg	*ft_get_args(char *input);
t_arg	*ft_get_quote_arg(char *input, int *i, t_arg *arg, char delim);
int		ft_set_token(t_arg *args);
int		ft_check_quotes(char input);
t_arg	*ft_get_arg(char *input, int *i, t_arg *arg);
void	*ft_custom_calloc(int size);

/* ************************************************************************ */
/*								ENV FUNCTIONS								*/
/* ************************************************************************ */

t_env	*ft_env_last(t_env *env);
void	ft_env_add_back(t_env **env_start, t_env *new);
t_env	*ft_get_env_element(t_env *env, char *env_line);
void	ft_delone_env(t_env *env, void (*del)(void *));
void	ft_cleanly_delone_env(t_env **env_start, t_env *target);
void	ft_print_env(t_env *env_list);
char	**ft_env_to_char(t_env *env);
t_env	*ft_env_to_list(char **env);
int		ft_env_size(t_env *env);
void	ft_manually_add_one_env(t_env *env_list, char *name, char *content);

/* ************************************************************************ */
/*								FREE FUNCTIONS								*/
/* ************************************************************************ */

void	ft_free_double_array(char **str);
void	ft_free_env(t_env *env_start);
void	*ft_magic_malloc(int function, size_t size, void *addr);

/* ************************************************************************ */
/*								BUILTIN FUNCTIONS							*/
/* ************************************************************************ */

/* unset */
int		ft_is_valid_env_variable(char *str);
t_env	*ft_find_env_elem(t_env *env_list, char *name);
int		ft_unset(t_env **env_list, char **name);
int		ft_export(t_env *env_list, char **to_add);
void	ft_print_pwd(void);
char	*ft_get_pwd(void);
int		ft_cd(t_env *env, char *path);

/* export */
int		ft_export(t_env *env_list, char **to_add);

/*  echo  */
int		ft_echo_n_opt(t_arg *arg);
int		ft_echo_nbr_cmd(t_arg *arg);
int		ft_echo(t_arg *arg);

void	ft_builtin_parser(t_arg *arg);

#endif
