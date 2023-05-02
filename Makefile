all: embedder_linux.c
	gcc -o embedder embedder_linux.c
clean:
	rm embedder
