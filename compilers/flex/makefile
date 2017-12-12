all:
	flex -o flex.c flex.l
	gcc -o flex -lfl flex.c
	./flex input.txt

clean:
	rm flex flex.c
