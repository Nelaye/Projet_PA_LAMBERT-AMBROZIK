SRC = liste.c map.c sprite_t.c niveau.c main.c
OBJ = $(OBJDIR)liste.o $(OBJDIR)map.o $(OBJDIR)sprite_t.o $(OBJDIR)niveau.o $(OBJDIR)main.o
OBJDIR = obj\

CC = gcc.exe
LD = gcc.exe
CFLAG = -Wall
INC = -I"C:\Program Files (x86)\CodeBlocks\MinGW\include" -I"C:\Program Files (x86)\CodeBlocks\SDL2-2.0.5\i686-w64-mingw32\include"
LIBDIR = -L"C:\Program Files (x86)\CodeBlocks\MinGW\lib" -L"C:\Program Files (x86)\CodeBlocks\SDL2-2.0.5\i686-w64-mingw32\lib"
LIB = "C:\Program Files (x86)\CodeBlocks\MinGW\lib\libmingw32.a" "C:\Program Files (x86)\CodeBlocks\SDL2-2.0.5\i686-w64-mingw32\lib\libSDL2main.a" "C:\Program Files (x86)\CodeBlocks\SDL2-2.0.5\i686-w64-mingw32\lib\libSDL2.dll.a"
BIN = bin\Debug\
OUT = the_lumberjack

all :

debug: $(OBJ)

$(OBJDIR)%.o : %.c %.h
    $(CC) -o $@ -c $< $(CFLAGS) $(INC)

out: $(OBJ)
    $(LD) $(LIBDIR) -o $(BIN)$(OUT) $^ $(LIB)

clean :
rd \s obj
md obj
