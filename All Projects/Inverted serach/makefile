var:=$(patsubst %.c, %.o, $(wildcard *.c))

Flist.exe:$(var)
	gcc -o $@ $^

clean :
	rm *.exe *.o