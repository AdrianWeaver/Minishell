/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 13:24:57 by jcervoni          #+#    #+#             */
/*   Updated: 2022/07/23 19:48:26 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

# include "minishell_struct.h"
# include "libft.h"

t_arg	*ft_get_args(char *input);
t_arg	*ft_get_infile(t_arg *arg, t_arg *head);
t_arg	*ft_get_heredoc(t_arg *arg, t_arg *head);
t_arg	*ft_get_outfile(t_arg *arg, t_arg *head);
t_arg	*ft_get_appendout(t_arg *arg, t_arg *head);
t_arg	*ft_get_arg(char *input, int *i, t_arg *arg);
char	*ft_get_prompt(void);
char	*ft_get_short_path(char *cwd);
int		ft_check_op(char c);
int		ft_check_arg(char c);
int		ft_set_token(t_arg *args);

/* ************************************************************************** */
/*                                   QUOTES                                   */
/* ************************************************************************** */

t_arg	*ft_get_quote_arg(char *input, int *i, t_arg *arg, char delim);
void	ft_fill_q_tab(char *str, int *dq_nbr);
void	ft_set_final_q_index(t_arg *arg, char *flags, int *dq_nbr, t_env *env);
int		ft_set_q_jump(char *str);
int		*ft_count_quotes(t_arg *arg);
int		*ft_lock_quote_pos(t_arg *arg, int dq);
int		ft_remove_quotes(t_arg *arg, int *dq_nbr);

/* ************************************************************************** */
/*                             VARIABLE EXPANSION                             */
/* ************************************************************************** */

char	**ft_lock_expand(int size);
char	*ft_get_var_pos(char *str, t_env *env);
char	*ft_get_expanded(char *str, t_env *env);
void	ft_flag_char(char *str, char *flags);
void	ft_get_strings(t_arg *arg, char **pieces, char *flags, t_env *env);
void	ft_final_string(t_arg *arg, char **pieces, char *flags, t_env *env);

int		ft_check_and_expand(t_arg *arg, t_env *env);
int		ft_check_var(char *str, t_env *env);
int		ft_expand_size(char *str, t_env *env);
int		ft_check_env_var(char *str, t_env *env);
int		ft_count_expand(t_arg *arg, char *flags, t_env *env);

/* ************************************************************************** */
/*                                REDIRECTIONS                                */
/* ************************************************************************** */

void	ft_clear_and_quit(t_arg *arg, t_arg *head);
void	ft_set_redirections(t_arg *arg, t_arg *head);
int		ft_redirection(t_arg *arg, t_env *env, int std[2]);
int		ft_redirection_in(t_arg *arg, t_env *env, int std[2]);
int		ft_check_first_arg(t_arg *arg);
int		ft_check_wrong_arg(t_arg *arg);
int		ft_redirection_out(t_arg *arg);
int		ft_get_redirections(t_arg *arg);
int		ft_check_single_redir(t_arg *arg);
int		ft_check_double_redir(t_arg *arg);
int		ft_check_double_pipe(t_arg *arg, t_arg *head);

#endif
