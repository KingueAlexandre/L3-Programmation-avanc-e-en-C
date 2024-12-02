# COMPILING LOW LEVEL IMAGE PROCESSING FEATURES

basic_image_process.so: basic_image_process.o
	gcc -shared basic_image_process.o -o basic_image_process.so -g

basic_image_process.o: basic_image_process.c
	gcc -c basic_image_process.c -fpic -o basic_image_process.o -O2 -g

clean:
	rm -f basic_image_process.so
