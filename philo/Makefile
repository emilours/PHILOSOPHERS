# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eminatch <eminatch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/02 16:56:42 by eminatch          #+#    #+#              #
#    Updated: 2023/03/18 17:56:54 by eminatch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_PATH	= src/
OBJ_PATH	= obj/

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -MMD -MP -pthread
SRC = 	main.c \
		conditions.c \
		conditions_utils.c \
		errors.c \
		routine.c \
		routine_utils.c \
		table.c \
	
SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
DEPS	= $(addprefix ${OBJ_PATH}, ${SRC:.c=.d})
INCS	= -I ./includes/

RM = rm -rf

all: $(NAME)

$(NAME) : $(OBJS)
	@$(MAKE) --no-print-directory header
	@echo "Compiling PHILOSOPHERS objects ⚡"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\nCompiled PHILOSOPHERS 🍀"	

$(OBJ_PATH)%.o: $(SRC_PATH)%.c 
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) ${INCS} -o $@ -c $<

clean:
	@echo "\nCleaning PHILOSOPHERS objects 🧹"
	@${RM} $(OBJ_PATH) ${DEPS}
	@echo "\nClean PHILOSOPHERS ✨"

fclean: clean
	@${RM} -f $(NAME)

debug : fclean
	@make --no-print-directory CFLAGS+="-g3 -pthread -fsanitize=thread"

re: fclean all

define HEADER
░█▀█░█░█░▀█▀░█░░░█▀█░░░░░█░░░█▀▀░█▄█░▀█▀░█▀█░█▀█░▀█▀░█▀▀░█░█
░█▀▀░█▀█░░█░░█░░░█░█░░░▄▀░░░░█▀▀░█░█░░█░░█░█░█▀█░░█░░█░░░█▀█
░▀░░░▀░▀░▀▀▀░▀▀▀░▀▀▀░░░▀░░░░░▀▀▀░▀░▀░▀▀▀░▀░▀░▀░▀░░▀░░▀▀▀░▀░▀
endef
export HEADER

header :
	clear
	@echo "$$HEADER"

-include ${DEPS}

.SECONDARY : ${OBJ} ${OBJ_PATH} ${OBJS}

.PHONY : all clean fclean re
