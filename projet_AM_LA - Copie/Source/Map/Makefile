SRC = map.c
OBJ = $(OBJDIR)map.o
OBJDIR = ../../obj/Debug/Map

all : $(TARGET)

debug : $(OBJ)

$(OBJDIR)%.o : %.c %.h
	@$(CC) -o $@ -c $< $(CFLAGS) $(INC)