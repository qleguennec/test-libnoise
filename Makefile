PROJECT		=	test-libnoise
BINDIR		?=	.
BUILDDIR	?=	build
NAME		=	$(BINDIR)/test-libnoise

CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror -g

BLACK		=	"\033[0;30m"
RED			=	"\033[0;31m"
GREEN		=	"\033[0;32m"
YELLOW		=	"\033[1;33m"
BLUE		=	"\033[0;34m"
MAGENTA		=	"\033[0;35m"
CYAN		=	"\033[0;36m"
WHITE		=	"\033[0;37m"
END			=	"\033[0m"

PRINT		=	@printf COL$(PROJECT)$(END)'\t'
PRPROJ		=	$(subst COL, $(BLUE), $(PRINT))
PRRM		=	$(subst COL, $(CYAN), $(PRINT))

SRCEX		=
SRC			=	$(filter-out $(SRCEX), $(filter %.c, $(shell ls)))
OBJECTS		=	$(addprefix $(BUILDDIR)/, $(SRC:%.c=%.o))

LIBLINK		=	 -lnoise -lcl -lft
LIBDIRS		:=	$(patsubst -l%, lib%, $(LIBLINK))
LIBS		:=	$(patsubst -l%, lib%.a, $(LIBDIRS))
LDFLAGS		:=	$(addprefix -L, $(LIBS))
LIBLINK		+=	 -lOpenCL
LDFLAGS		+=	$(LIBLINK)

all: $(NAME)

lib%.a: %
	$(PRPROJ)
	make --no-print-directory -C $<

$(BUILDDIR)/%.o: %.c
	@[ -d $(BUILDDIR) ] || mkdir $(BUILDDIR)
	$(PRPROJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS) $(LIBS)
	$(PRPROJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) $(LIBLINK) -o $(NAME)
	@printf "OK\t"$(NAME)'\n'

.PHONY: clean sclean fclean re r ex

clean:
	$(PRRM)
	rm -rf $(BUILDDIR)

fclean: clean
	$(PRRM)
	rm -rf $(NAME)

ex: re
	$(NAME)

re: fclean all
