cldl32	:	main.o cldl32.res Font.o Comment.o Link.o
	gcc -shared -mwindows -mno-cygwin -o cldl32.dll main.o cldl32.res Font.o Comment.o Link.o -limm32
cldl32.res	:	cldl32.rc
	windres $< -O coff -o $@

install:
	cp cldl32.dll D:\Tools\clcl

clean:
	rm -f *.o *.res *.dll