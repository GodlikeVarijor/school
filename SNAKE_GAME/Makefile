CC = gcc
CFLAGS = -Wall

SRCS = snake.c score.c snake_logic.c
OBJS = $(SRCS:.c=.o)

TARGET = snake

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)