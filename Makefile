NAME	= philosophers

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror

INC	= -I.

OBJ_DIR	= obj

OBJS	= $(SRCS:%.c=$(OBJ_DIR)/%.o)

RM	= rm -rf

SRCS	=	fork_actions.c	\
		initialization.c	\
		main.c	\
		message_utils.c	\
		monitoring.c	\
		philo_actions.c	\
		time_utils.c

all:	$(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
