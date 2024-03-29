/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 09:18:31 by aweaver           #+#    #+#             */
/*   Updated: 2022/08/02 19:49:21 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define TOKEN_INFILE 0
# define TOKEN_HEREDOC 1
# define TOKEN_CMD 2
# define TOKEN_PIPE 3
# define TOKEN_AND 4
# define TOKEN_OUTFILE 6
# define TOKEN_APPENDOUT 7

/* ************************************************************************ */
/*							MAGIC MALLOC DEFINES							*/
/* ************************************************************************ */
# ifndef MS_MAGIC_MALLOC_DEFINES
#  define MS_MAGIC_MALLOC_DEFINES
#  define FREE 0
#  define MALLOC 1
#  define ADD 2
#  define FLUSH -1
# endif

/* ************************************************************************ */
/*						SIGNAL HANDLE INTERACTIVE DEFINE					*/
/* ************************************************************************ */
# ifndef MS_SIGNAL_INTERACTIVE
#  define MS_SIGNAL_INTERACTIVE
#  define INTERACTIVE 1
#  define NOT_INTERACTIVE 0
# endif

/* ************************************************************************ */
/*								OTHER DEFINES								*/
/* ************************************************************************ */
# define MS_NOFILE -22
# define MS_CTRLD -23
# define NOT_FOUND "command not found"
# define SYNTAX_ERROR "minishell: syntax error near unexpected token"
# define IS_DIR "Is a directory"
# define MS_NOCWD "minishell: currrent working directory no longer exists"
# define MS_NOCWD2 "\nquitting execution to prevent undefined behaviours\n"
# define MS_WTF "ᛞᛟ ᚾᛟᛏ ᛞᛟ ᚦᛁᛋ ᛈᛚᛖᚨᛋᛖ\n" 

# ifndef DEBUG
#  define DEBUG 1
# endif

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>
# include <errno.h>
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

extern int	g_ret_value;

/* ************************************************************************ */
/*                              MAIN FUNCTIONS                              */
/* ************************************************************************ */

t_arg	*ft_init_shell(int std[2]);
int		ft_main_loop(t_arg *arg, t_env **env, int std[2]);

/* ************************************************************************ */
/*                                 PARSING                                  */
/* ************************************************************************ */

/* ************************************ */
/*              ARGS TOOLS              */
/* ************************************ */

t_arg	*ft_newarg(char *argv);
t_arg	*ft_lastarg(t_arg *arg);
void	ft_clear_arg(t_arg *arg);
void	ft_addarg_back(t_arg **argl, t_arg *new);
int		ft_argsize(t_arg *arg);

/* ************************************ */
/*              ARGS TOOLS              */
/* ************************************ */

t_mlc	*ft_newmlc(void *adr);
t_mlc	*ft_lastmlc(t_mlc *mlc);
void	ft_clearmlc(t_mlc *mlc);
void	ft_addmlc_back(t_mlc **mlcl, t_mlc *new);
int		ft_mlcsize(t_mlc *mlc);

t_arg	*ft_get_args(char *input);
t_arg	*ft_get_arg(char *input, int *i, t_arg *arg);
t_arg	*ft_get_quote_arg(char *input, int *i, t_arg *arg, char delim);
char	**ft_list_to_char(t_arg *list);
int		ft_set_token(t_arg *args);
int		ft_check_quotes(char input);

/* ************************************************************************ */
/*								ENV FUNCTIONS								*/
/* ************************************************************************ */

t_env	*ft_env_last(t_env *env);
t_env	*ft_env_to_list(char **env, int std[2]);
t_env	*ft_get_env_element(t_env *env, char *env_line);
void	ft_delone_env(t_env **env);
void	ft_env_add_back(t_env **env_start, t_env *new);
void	ft_cleanly_delone_env(t_env **env_start, t_env *target);
void	ft_deal_with_existing_env_var(t_env **env_list, t_env *to_add);
void	ft_manually_add_one_env(t_env *env_list, char *name, char *content);
char	**ft_env_to_char(t_env *env);
int		ft_env_size(t_env *env);
int		ft_is_valid_env_variable(char *str);
int		ft_print_env(t_env *env_list, char **arg);
void	ft_replace_env_content(t_env *env_elem, char *new_content);
void	ft_increment_shlvl(t_env *shlvl);
void	ft_update_shlvl(t_env *env);

/* ************************************************************************ */
/*								FREE FUNCTIONS								*/
/* ************************************************************************ */

t_mlc	*ft_malloc_list_add_back(t_mlc **mlc_list, t_mlc *new_mlc);
void	ft_free_env(t_env *env_start);
void	ft_free_double_array(char **str);
void	ft_free_mlc_and_quit(t_mlc *mlc_start, int exit_code);
void	ft_delone_mlc(t_mlc *mlc, void (*del)(void *));
void	*ft_magic_malloc(int funct, size_t size, void *addr);
void	ft_cleanly_delone_mlc(t_mlc **mlc_start, void *addr);

