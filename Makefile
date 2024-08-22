CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE_DIR)

SRCS_DIR = srcs/
BONUS_SRCS_DIR = bonus/
INCLUDE_DIR = include/
LIBFT_DIR = libft

CLIENT = client
SERVER = server
BONUS_CLIENT = client_bonus
BONUS_SERVER = server_bonus
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = client.c server.c
BONUS_SRCS = client_bonus.c server_bonus.c
OBJS = $(addprefix $(SRCS_DIR), $(SRCS:.c=.o))
BONUS_OBJS = $(addprefix $(BONUS_SRCS_DIR), $(BONUS_SRCS:.c=.o))

vpath %.c $(SRCS_DIR) $(BONUS_SRCS_DIR)

all: $(LIBFT) $(CLIENT) $(SERVER)

$(CLIENT): $(SRCS_DIR)client.o $(LIBFT)
	$(CC) $(CFLAGS) $< $(LIBFT) -o $@

$(SERVER): $(SRCS_DIR)server.o $(LIBFT)
	$(CC) $(CFLAGS) $< $(LIBFT) -o $@

bonus: $(BONUS_SERVER) $(BONUS_CLIENT)

$(BONUS_CLIENT): $(BONUS_SRCS_DIR)client_bonus.o $(LIBFT)
	$(CC) $(CFLAGS) $< $(LIBFT) -o $@

$(BONUS_SERVER): $(BONUS_SRCS_DIR)server_bonus.o $(LIBFT)
	$(CC) $(CFLAGS) $< $(LIBFT) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(SERVER) $(CLIENT) $(BONUS_SERVER) $(BONUS_CLIENT)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
