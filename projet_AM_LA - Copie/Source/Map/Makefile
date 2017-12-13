SRC = map.c
OBJ = $(OBJDIR)map.o
OBJDIR = ../../obj/Debug/Map

all : $(TARGET)

debug : $(OBJ)

$(OBJDIR)%.o : %.c
	@$(CC) -o $@ -c $< $(CFLAGS) $(INC)