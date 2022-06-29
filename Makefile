CC=gcc

INCDIRS=-I ./include
OPT=-O3
CFLAGS=-Wall -Wextra -g  $(OPT) $(INCDIRS)
OBJDIR=./obj

VPATH = ./src ./tests
SRCS=wdist.c test_wdist.c
OBJS=$(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))
TEST_APP=test_app

all: $(TEST_APP)

$(TEST_APP): $(OBJS)
	$(CC) -o $@ $^

$(OBJDIR)/%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf $(TEST_APP) $(OBJS)

