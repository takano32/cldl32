OBJ=main.o Font.o Comment.o Link.o Span.o Footnote.o
cldl32	:	cldl32.res ${OBJ}
	gcc -shared -mwindows -mno-cygwin -o cldl32.dll ${OBJ} cldl32.res -limm32
cldl32.res	:	cldl32.rc
	windres $< -O coff -o $@

install:
	cp cldl32.dll /cygdrive/D/Tools/clcl

installz:
	cp cldl32.dll /cygdrive/Z/Tools/clcl

clean:
	rm -f *.o *.res *.dll
