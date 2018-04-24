objects = test_main.o hydro.o HAL_mock.o

test_exec : $(objects)
	gcc -o test_exec $(objects)

test_main.o : hydro.h

hydro.o : hydro.h HAL_mock.h

HAL_mock.o : HAL_mock.h