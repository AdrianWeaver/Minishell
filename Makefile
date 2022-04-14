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

SRCS 			=	main.c	\
					$(addprefix $(SRCS_PARSING),	\
						ms_parser.c	\
					 )\
					$(addprefix $(SRCS_ERRORS),		\
						ms_errors.c	\
					 )\
					$(addprefix $(SRCS_UTILS),		\
						ms_args_lst_utils.c	\
						ms_mlc_lst_utils.c)

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
					@mkdir -p $(OBJS_PATH)
					@mkdir -p $(OBJS_PATH)$(SRCS_PARSING)
					@mkdir -p $(OBJS_PATH)$(SRCS_EXEC)
					@mkdir -p $(OBJS_PATH)$(SRCS_ERRORS)
					@mkdir -p $(OBJS_PATH)$(SRCS_BUILTINS)
					@mkdir -p $(OBJS_PATH)$(SRCS_CMDS)
					@mkdir -p $(OBJS_PATH)$(SRCS_UTILS)
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
