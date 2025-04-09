SRC=	ft_printf.c\
		ft_printf_parser.c\
		ft_printf_options.c\
		ft_printf_utils.c\
		ft_intlen.c\
		ft_min.c\
		print/ft_printf_char.c\
		print/ft_printf_hex.c\
		print/ft_printf_int.c\
		print/ft_printf_ptr.c\
		print/ft_printf_str.c\
		print/ft_printf_options.c\
		print/ft_put.c

OBJ = $(SRC:.c=.o)

C=cc

CFLAGS=

INCLUDE=include

TARGET=libftprintf.a

$(TARGET): $(OBJ)
	ar rc $@ $(OBJ)

%.o: %.c
	$(C) -I$(INCLUDE) $(CFLAGS) -o $@ -c $<

all: $(TARGET)

bonus: all

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all

