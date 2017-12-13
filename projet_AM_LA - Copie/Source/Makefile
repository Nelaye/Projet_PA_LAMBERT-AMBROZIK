SRC = main.c
OBJ = $(OBJDIR)main.o
OBJDIR = ../obj/Debug/

LISTE = Liste
NIVEAU = Niveau
MAP = Map
SPRITE = Sprite


all : before $(TARGET)

before:
	@(cd $(LISTE) && $(MAKE))
	@(cd $(MAP) && $(MAKE))
	@(cd $(SPRITE) && $(MAKE))
	@(cd $(NIVEAU) && $(MAKE))

debug : $(OBJ)

$(OBJDIR)%.o : %.c
	@$(CC) -o $@ -c $< $(CFLAGS) $(INC)