# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aweaver <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/23 10:40:46 by aweaver           #+#    #+#              #
#    Updated: 2022/05/09 11:30:46 by aweaver          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

SRCS_PATH 	=	./sources/
LIBFT_PATH	=	./libft/
GNL_PATH	=	./get_next_line/
PRINTF_PATH	=	./ft_printf/

SRCS		=	$(addprefix $(LIBFT_PATH),\
				ft_abs.c			\
				ft_isalpha.c		\
				ft_isdigit.c		\
				ft_isalnum.c		\
				ft_isascii.c		\
				ft_isprint.c		\
				ft_is_base_ok.c		\
				ft_is_int.c			\
				ft_array_size.c		\
				ft_strlen_int.c		\
				ft_strlen_nl.c		\
				ft_strlen.c			\
				ft_memset.c			\
				ft_bzero.c			\
				ft_memcpy.c			\
				ft_memmove.c		\
				ft_strcpy.c			\
				ft_strcat.c			\
				ft_strlcpy.c		\
				ft_strlcat.c		\
				ft_toupper.c		\
				ft_tolower.c		\
				ft_strchr.c			\
				ft_strrchr.c		\
				ft_strcmp.c			\
				ft_strncmp.c		\
				ft_memchr.c			\
				ft_memcmp.c			\
				ft_strnstr.c		\
				ft_atoi.c			\
				ft_realloc.c		\
				ft_calloc.c			\
				ft_strdup.c			\
				ft_strndup.c		\
				ft_substr.c			\
				ft_strjoin.c		\
				ft_strjoin_free.c	\
				ft_strtrim.c		\
				ft_split.c			\
				ft_itoa.c			\
				ft_utoa.c			\
				ft_ultoa.c			\
				ft_itoa_base.c		\
				ft_utoa_base.c		\
				ft_ultoa_base.c		\
				ft_strmapi.c		\
				ft_striteri.c		\
				ft_putchar.c		\
				ft_putchar_colour.c	\
				ft_putstr.c			\
				ft_putstr_colour.c	\
				ft_putendl.c		\
				ft_putnbr.c			\
				ft_putchar_fd.c		\
				ft_putstr_fd.c		\
				ft_putendl_fd.c		\
				ft_putnbr_fd.c		\
				ft_lstnew.c			\
				ft_lstadd_front.c	\
				ft_lstsize.c		\
				ft_lstlast.c		\
				ft_lstadd_back.c	\
				ft_lstdelone.c		\
				ft_lstclear.c		\
				ft_lstiter.c		\
				ft_lstmap.c			\
				ft_count_digits.c)\
				$(addprefix $(GNL_PATH),\
				get_next_line.c)		\
				$(addprefix $(PRINTF_PATH),\
				ft_lstreset.c				\
				ft_printf_c.c				\
				ft_printf_s.c				\
				ft_printf_p.c 				\
				ft_printf_u.c				\
				ft_printf_x.c				\
				ft_printf_o.c				\
				ft_printf_id.c				\
				ft_flag_hyphen.c			\
				ft_printf_check_flags.c		\
				ft_printf_parse.c			\
				ft_printf.c)

OBJS		=	$(addprefix $(OBJS_PATH),$(SRCS:.c=.o))

OBJS_PATH	=	./objects/

CC			=	gcc

INC			=	-I ./includes

DEP			=	$(OBJS:.o=.d)

CFLAGS		=	-MMD -Wall -Wextra -Werror -g3

all:		$(NAME)

$(NAME):	$(OBJS)
			ar -rcs $@ $^

$(OBJS_PATH)%.o:		$(SRCS_PATH)%.c
			@mkdir -p $(OBJS_PATH)
			@mkdir -p $(OBJS_PATH)$(LIBFT_PATH)
			@mkdir -p $(OBJS_PATH)$(GNL_PATH)
			@mkdir -p $(OBJS_PATH)$(PRINTF_PATH)
			$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:	
			rm -rf $(OBJS_PATH)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

-include $(DEP)

.PHONY:		all re clean fclean
