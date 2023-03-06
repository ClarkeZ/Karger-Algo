CC = gcc
SOURCE = $(wildcard *.c)
OBJS = $(SOURCE:.c=.o)
HEADERS = $(wildcard *.h)
DOT = $(wildcard *.dot)

OUT = main

FLAGS = -g -Wall -O2 

all: $(OBJS)
	$(CC) $(FLAGS) -o $(OUT) $^

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) -o $@ -c $< 

clean:
	rm -f $(OBJS) $(OUT) $(DOT)
