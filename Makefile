PROG := boatman
SRCS := $(wildcard ./src/*.c)
OBJS := $(SRCS:%.c=%.o)
DEPS := $(SRCS:%.c=%.d)

CC := gcc
CCFLAGS :=

all: $(DEPENDS) $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CCFLAGS) -o $@ $^

.c.o:
	$(CC) $(CCFLAGS) -MMD -MP -MF $(<:%.c=%.d) -c $< -o $(<:%.c=%.o)

.PHONY: clean
clean:
	$(RM) $(PROG) $(OBJS) $(DEPS)

-include $(DEPS)
