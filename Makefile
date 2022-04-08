NAME			=		minishell

#############################################################################
#																			#
#								COMPILER									#
#																			#
#############################################################################

CC				=	gcc
CFLAGS			=	-MMD -Wall -Wextra -Werror -g3
INC				=	-I ./includes\
					-I ./libft/includes
SILENT			=	--no-print-directory

#############################################################################
#																			#
#									PATHS									#
#																			#
#############################################################################

SRCS_PATH		=	./sources/
OBJS_PATH		=	./objects/
LIBFT_PATH		=	./libft/


#############################################################################
#																			#
#									FILES									#
#																			#
#############################################################################

SRCS 			=	main.c

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
					$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBFT)
					@echo "Linking files and libft"

$(OBJS_PATH)%.o:	$(SRCS_PATH)%.c
					@mkdir -p $(OBJS_PATH)
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
