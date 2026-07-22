COMPILER = gcc
FLAGS    = -Wall -Wextra -g -O3
BINARYDIR = binary
EXENAME   = test 

VPATH = . ..

INCLUDES = -I. -I..

SRCS_LOCAL  = $(filter-out main.c, $(wildcard *.c))
SRCS_PARENT = $(filter-out ../main.c, $(wildcard ../*.c))

OBJS_LOCAL  = $(SRCS_LOCAL:%.c=$(BINARYDIR)/%.o)
OBJS_PARENT = $(SRCS_PARENT:../%.c=$(BINARYDIR)/parent_%.o)
OBJS        = $(OBJS_LOCAL) $(OBJS_PARENT)

.PHONY: all clean run

all: $(BINARYDIR) $(EXENAME)

# Link the executable
$(EXENAME): $(OBJS) $(BINARYDIR)/main.o
	$(COMPILER) $(FLAGS) $^ -o $@ -lm

# Rule for local .c files
$(BINARYDIR)/%.o: %.c
	$(COMPILER) $(FLAGS) $(INCLUDES) -c $< -o $@

# Rule for parent directory .c files
$(BINARYDIR)/parent_%.o: ../%.c
	$(COMPILER) $(FLAGS) $(INCLUDES) -c $< -o $@

# Rule for main.c (searches current directory first, then parent via VPATH)
$(BINARYDIR)/main.o: main.c
	$(COMPILER) $(FLAGS) $(INCLUDES) -c $< -o $@

# Create binary directory
$(BINARYDIR):
	mkdir -p $(BINARYDIR)

run:
	./$(EXENAME)

clean:
	rm -rf $(BINARYDIR) $(EXENAME)