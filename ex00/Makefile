NAME = rush01

CXX = gcc
CXXFLAGS = -Wall -Wextra -Werror -Wpedantic -MMD -MP

SRCDIR = .
INCDIR = .
OBJDIR = obj

SRCS = $(addprefix $(SRCDIR)/, main.c array.c solver.c stack.c validate_board.c validate_board2.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEPS = $(OBJS:.o=.d)

IFLAGS = -I$(INCDIR)

COUNT_FILE = .build_count
TOTAL_FILE = .build_total
BUILD_FILES = $(COUNT_FILE) $(TOTAL_FILE)

define INIT_COUNT
$(if $(COUNT_STARTED),:,$(eval COUNT_STARTED := 1)needed=0; for obj in $(OBJS); do $(MAKE) --no-print-directory -q $$obj >/dev/null 2>&1; status=$$?; if [ $$status -eq 1 ]; then needed=$$((needed + 1)); elif [ $$status -eq 2 ]; then needed=$(words $(OBJS)); break; fi; done; if [ $$needed -eq 0 ]; then needed=1; fi; echo 0 > $(COUNT_FILE); echo $$needed > $(TOTAL_FILE); printf "\n\n")
endef

define ESC
$(shell printf '\033')
endef

RESET   = $(ESC)[0m
BOLD    = $(ESC)[1m
RED     = $(ESC)[31m
GREEN   = $(ESC)[32m
YELLOW  = $(ESC)[33m
ORANGE  = $(ESC)[38;5;208m
YLLWGRN = $(ESC)[38;2;150;255;25m

all: $(NAME)

$(NAME): $(OBJS)
	@{ \
		printf "$(GREEN)Linking...$(RESET)\n" && \
		$(CXX) $(CXXFLAGS) $(IFLAGS) $(OBJS) -o $(NAME) && \
		rm -f $(BUILD_FILES) && \
		printf "$(GREEN)Build complete (100%%)$(RESET)\n"; \
	} || { rm -f $(BUILD_FILES); false; }

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@{ \
		$(call INIT_COUNT) && \
		count=$$(cat $(COUNT_FILE)) && \
		total=$$(cat $(TOTAL_FILE)) && \
		count=$$((count + 1)) && \
		echo $$count > $(COUNT_FILE) && \
		percent_str=$$(echo "scale=2; $$count / $$total * 100" | bc) && \
		percent_int=$$(printf "%.0f" $$percent_str) && \
		filled=$$((percent_int / 2)) && \
		empty=$$((50 - filled)) && \
		bar=""; bg=""; \
		i=0; while [ $$i -lt $$filled ]; do bar="$${bar}█"; i=$$((i+1)); done && \
		i=0; while [ $$i -lt $$empty ]; do bg="$${bg}░"; i=$$((i+1)); done && \
		if [ $$percent_int -lt 25 ]; then color="$(RED)"; \
		elif [ $$percent_int -lt 50 ]; then color="$(ORANGE)"; \
		elif [ $$percent_int -lt 75 ]; then color="$(YELLOW)"; \
		elif [ $$percent_int -lt 100 ]; then color="$(YLLWGRN)"; \
		else color="$(GREEN)"; fi && \
		printf "$(ESC)[2A\r$(ESC)[K%sCompiling $(NAME): [%s%s] [%3d/%3d] %6.2f%%%s\n" \
		"$(BOLD)$$color" "$$bar" "$$bg" $$count $$total "$$percent_str" "$(RESET)" && \
		printf "\r$(ESC)[K$(BOLD)Current file:$(RESET) %-34s\n" "$(notdir $<)" && \
		$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -o $@; \
	} || { rm -f $(BUILD_FILES); false; }

$(OBJDIR):
	@mkdir -p $(OBJDIR)

-include $(DEPS)

clean:
	@rm -rf $(OBJDIR) $(COUNT_FILE) $(TOTAL_FILE)
	@printf "$(RED)Objects removed$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(RED)Executable removed$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re