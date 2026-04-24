#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/22 14:39:19 by mvignes           #+#    #+#              #
#    Updated: 2026/04/10 16:05:55 by mmusquer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#================================================#
#                 _       _     _           	||
#                (_)     | |   | |          	||
#__   ____ _ _ __ _  __ _| |__ | | ___  ___ 	||
#\ \ / / _` | '__| |/ _` | '_ \| |/ _ \/ __|	||
# \ V / (_| | |  | | (_| | |_) | |  __/\__ \	||
#  \_/ \__,_|_|  |_|\__,_|_.__/|_|\___||___/	||
#================================================#

NAME		= minishell
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g3
RM			= rm -f

MAKEFLAGS	+= --no-print-directory

RED			= \033[0;31m
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
BLUE		= \033[0;34m
MAGENTA		= \033[0;35m
CYAN		= \033[0;36m
GRAS		= \033[1m
RESET		= \033[0m

SRCS_DIR	= srcs
OBJS_DIR	= .objects

SRCS	= srcs/libft/ft_isalpha.c\
		srcs/libft/ft_isdigit.c\
		srcs/libft/ft_isalnum.c\
		srcs/libft/ft_isascii.c\
		srcs/libft/ft_isprint.c\
		srcs/libft/ft_is_space.c\
		srcs/libft/ft_strlen.c\
		srcs/libft/ft_memset.c\
		srcs/libft/ft_bzero.c\
		srcs/libft/ft_memcpy.c\
		srcs/libft/ft_memmove.c\
		srcs/libft/ft_strlcpy.c\
		srcs/libft/ft_strlcat.c\
		srcs/libft/ft_toupper.c\
		srcs/libft/ft_tolower.c\
		srcs/libft/ft_strchr.c\
		srcs/libft/ft_strrchr.c\
		srcs/libft/ft_strncmp.c\
		srcs/libft/ft_memchr.c\
		srcs/libft/ft_memcmp.c\
		srcs/libft/ft_strnstr.c\
		srcs/libft/ft_atoi.c\
		srcs/libft/ft_atol.c\
		srcs/libft/ft_atoi_base.c\
		srcs/libft/ft_calloc.c\
		srcs/libft/ft_strdup.c\
		srcs/libft/ft_free_tab.c\
		srcs/libft/ft_substr.c\
		srcs/libft/ft_strjoin.c\
		srcs/libft/ft_strtrim.c\
		srcs/libft/ft_split.c\
		srcs/libft/ft_itoa.c\
		srcs/libft/ft_strmapi.c\
		srcs/libft/ft_striteri.c\
		srcs/libft/ft_putchar_fd.c\
		srcs/libft/ft_putstr_fd.c\
		srcs/libft/ft_putendl_fd.c\
		srcs/libft/ft_putnbr_fd.c\
		srcs/libft/ft_lstnew.c\
		srcs/libft/ft_lstadd_front.c\
		srcs/libft/ft_lstsize.c\
		srcs/libft/ft_lstlast.c\
		srcs/libft/ft_lstadd_back.c\
		srcs/libft/ft_lstdelone.c\
		srcs/libft/ft_lstclear.c\
		srcs/libft/ft_lst_create_and_addback.c\
		srcs/libft/ft_lst_sort.c\
		srcs/libft/ft_lstiter.c\
		srcs/libft/ft_lstmap.c\
		srcs/libft/ft_print_char.c\
		srcs/libft/ft_printf.c\
		srcs/libft/ft_print_int.c\
		srcs/libft/ft_size.c\
		srcs/libft/get_next_line.c\
		srcs/libft/get_next_line_utils.c\
		\
		srcs/main.c\
		\
		srcs/utils/lstenv.c\
		srcs/utils/other_split.c\
		srcs/utils/print_struc.c\
		\
		srcs/buildin/cd.c\
		srcs/buildin/echo.c\
		srcs/buildin/env.c\
		srcs/buildin/exit.c\
		srcs/buildin/export.c\
		srcs/buildin/orchestrator.c\
		srcs/buildin/pwd.c\
		srcs/buildin/unset.c\
		srcs/buildin/utils.c\
		\
		srcs/execution/env.c\
		srcs/execution/env_utils.c\
		srcs/execution/exec_cmd.c\
		srcs/execution/exec_line.c\
		srcs/execution/path.c\
		srcs/execution/pipe.c\
		srcs/execution/and.c\
		srcs/execution/or.c\
		srcs/execution/redir.c\
		srcs/execution/redir_heredoc.c\
		srcs/execution/redir_heredoc_utils.c\
		srcs/execution/wildcard.c\
		srcs/execution/wildcard_utils.c\
		srcs/execution/utils.c\
		\
		srcs/lexer/lexer.c\
		srcs/lexer/lexer_utils.c\
		srcs/lexer/lexer_cut.c\
		srcs/lexer/lexer_checker_main.c\
		srcs/lexer/lexer_checker_sep_redir.c\
		srcs/lexer/lexer_checker_bracket.c\
		\
		srcs/parser/parser.c\
		srcs/parser/parser_cut.c\
		srcs/parser/parser_utils.c\
		srcs/parser/parser_free.c\
		\
		srcs/expand/expand.c\
		srcs/expand/expand_dollards.c\
		srcs/expand/expand_quotes.c\
		srcs/expand/expand_concatenate.c\
		\
		srcs/signal/signal.c\

SRCS_BONUS	= \

OBJS		= $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))
OBJS_BONUS	= $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS_BONUS))


INCLUDES	= -I ./includes


#================================#
#______           _           	||
#| ___ \         | |          	||
#| |_/ /___  __ _| | ___  ___ 	||
#|    // _ \/ _` | |/ _ \/ __|	||
#| |\ \  __/ (_| | |  __/\__ \	||
#\_| \_\___|\__, |_|\___||___/	||
#            __/ |            	||
#           |___/             	||
#================================#


TOTAL = $(words $(OBJS), $(OBJS_BONUS))

all:
	@$(MAKE) -j12 $(NAME)

$(NAME): $(OBJS)
	@printf "\n"
	@if $(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME); then \
		$(MAKE) name_ascii; \
		$(MAKE) user42; \
		printf "$(GREEN)$(GRAS)👌 Compilation terminée !$(RESET)\n\n"; \
	else \
		printf "\n$(RED)$(GRAS)Erreur de compilation !$(RESET)\n\n"; \
		$(MAKE) error_ascii; \
		exit 1; \
	fi

clean:
	@$(RM) -r $(OBJS_DIR)
	@$(RM) vgcore.*
	@printf "$(RED)Dossier .objects supprimé$(RESET)\n"

fclean: clean
	@$(RM) $(NAME) .last_colors
	@printf "$(RED)$(NAME) supprimé$(RESET)\n"

re: fclean all

bonus:
	@$(MAKE) -j12 $(NAME) $(OBJS_BONUS)

bash:
	bash --posix

#============================================================#
# _____                       _ _       _   _             	||
#/  __ \                     (_) |     | | (_)            	||
#| /  \/ ___  _ __ ___  _ __  _| | __ _| |_ _  ___  _ __  	||
#| |    / _ \| '_ ` _ \| '_ \| | |/ _` | __| |/ _ \| '_ \ 	||
#| \__/\ (_) | | | | | | |_) | | | (_| | |_| | (_) | | | |	||
# \____/\___/|_| |_| |_| .__/|_|_|\__,_|\__|_|\___/|_| |_|	||
#                      | |                                	||
#                      |_|                                	||
#============================================================#

INDEX = 0

define compile_msg
	$(eval INDEX=$(shell echo $$(($(INDEX)+1))))
	@printf "\r$(BLUE)$(GRAS)[$(INDEX)/$(TOTAL)]$(RESET) $(GRAS)Compilation: %-30s$(RESET)" "$(notdir $<)"
endef

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(eval INDEX=$(shell echo $$(($(INDEX)+1))))
	@printf "\r$(BLUE)$(GRAS)[$(INDEX)/$(TOTAL)]$(RESET) $(GRAS)Compilation: %-30s$(RESET)" "$(notdir $<)"
	@if ! $(CC) $(CFLAGS) -c $< -o $@; then \
		printf "\n$(RED)$(GRAS)Erreur dans: $(notdir $<)$(RESET)\n"; \
		$(CC) $(CFLAGS) -c $< -o $@ 2>&1 | head -10; \
		$(MAKE) error_ascii; \
		exit 1; \
	fi

#============================#
# _____       _   _ _     	||
#|  _  |     | | (_) |    	||
#| | | |_   _| |_ _| |___ 	||
#| | | | | | | __| | / __|	||
#\ \_/ / |_| | |_| | \__ \	||
# \___/ \__,_|\__|_|_|___/	||
#============================#

# Statistiques du projet
stats:
	@printf "$(CYAN)Statistiques du projet:$(RESET)\n"
	@printf "	Fichiers .c	: %d\n" $(TOTAL)
	@printf "	Lignes code	: %d\n" $$(cat $(SRCS) $(SRCS_BONUS) | wc -l)
	@printf "	Headers		: %d\n" $$(find includes -name "*.h" | wc -l)

#===========================================#
#  ___       _      ___          _ _ 	   ||
# / _ \     | |    / _ \        (_|_)	   ||
#/ /_\ \_ __| |_  / /_\ \___ ___ _ _ 	   ||
#|  _  | '__| __| |  _  / __/ __| | |	   ||
#| | | | |  | |_  | | | \__ \__ \ | |	   ||
#\_| |_/_|   \__| \_| |_/___/___/_|_|	   ||
#===========================================#

COLOR_FILE	= .last_colors
COLOR_MAX	:= $(call get_random_color)$(GRAS)
COLOR_MAT	:= $(call get_random_color)$(GRAS)


# Fonction pour obtenir une couleur différente de la précédente
define get_random_color
$(shell \
	LAST=$$(cat $(COLOR_FILE) 2>/dev/null | head -1 || echo 0); \
	NEW=$$(od -An -N1 -tu1 /dev/urandom | tr -d ' '); \
	NEW=$$((NEW % 6 + 1)); \
	COUNT=0; \
	while [ "$$NEW" = "$$LAST" ] && [ $$COUNT -lt 10 ]; do \
		NEW=$$(od -An -N1 -tu1 /dev/urandom | tr -d ' '); \
		NEW=$$((NEW % 6 + 1)); \
		COUNT=$$((COUNT + 1)); \
	done; \
	echo $$NEW > $(COLOR_FILE); \
	printf "\033[0;3%dm" $$NEW \
)
endef

name_ascii:
	@printf "\n"
	@printf "$(call get_random_color)$(GRAS)"
	@printf "                  ,,                ,,           ,,                 ,,    ,,  \n"
	@printf "'7MMM.     ,MMF'  db                db         '7MM               '7MM  '7MM  \n"
	@printf "  MMMb    dPMM                                   MM                 MM    MM  \n"
	@printf "  M YM   ,M MM  '7MM  '7MMpMMMb.  '7MM  ,pP'Ybd  MMpMMMb.  .gP'Ya   MM    MM  \n"
	@printf "  M  Mb  M' MM    MM    MM    MM    MM  8I   ''  MM    MM ,M'   Yb  MM    MM  \n"
	@printf "  M  YM.P'  MM    MM    MM    MM    MM  'YMMMa.  MM    MM 8M''''''  MM    MM  \n"
	@printf "  M  'YM'   MM    MM    MM    MM    MM  L.   I8  MM    MM YM.    ,  MM    MM  \n"
	@printf ".JML. ''  .JMML..JMML..JMML  JMML..JMML.M9mmmP'.JMML  JMML.'Mbmmd'.JMML..JMML.\n"
	@printf "$(RESET)\n"


user42:
#	@printf "$(call get_random_color)$(GRAS)"
	@printf "                                                                                                             AW                                                                                  \n"
	@printf "$(COLOR_MAX)'7MMM.     ,MMF''7MMM.     ,MMF''7MMF'   '7MF'.M***bgd   .g8**8q. '7MMF'   '7MF''7MM***YMM  '7MM***Mq.$(RESET)      ,M'$(COLOR_MAT)'7MMM.     ,MMF''7MMF'   '7MF''7MMF' .g8***bgd '7MN.   '7MF''7MM***YMM   .M***bgd$(RESET) \n"
	@printf "  $(COLOR_MAX)MMMb    dPMM    MMMb    dPMM    MM       M ,MI    *Y .dP'    'YM. MM       M    MM    '7    MM   'MM.$(RESET)     MV   $(COLOR_MAT)MMMb    dPMM    'MA     ,V    MM .dP'     'M   MMN.    M    MM    '7  ,MI    *Y$(RESET) \n"
	@printf "  $(COLOR_MAX)M YM   ,M MM    M YM   ,M MM    MM       M 'MMb.     dM'      'MM MM       M    MM   d      MM   ,M9$(RESET)     AW    $(COLOR_MAT)M YM   ,M MM     VM:   ,V     MM dM'       '   M YMb   M    MM   d    'MMb.$(RESET)     \n"
	@printf "  $(COLOR_MAX)M  Mb  M' MM    M  Mb  M' MM    MM       M   'YMMNq. MM        MM MM       M    MMmmMM      MMmmdM9$(RESET)     ,M'    $(COLOR_MAT)M  Mb  M' MM      MM.  M'     MM MM            M  'MN. M    MMmmMM      'YMMNq.$(RESET) \n"
	@printf "  $(COLOR_MAX)M  YM.P'  MM    M  YM.P'  MM    MM       M .     'MM MM.      ,MP MM       M    MM   Y  ,   MM  YM.$(RESET)     MV     $(COLOR_MAT)M  YM.P'  MM      'MM A'      MM MM.    '7MMF' M   'MM.M    MM   Y  , .     'MM$(RESET) \n"
	@printf "  $(COLOR_MAX)M  'YM'   MM    M  'YM'   MM    YM.     ,M Mb     dM 'Mb.    ,dP' YM.     ,M    MM     ,M   MM   'Mb.$(RESET)  AW      $(COLOR_MAT)M  'YM'   MM       :MM;       MM 'Mb.     MM   M     YMM    MM     ,M Mb     dM$(RESET) \n"
	@printf "$(COLOR_MAX).JML. ''  .JMML..JML. ''  .JMML.   'bmmmmd*' P*Ybmmd*    '*bmmd*'    'bmmmmd*'  .JMMmmmmMMM .JMML. .JMM.$(RESET),M'    $(COLOR_MAT).JML. ''  .JMML.      VF      .JMML. '*bmmmdPY .JML.    YM  .JMMmmmmMMM P*Ybmmd*$(RESET)  \n"
	@printf "                                                             $(COLOR_MAX)MMb$(RESET)                                        MV                                                                                       \n"
	@printf "                                                              $(COLOR_MAX)'bood'$(RESET)                                   AW                                                                                        \n"
	@printf "$(RESET)\n"

error_ascii:
	@printf "\n"
	@printf "$(RED)$(GRAS)"
	@printf "  _____ ____  ____   ___  ____                                \n"
	@printf " | ____|  _ \|  _ \ / _ \|  _ \                               \n"
	@printf " |  _| | |_) | |_) | | | | |_) |                              \n"
	@printf " | |___|  _ <|  _ <| |_| |  _ <                               \n"
	@printf " |_____|_|_\_\_| \_\\____/|_| \_\      _  _____ ___ ___  _   _ \n"
	@printf "  / ___/ _ \|  \/  |  _ \_ _| |      / \|_   _|_ _/ _ \| \ | |\n"
	@printf " | |  | | | | |\/| | |_) | || |     / _ \ | |  | | | | |  \| |\n"
	@printf " | |__| |_| | |  | |  __/| || |___ / ___ \| |  | | |_| | |\  |\n"
	@printf "  \____\___/|_|  |_|_|  |___|_____/_/   \_\_| |___\___/|_| \_|\n"
	@printf "$(RESET)\n"


#====================================#
#  ____  _   _  ___  _   ___   __	||
# |  _ \| | | |/ _ \| \ | \ \ / /	||
# | |_) | |_| | | | |  \| |\ V / 	||
# |  __/|  _  | |_| | |\  | | |  	||
# |_|   |_| |_|\___/|_| \_| |_|  	||
#====================================#

.PHONY: all bonus clean fclean re norm lines name_ascii user42
