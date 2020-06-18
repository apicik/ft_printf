# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ediego <ediego@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/19 19:01:02 by ediego            #+#    #+#              #
#    Updated: 2019/12/21 15:38:53 by ediego           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = gcc
FLAGS = -g -Wall -Werror -Wextra
INCLUDES = -I$(HEADERS_DIRECTORY)


# HEADERS

HEADERS_LIST = \
	ft_printf.h
HEADERS_DIRECTORY = ./includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

# SOURCES

SOURCES_DIRECTORY = ./sources/
SOURCES_LIST = \
	atoi_ll.c \
	ft_strcat.c \
	out_f_functions.c \
	fill_list.c \
	ft_strlen.c \
	out_o.c \
	ft_bzero.c \
	ft_strnew.c \
	out_scp.c \
	ft_memalloc.c \
	new_fill_lst_out.c \
	out_scp_functions.c \
	ft_printf.c \
	out_di.c \
	out_u.c \
	ft_putchar.c \
	out_di_functions.c \
	out_f.c \
	ft_putstr.c \
	out_x16.c

SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

# OBJECTS

OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

# COLORS

GREEN = \033[1;36m
RED = \033[1;35m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS_DIRECTORY) $(OBJECTS)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)
	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(GREEN)$(OBJECTS_DIRECTORY) was created$(RESET)"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

clean:
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all























# CC = gcc

# NAME = libftprintf.a

# FLAGS = -Wall -Wextra -Werror

# DIR_S = srcs

# DIR_O = temporary

# HEADER = includes

# SOURCES = atoi_ll.c \
# 			ft_strcat.c \
# 			out_f_functions.c \
# 			fill_list.c \
# 			ft_strjoin.c \
# 			out_list.c \
# 			ft_atoi.c \
# 			ft_strlen.c \
# 			out_o.c \
# 			ft_bzero.c \
# 			ft_strnew.c \
# 			out_scp.c \
# 			ft_memalloc.c \
# 			new_fill_lst.c \
# 			out_scp_functions.c \
# 			ft_printf.c \
# 			out_di.c \
# 			out_u.c \
# 			ft_putchar.c \
# 			out_di_functions.c \
# 			out_x16.c

# SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

# OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

# all: $(NAME)

# $(NAME): $(OBJS) $(DIR_O)
# 	@ar rc $(NAME) $(OBJS)
# 	@ranlib $(NAME)

# $(DIR_O)/%.o: $(DIR_S)/%.c
# 	@mkdir -p temporary
# 	@$(CC) $(FLAGS) -c $(HEADER) $< -o $@

# clean:
# 	@rm -f $(OBJS)
# 	@rm -rf $(DIR_O)

# fclean: clean
# 	@rm -f $(NAME)

# re: fclean all