/* ************************************************************************ */
/*								BUILTIN FUNCTIONS							*/
/* ************************************************************************ */

/* unset */
t_env	*ft_find_env_elem(t_env *env_list, char *name);
char	*ft_get_pwd(int std[2]);
int		ft_print_pwd(int std[2]);
int		ft_unset(t_env **env_list, char **name);

/* cd */
int		ft_cd(t_env *env, char **path, int std[2]);

/* export */
int		ft_export(t_env **env_list, char **to_add);

/*  echo  */
t_arg	*ft_echo_skip_opt(t_arg *arg, int *n_opt);
int		ft_echo(t_arg *arg);
int		ft_echo_n_opt(t_arg *arg);

/* exit */
void	ft_write_exit(void);
int		ft_exit_manager(t_arg *arg, int std[2]);
void	ft_exit(unsigned char exit_code, int std[2]);

int		ft_builtin_parser(t_env **env, t_arg *arg, int std[2]);
int		ft_is_a_builtin(t_arg *arg);

/* ************************************************************************ */
/*                           REDIRECTION FUNCTIONS                          */
/* ************************************************************************ */

int		ft_set_redirections(t_arg *arg, t_arg *head);
int		*ft_redirection(t_arg *arg);
int		ft_redirection_in(t_arg *arg, int current_in);
int		ft_redirection_out(t_arg *arg, int current_out);
int		ft_get_redirections(t_arg *arg);

int		*ft_set_currents(void);

int		ft_fill_heredoc(int file, char *delim, int flag, t_env *env);
void	ft_get_hd_strings(char *line, char **pieces, char *flags, t_env *env);
char	*ft_final_hd_string(char *line, char **pieces, char *flags, t_env *env);
char	*ft_expand_heredoc(char *line, t_env *env);
int		ft_check_delim(t_arg *arg);
int		ft_heredoc(t_arg *arg, t_env *env, int std[2], char **heredoc_name);
int		ft_count_hd_expand(char *line, char *flags, t_env *env);
int		ft_manage_heredoc(t_arg *arg, t_env *env, int std[2], char **hd_name);
int		ft_redir_heredoc(t_arg *arg, t_env *env, int std[2], char **hd_name);

char	*ft_create_heredoc(void);
void	ft_close_heredoc(int std[2], int tmp_file);

/* ************************************************************************ */
/*                            EXECUTION FUNCTIONS                           */
/* ************************************************************************ */

t_arg	*ft_get_next_pipe(t_arg *arg);
void	ft_freetab(char **tab);
void	ft_final_path(char **paths);
char	**ft_get_path(char **env);
char	**ft_list_to_char_exec(t_arg *list);
char	*ft_get_cmd(char *arg, char **paths);
int		ft_count_pipes(t_arg *arg);
int		ft_try(t_arg *arg, t_env **env, int pipes, int fds[2]);
int		ft_child(t_arg *arg, t_env **env, int std[2]);
int		ft_executor(t_arg *arg, t_env **env, int std[2], int *currents);
int		ft_piped_child(t_arg *arg, t_env **env, int std[2]);

void	ft_close_child(int fds[2], int std[2], int currents[2]);
void	ft_close_parent(int std[2]);
int		ft_check_child_return(pid_t child_pid);
int		ft_check_pipes(t_arg *arg, t_env **env, int std[2]);

char	*ft_display_prompt(int std[2]);
int		*ft_save_std_fd(void);
int		ft_check_cmd(char *cmd);
int		ft_error(char *file);

/* ************************************************************************ */
/*                            SIGNALS FUNCTIONS                             */
/* ************************************************************************ */

void	ft_signal_catching(void);
void	ft_signal_catching_heredoc(void);
void	ft_my_magic_handler_heredoc(int signum);
void	ft_my_magic_handler_interactive(int signum);
void	ft_my_magic_handler_not_interactive(int signum);
void	ft_ignore_signal(void);
void	ft_ignore_handler(int signum);
void	ft_set_term_behaviour(void);
int		ft_is_interactive(void);
void	ft_ignore_signal_heredoc(void);

/* ************************************************************************ */
/*                            ERROR MANAGEMENT                              */
/* ************************************************************************ */

void	ft_clear_and_quit(t_arg *arg, t_arg *head);
int		ft_check_double_redir(t_arg *arg);
int		ft_check_single_redir(t_arg *arg);
int		ft_check_wrong_arg(t_arg *arg);
int		ft_check_first_arg(t_arg *arg);
int		ft_check_double_pipe(t_arg *arg, t_arg *head);

#endif
