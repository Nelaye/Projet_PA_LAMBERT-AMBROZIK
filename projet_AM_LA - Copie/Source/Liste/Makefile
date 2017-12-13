SRC = liste.c
OBJ = $(OBJDIR)liste.o
OBJDIR = ../../obj/Debug/Liste

all : $(TARGET)

debug : $(OBJ)

$(OBJDIR)%.o : %.c %.h
	@$(CC) -o $@ -c $< $(CFLAGS) $(INC)