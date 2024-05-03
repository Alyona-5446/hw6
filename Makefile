CFLAGS ?= -O2 -g

CFLAGS += -std=gnu99

CFLAGS += -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self \
	-Wswitch-default -Wpointer-arith -Wtype-limits -Wempty-body \
	-Wstrict-prototypes -Wold-style-declaration -Wold-style-definition \
	-Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs \
	-Wstack-usage=4096 -Wmissing-prototypes -Wfloat-equal -Wabsolute-value

CFLAGS += -fsanitize=undefined -fsanitize-undefined-trap-on-error

CC += -m32 -no-pie -fno-pie

ASFLAGS = -f elf32

AS = nasm

LDLIBS = -lm

objects = integral.o funcs.o test_funcs.o numeric.o

.PHONY: all, clean, test

all: integral

clean:
	rm -f *.o
	rm integral

test:
	./integral -h -R 4:5:-4.2:-2.35:0.001:-3
	./integral -i -R 4:6:-1.57:2.6:0.0001:0
	./integral --test-root 5:6:0.25:5.75:0.00001:1
	./integral -I 4:-5:-2:0.001:-6
	./integral -I 5:1:4:0.0001:29.25
	./integral --test-integral 6:-1:2:0.00001:-0.63878
	./integral --iterations
	./integral -ir
	./integral

integral: $(objects)
	$(CC) $(CFLAGS) -o $@ $(objects) $(LDLIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.o: %.asm
	$(AS) $(ASFLAGS) -o $@ $<
