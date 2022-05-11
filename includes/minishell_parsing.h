/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 13:24:57 by jcervoni          #+#    #+#             */
/*   Updated: 2022/05/10 15:50:31 by jcervoni         ###   ########.fr       */
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
void	*ft_custom_calloc(int size);
t_arg	*ft_get_infile(t_arg *arg);
t_arg	*ft_get_heredoc(t_arg *arg);
t_arg	*ft_get_outfile(t_arg *arg);
t_arg	*ft_get_appendout(t_arg *arg);
void	ft_join_cmd(t_arg *arg);

#endif
