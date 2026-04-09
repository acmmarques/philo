NAME        = philo

# Compiler and flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -pthread

# Directories
SRC_DIR     = src/
OBJ_DIR     = obj/
INC_DIR     = inc/

# Colors
GREEN       = \033[0;32m
RED         = \033[0;31m
BLUE        = \033[0;34m
GRAY        = \033[0;90m
RESET       = \033[0m

# Files
SRC_FILES   = exit.c \
			  init.c \
			  main.c \
			  parsing.c \

# TESTS
TEST_DIR	= tests/

TEST_FILES	= test_main.c \

TEST_SRCS	= $(addprefix $(TEST_DIR), $(TEST_FILES))
PROJ_SRCS_NO_MAIN = $(filter-out $(SRC_DIR)main.c, $(SRCS))

SRCS        = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS        = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

# Headers
INCS        = -I $(INC_DIR)

# Rules
all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)[SUCCESS] $(NAME) compiled successfully!$(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@
	@echo "$(BLUE)[COMPILING] $<...$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(GRAY)[INFO] Created object directory.$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)[CLEAN] Removed object files.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)[FCLEAN] Removed $(NAME) executable.$(RESET)"

re: fclean all

# --- TDD Rule ---
test:
	@echo "$(BLUE)[BUILDING TESTS] Compiling test runner...$(RESET)"
	@$(CC) $(CFLAGS) $(INCS) $(PROJ_SRCS_NO_MAIN) $(TEST_SRCS) -o test_runner
	@echo "$(GREEN)[RUNNING TESTS] Executing test_runner...$(RESET)"
	@./test_runner
	@rm -f test_runner

.PHONY: all clean fclean re test

