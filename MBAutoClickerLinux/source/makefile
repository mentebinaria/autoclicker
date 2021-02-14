all: autoclicker
autoclicker: main.o click.o
	gcc -o autoclicker main.o click.o -lX11
clean:
	rm -rf *.o *~ autoclicker