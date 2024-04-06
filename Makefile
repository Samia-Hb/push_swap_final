CFLAGS = -Wall -Wextra -Werror
CC = gcc
NAME = push_swap.a
AR = ar rcs
SRCS = main.c final_push.c push_swap_utils.c arguments_checker.c moves.c moves_calculation.c ft_split.c regular_cases.c ft_atoi.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $@ $(OBJS)

clean:
	rm -f $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

fclean: clean
	rm -f $(NAME)

re: clean all

.PHONY: all clean fclean re%