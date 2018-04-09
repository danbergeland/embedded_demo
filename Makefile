objects = test_main.o hydro.o

test_exec : $(objects)
	gcc -o test_exec $(objects)

test_main.o : hydro.h

hydro.o : hydro.h