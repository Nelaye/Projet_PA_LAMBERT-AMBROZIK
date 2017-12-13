SRC = sprite_t.c
OBJ = $(OBJDIR)sprite_t.o
OBJDIR = ../../obj/Debug/Sprite

all : $(TARGET)

debug : $(OBJ)

$(OBJDIR)%.o : %.c %.h
	@$(CC) -o $@ -c $< $(CFLAGS) $(INC)