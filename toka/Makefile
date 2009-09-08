CFLAGS = -Wall
LDFLAGS = -ldl
DEPS = bits.c class.c cmdline.c conditionals.c console.c data.c debug.c decompile.c dictionary.c errors.c ffi.c files.c gc.c initial.c interpret.c math.c parser.c quotes.c stack.c strings.c toka.c vm.c
toka: $(DEPS)
	 gcc $(CFLAGS) $(LDFLAGS) $(OTHER) $(DEPS) -o toka

clean:
	rm -f toka *~
