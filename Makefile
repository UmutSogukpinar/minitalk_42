NAME_CLIENT = client
NAME_SERVER = server

SRC_CLIENT = client.c
SRC_SERVER = server.c

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)

NAME_CLIENT_BONUS = client_bonus
NAME_SERVER_BONUS = server_bonus

SRC_CLIENT_BONUS = bonus/client_bonus.c
SRC_SERVER_BONUS = bonus/server_bonus.c

OBJ_CLIENT_BONUS = $(SRC_CLIENT_BONUS:.c=.o)
OBJ_SERVER_BONUS = $(SRC_SERVER_BONUS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iprintf_42
RM = rm -rf
PRINTF_A = printf_42/libftprintf.a

all: $(NAME_SERVER) $(NAME_CLIENT)

bonus: $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

server:	$(NAME_SERVER)
client: $(NAME_CLIENT)

server_bonus: $(NAME_SERVER_BONUS)
client_bonus: $(NAME_CLIENT_BONUS)

$(NAME_SERVER): $(OBJ_SERVER)
	$(MAKE) -C printf_42
	$(CC) $(CFLAGS) $(OBJ_SERVER) -Lprintf_42 -lftprintf -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT)
	$(MAKE) -C printf_42
	$(CC) $(CFLAGS) $(OBJ_CLIENT) -Lprintf_42 -lftprintf -o $(NAME_CLIENT)

$(NAME_SERVER_BONUS): $(OBJ_SERVER_BONUS)
	$(MAKE) -C printf_42
	$(CC) $(CFLAGS) $(OBJ_SERVER_BONUS) -Lprintf_42 -lftprintf -o $(NAME_SERVER_BONUS)

$(NAME_CLIENT_BONUS): $(OBJ_CLIENT_BONUS)
	$(MAKE) -C printf_42
	$(CC) $(CFLAGS) $(OBJ_CLIENT_BONUS) -Lprintf_42 -lftprintf -o $(NAME_CLIENT_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C printf_42 clean
	$(RM) $(OBJ_SERVER) $(OBJ_CLIENT) $(OBJ_CLIENT_BONUS) $(OBJ_SERVER_BONUS)

fclean: clean
	$(MAKE) -C printf_42 fclean
	$(RM) $(NAME_SERVER) $(NAME_CLIENT) $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

re: fclean all

.PHONY: all clean fclean re server client server_bonus client_bonus bonus
