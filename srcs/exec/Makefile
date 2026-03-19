# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/22 14:39:19 by mvignes           #+#    #+#              #
#    Updated: 2026/03/18 05:35:30 by mvignes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= env
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

MAKEFLAGS	+= --no-print-directory

SRCS	= ../libft/ft_isalpha.c\
		../libft/ft_isdigit.c\
		../libft/ft_isalnum.c\
		../libft/ft_isascii.c\
		../libft/ft_isprint.c\
		../libft/ft_strlen.c\
		../libft/ft_memset.c\
		../libft/ft_bzero.c\
		../libft/ft_memcpy.c\
		../libft/ft_memmove.c\
		../libft/ft_strlcpy.c\
		../libft/ft_strlcat.c\
		../libft/ft_toupper.c\
		../libft/ft_tolower.c\
		../libft/ft_strchr.c\
		../libft/ft_strrchr.c\
		../libft/ft_strncmp.c\
		../libft/ft_memchr.c\
		../libft/ft_memcmp.c\
		../libft/ft_strnstr.c\
		../libft/ft_atoi.c\
		../libft/ft_atol.c\
		../libft/ft_atoi_base.c\
		../libft/ft_calloc.c\
		../libft/ft_strdup.c\
		../libft/ft_free_tab.c\
		../libft/ft_substr.c\
		../libft/ft_strjoin.c\
		../libft/ft_strtrim.c\
		../libft/ft_split.c\
		../libft/ft_itoa.c\
		../libft/ft_strmapi.c\
		../libft/ft_striteri.c\
		../libft/ft_putchar_fd.c\
		../libft/ft_putstr_fd.c\
		../libft/ft_putendl_fd.c\
		../libft/ft_putnbr_fd.c\
		../libft/ft_lstnew.c\
		../libft/ft_lstadd_front.c\
		../libft/ft_lstsize.c\
		../libft/ft_lstlast.c\
		../libft/ft_lstadd_back.c\
		../libft/ft_lstdelone.c\
		../libft/ft_lstclear.c\
		../libft/ft_lstiter.c\
		../libft/ft_lstmap.c\
		../libft/ft_print_char.c\
		../libft/ft_printf.c\
		../libft/ft_print_int.c\
		../libft/ft_size.c\
		../libft/get_next_line.c\
		../libft/get_next_line_utils.c\
		\
		ttest.c\
		../utils/lstenv.c\
		../utils/other_split.c\
		../utils/print_struc.c\
		

OBJS		= $(SRCS:.c=.o)

%.o: %.c ../../includes/env.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) ../../includes/env.h
	ar rcs $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus