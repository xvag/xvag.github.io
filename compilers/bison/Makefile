all:
	bison -d skeleton_Bison.y
	flex skeleton_Flex.l
	gcc -o parser skeleton_Bison.tab.c lex.yy.c
#	./parser input.txt
#	make clean
clean:
	rm skeleton_Bison.tab.c skeleton_Bison.tab.h lex.yy.c parser
