SRC = niveau.c
OBJ = $(OBJDIR)niveau.o
OBJDIR = ../../obj/Debug/Niveau

all : $(TARGET)

debug : $(OBJ)

$(OBJDIR)%.o : %.c %.h
	@$(CC) -o $@ -c $< $(CFLAGS) $(INC)