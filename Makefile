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
SRCS_EXEC		=	./exec/
SRCS_ERRORS		=	./errors/
SRCS_BUILTINS	=	./builtins/
SRCS_ENV		=	./env/
SRCS_UTILS		=	./utils/
SRCS_REDIRECT	=	./redirections/


#############################################################################
#																			#
#									FILES									#
#																			#
#############################################################################

SRCS 			=	mitch_main_test.c	\
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
						ms_redirection.c \
						ms_prompt.c \
						ms_list_to_char.c\
					)\
					$(addprefix $(SRCS_ENV), \
						ms_env_to_list.c \
						ms_env_to_char.c \
						ms_free_env.c \
						ms_print_env.c	\
						ms_env_utils.c	\
					)\
					$(addprefix $(SRCS_BUILTINS),		\
						ms_export.c	\
						ms_unset.c	\
						ms_pwd.c	\
						ms_cd.c		\
						ms_builtin_parser.c \
						ms_echo.c \
					)\
					$(addprefix $(SRCS_REDIRECT),		\
						ms_heredoc.c \
						ms_expand_heredoc.c \
					)\
					$(addprefix $(SRCS_EXEC),	\
						ms_exec.c \
						ms_exec_tools.c\
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

vtest:				$(NAME)
					valgrind --leak-check=full --track-fds=yes\
					--show-leak-kinds=all\
					--suppressions=.ignore_readline ./$(NAME)

teststaf:			$(LIBFT)
					@clear
					$(CC) -Wall -Wextra -g3 \
					./sources/builtins/ms_unset.c	\
					./sources/builtins/ms_export.c	\
					./sources/builtins/ms_pwd.c	\
					./sources/builtins/ms_cd.c	\
					./sources/env/ms_env_to_list.c  \
					./sources/utils/main_staf.c \
					./sources/env/ms_free_env.c \
					./sources/env/ms_env_utils.c	\
					./sources/env/ms_print_env.c \
					./sources/utils/ms_magic_malloc.c \
					./sources/utils/ms_magic_malloc_utils.c \
					-I ./includes -I ./libft/includes libft/libft.a 
					valgrind --leak-check=full --show-leak-kinds=all ./a.out

testexport:			$(LIBFT)
					@clear
					$(CC) -Wall -Wextra -g3 \
					./sources/builtins/ms_unset.c	\
					./sources/builtins/ms_export.c	\
					./sources/builtins/ms_pwd.c	\
					./sources/builtins/ms_cd.c	\
					./sources/env/ms_env_to_list.c  \
					./sources/builtins/main_test_staf.c \
					./sources/env/ms_free_env.c \
					./sources/env/ms_env_utils.c	\
					./sources/env/ms_print_env.c \
					./sources/utils/ms_magic_malloc.c \
					./sources/utils/ms_magic_malloc_utils.c \
					-I ./includes -I ./libft/includes libft/libft.a 
					valgrind --leak-check=full --show-leak-kinds=all ./a.out

-include $(DEPS)
.PHONY:				all clean fclean re test
