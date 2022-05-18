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
SRCS_UTILS		=	./utils/


#############################################################################
#																			#
#									FILES									#
#																			#
#############################################################################

SRCS 			=	mitch_main_test.c	\
					$(addprefix $(SRCS_PARSING),	\
						ms_parser.c	\
						ms_parse_redirections.c \
						ms_parse_dquote.c \
						ms_parse_squote.c \
						ms_expansion.c \
						ms_cat_expansion.c \
					 )\
					$(addprefix $(SRCS_ERRORS),		\
						ms_errors.c	\
					 )\
					$(addprefix $(SRCS_UTILS),		\
						ms_args_lst_utils.c	\
						ms_mlc_lst_utils.c \
						ms_env_to_list.c \
						ms_free_env.c \
					)\

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

teststaf:			$(LIBFT)
					@clear
					$(CC) -Wall -Wextra -g3 \
					./sources/builtins/ms_unset.c	\
					./sources/builtins/ms_export.c	\
					./sources/env/ms_env_to_list.c  \
					./sources/builtins/main_test_staf.c \
					./sources/env/ms_free_env.c \
					./sources/env/ms_env_utils.c	\
					./sources/env/ms_print_env.c \
					-I ./includes -I ./libft/includes libft/libft.a
					valgrind --leak-check=full ./a.out

-include $(DEPS)
.PHONY:				all clean fclean re test
