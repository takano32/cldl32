OBJ=main.o Font.o Comment.o Link.o Div.o Span.o Footnote.o
cldl32	:	cldl32.res ${OBJ}
	${CC} -shared -mwindows -mno-cygwin -o cldl32.dll ${OBJ} cldl32.res -limm32

.SUFFIXES:	.rc .res
.rc.res:
	windres $< -O coff -o $@

install:
	cp cldl32.dll /cygdrive/D/Tools/clcl

installz:
	cp cldl32.dll /cygdrive/Z/Tools/clcl

clean:
	rm -f *.o *.res *.dll
