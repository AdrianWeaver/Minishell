/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 09:18:31 by aweaver           #+#    #+#             */
/*   Updated: 2022/06/23 17:22:14 by aweaver          ###   ########.fr       */
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
# define ADD 2
# define FLUSH -1
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <fcntl.h>
# include <wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdarg.h>
# include "minishell_struct.h"
# include "minishell_parsing.h"
# include "libft.h"
# include "libftprintf.h"
# include "get_next_line.h"

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
char	**ft_list_to_char(t_arg *list);

/* ************************************************************************ */
/*								ENV FUNCTIONS								*/
/* ************************************************************************ */

t_env	*ft_env_last(t_env *env);
void	ft_env_add_back(t_env **env_start, t_env *new);
t_env	*ft_get_env_element(t_env *env, char *env_line);
void	ft_delone_env(t_env *env);
void	ft_cleanly_delone_env(t_env **env_start, t_env *target);
void	ft_print_env(t_env *env_list);
char	**ft_env_to_char(t_env *env);
t_env	*ft_env_to_list(char **env);
int		ft_env_size(t_env *env);
int		ft_is_valid_env_variable(char *str);
void	ft_deal_with_existing_env_var(t_env **env_list, t_env *to_add);
void	ft_manually_add_one_env(t_env *env_list, char *name, char *content);

/* ************************************************************************ */
/*								FREE FUNCTIONS								*/
/* ************************************************************************ */

void	ft_free_double_array(char **str);
void	ft_free_env(t_env *env_start);
void	*ft_magic_malloc(int funct, size_t size, void *addr);
void	ft_delone_mlc(t_mlc *mlc, void (*del)(void *));
void	ft_free_mlc_and_quit(t_mlc *mlc_start);
void	ft_cleanly_delone_mlc(t_mlc **mlc_start, void *addr);
t_mlc	*ft_malloc_list_add_back(t_mlc **mlc_list, t_mlc *new_mlc);

/* ************************************************************************ */
/*								BUILTIN FUNCTIONS							*/
/* ************************************************************************ */

/* unset */
t_env	*ft_find_env_elem(t_env *env_list, char *name);
int		ft_unset(t_env **env_list, char **name);
void	ft_print_pwd(void);
char	*ft_get_pwd(void);

/* cd */
int		ft_cd(t_env *env, char *path);

/* export */
int		ft_export(t_env **env_list, char **to_add);

/*  echo  */
int		ft_echo_n_opt(t_arg *arg);
t_arg	*ft_echo_skip_opt(t_arg *arg, int *n_opt);
int		ft_echo(t_arg *arg);

void	ft_builtin_parser(t_env **env, t_arg *arg);

/* ************************************************************************ */
/*								REDIRECTION FUNCTIONS            			*/
/* ************************************************************************ */

int		ft_heredoc(t_arg *arg, t_env *env);
void	ft_fill_heredoc(int file, char *delim, int flag, t_env *env);
int		ft_check_delim(t_arg *arg);
char	*ft_expand_heredoc(char *line, t_env *env);
int		ft_count_hd_expand(char *line, char *flags, t_env *env);
char	*ft_final_hd_string(char *line, char **pieces, char *flags, t_env *env);
void	ft_get_hd_strings(char *line, char **pieces, char *flags, t_env *env);

#endif
