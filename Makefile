TARGET :=assambler
CC := gcc
CFLAGS := -Wall -ansi -g
FOO := -pedantic
DEPFLAGS := -MP -MD

SRCS = $(foreach D,.,$(wildcard $(D)/*.c))
#SRCS := $(shell find $(SRC_DIRS) -name '*.c')
OBJECTS := $(SRCS:%.c=%.o)
DEPFILES := $(OBJECTS:.o=.d)


all: $(TARGET)

${TARGET}: $(OBJECTS)
	$(CC) -o $@ $^ -lm

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $< 

.PHONY: clean 
clean:
	rm -rf $(TARGET) $(OBJECTS) $(DEPFILES)
