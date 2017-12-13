
export CC = gcc.exe
export LD = gcc.exe
export CFLAGS = -Wall
export TARGET = debug

INC = -I"C:\Program Files (x86)\CodeBlocks\MinGW\include" -I"C:\Program Files (x86)\CodeBlocks\SDL2-2.0.5\i686-w64-mingw32\include"
LIBDIR = -L"C:\Program Files (x86)\CodeBlocks\MinGW\lib" -L"C:\Program Files (x86)\CodeBlocks\SDL2-2.0.5\i686-w64-mingw32\lib"
LIB = "C:\Program Files (x86)\CodeBlocks\MinGW\lib\libmingw32.a" "C:\Program Files (x86)\CodeBlocks\SDL2-2.0.5\i686-w64-mingw32\lib\libSDL2main.a" "C:\Program Files (x86)\CodeBlocks\SDL2-2.0.5\i686-w64-mingw32\lib\libSDL2.dll.a"
OBJDIR = obj\Debug\
OBJ = $(OBJDIR)Liste\liste.o $(OBJDIR)Map\map.o $(OBJDIR)Niveau\niveau.o $(OBJDIR)Sprite\sprite_t.o $(OBJDIR)main.o
BIN = bin\Debug\
OUT = the_lumberjack

SOURCE = Source

all : before $(TARGET)

before: 
	@(cd $(SOURCE) && $(MAKE))

debug: out

out: $(OBJ)
    $(LD) $(LIBDIR) -o $(BIN)$(OUT) $^ $(LIB)

clean :
	@rm -r obj
	@mkdir obj
	@mkdir obj\Debug
	@mkdir obj\Debug\Liste
	@mkdir obj\Debug\Niveau
	@mkdir obj\Debug\Map
	@mkdir obj\Debug\Sprite
