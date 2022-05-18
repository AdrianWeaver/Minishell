/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 13:24:57 by jcervoni          #+#    #+#             */
/*   Updated: 2022/05/18 12:11:15 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

# include "minishell_struct.h"
# include "libft.h"

t_arg	*ft_get_args(char *input);
t_arg	*ft_get_dquote_arg(char *input, int *i, t_arg *arg);
int		ft_set_token(t_arg *args);
int		ft_check_quotes(char input);
t_arg	*ft_get_arg(char *input, int *i, t_arg *arg);
int		ft_check_operator(char c);
void	*ft_custom_calloc(int size);
t_arg	*ft_get_infile(t_arg *arg);
t_arg	*ft_get_heredoc(t_arg *arg);
t_arg	*ft_get_outfile(t_arg *arg);
t_arg	*ft_get_appendout(t_arg *arg);
void	ft_join_cmd(t_arg *arg);
int		ft_remove_dquotes(t_arg *arg, int *dq_nbr);
int		ft_check_dquotes(t_arg *arg);
int		*ft_count_dquotes(t_arg *arg);
void	ft_set_final_dq_index(t_arg *arg, int *dq_nbr, t_env *env);
char	*ft_get_expanded(char *str, t_env *env);
int		ft_count_expand(t_arg *arg, t_env *env);
char	**ft_lock_expand(int size);
int		ft_expand_size(char *str, t_env *env);
void	ft_final_string(t_arg *arg, char **pieces, char *flags, t_env *env);
int		ft_check_var(char *str, t_env *env);
int		ft_check_env_var(char *str, t_env *env);
int		ft_set_dq_jump(char *str);
void	ft_get_strings(t_arg *arg, char **pieces, char *flags, t_env *env);
char	*ft_get_var_pos(char *str, t_env *env);

int		ft_test(t_arg *arg, t_env *env);

#endif
