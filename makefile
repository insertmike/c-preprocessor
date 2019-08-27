all: target1 target2 target3 target4 

target1:
	cl preprocess.c
	preprocess -i math_functions.c 
target2:
	cl preprocess.c
	preprocess -i math_functions.c -v
target3:
	cl preprocess.c
	preprocess -i string_functions.c 
target4:
	cl preprocess.c
	preprocess -i string_functions.c -v 
	
clean: 
		del *.obj
		del *.exe 
	