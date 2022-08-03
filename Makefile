NAME			=		minishell

#############################################################################
#																			#
#								COMPILER									#
#																			#
#############################################################################

CC				=	gcc

CFLAGS			=	-MMD -Wall -Wextra -Werror -g3

INC				=	-I ./includes/\
					-I ./libft/includes/

SILENT			=	--no-print-directory

#############################################################################
#																			#
#									PATHS									#
#																			#
#############################################################################

SRCS_PATH		=	./sources/
OBJS_PATH		=	./objects/
LIBFT_PATH		=	./libft/
SRCS_PARSING	=	./parsing/
SRCS_ERRORS		=	./errors/
SRCS_BUILTINS	=	./builtins/
SRCS_ENV		=	./env/
SRCS_EXEC		=	./exec/
SRCS_UTILS		=	./utils/
SRCS_REDIRECT	=	./redirections/
SRCS_SIGNALS	=	./signals/
SRCS_TERMINAL	=	./terminal/


#############################################################################
#																			#
#									FILES									#
#																			#
#############################################################################

SRCS				=	main.c\
					$(addprefix $(SRCS_PARSING),	\
						ms_parser.c	\
						ms_parse_check.c \
						ms_parse_redirections.c \
						ms_parse_quote.c \
						ms_expansion.c \
						ms_cat_expansion.c \
					 )\
					$(addprefix $(SRCS_ERRORS),		\
						ms_syntax_errors.c	\
					 )\
					$(addprefix $(SRCS_UTILS),		\
						ms_args_lst_utils.c	\
						ms_magic_malloc.c \
						ms_magic_malloc_utils.c \
						ms_mlc_lst_utils.c		\
						ms_prompt.c \
						ms_list_to_char.c \
						ms_list_to_char_exec.c \
					)\
					$(addprefix $(SRCS_ENV), \
						ms_env_to_list.c \
						ms_env_to_char.c \
						ms_free_env.c \
						ms_print_env.c	\
						ms_env_utils.c	\
						ms_shlvl.c	\
					)\
					$(addprefix $(SRCS_BUILTINS),		\
						ms_export.c	\
						ms_unset.c	\
						ms_pwd.c	\
						ms_cd.c		\
						ms_builtin_parser.c \
						ms_echo.c \
						ms_exit.c	\
					)\
					$(addprefix $(SRCS_REDIRECT),		\
						ms_heredoc.c \
						ms_expand_heredoc.c \
						ms_heredoc_management.c \
						ms_redirection.c \
						ms_check_redirections.c \
						ms_check_child_return.c	\
					)\
					$(addprefix $(SRCS_EXEC),	\
						ms_exec.c \
						ms_exec_tools.c \
						ms_check_cmd.c \
						ms_std_fd_management.c \
					)\
					$(addprefix $(SRCS_SIGNALS),	\
						ms_signals.c \
						ms_signals_heredoc.c \
					)\
					$(addprefix $(SRCS_TERMINAL),	\
						ms_terminal.c\
					)

OBJS			=	$(addprefix $(OBJS_PATH), $(SRCS:.c=.o))
DEPS			=	$(OBJS:.o=.d)
LIBFT			=	$(addprefix $(LIBFT_PATH), libft.a)

#############################################################################
#																			#
#									RULES									#
#																			#
#############################################################################

all:				$(NAME)

$(NAME):			$(OBJS) $(LIBFT)
					$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBFT) -lreadline
					@echo "Linking files and libft"

$(OBJS_PATH)%.o:	$(SRCS_PATH)%.c
					@mkdir -p $(dir $@)
					$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(LIBFT):
					@make -C $(LIBFT_PATH) $(SILENT)

clean:
					@rm -rf $(OBJS_PATH)
					@echo "Objects cleaned!"

fclean:				clean
					@rm -f $(NAME)

re:					fclean
					@make all $(SILENT)

test:				$(NAME)
					./$(NAME)

-include $(DEPS)
.PHONY:				all clean fclean re test
