COMPILER  = gcc
FLAGS     = -Wall -Wextra -g -O3
BINARYDIR = binary
EXENAME   = test 

INCLUDES  = -I. -I.. -I../../Vector

SRCS_LOCAL  = $(filter-out main.c, $(wildcard *.c))
SRCS_PARENT = $(filter-out ../main.c, $(wildcard ../*.c))
SRCS_VECTOR = $(wildcard ../../Vector/*.c)

OBJS_LOCAL  = $(SRCS_LOCAL:%.c=$(BINARYDIR)/%.o)
OBJS_PARENT = $(SRCS_PARENT:../%.c=$(BINARYDIR)/parent_%.o)
OBJS_VECTOR = $(SRCS_VECTOR:../../Vector/%.c=$(BINARYDIR)/vector_%.o)

OBJS        = $(OBJS_LOCAL) $(OBJS_PARENT) $(OBJS_VECTOR)

.PHONY: all clean run

all: $(BINARYDIR) $(EXENAME)

# Link the executable
$(EXENAME): $(OBJS) $(BINARYDIR)/main.o
	$(COMPILER) $(FLAGS) $^ -o $@ -lm

# Rule for local .c files
$(BINARYDIR)/%.o: %.c
	$(COMPILER) $(FLAGS) $(INCLUDES) -c $< -o $@

# Rule for parent directory 
$(BINARYDIR)/parent_%.o: ../%.c
	$(COMPILER) $(FLAGS) $(INCLUDES) -c $< -o $@

# Rule for Vector/ directory 
$(BINARYDIR)/vector_%.o: ../../Vector/%.c
	$(COMPILER) $(FLAGS) $(INCLUDES) -c $< -o $@

# Rule for main.c
$(BINARYDIR)/main.o: main.c
	$(COMPILER) $(FLAGS) $(INCLUDES) -c $< -o $@

# Create binary directory
$(BINARYDIR):
	mkdir -p $(BINARYDIR)

run:
	./$(EXENAME)

clean:
	rm -rf $(BINARYDIR) $(EXENAME)