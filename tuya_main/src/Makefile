BIN:=tuya_main
SRCS:=$(wildcard *.c)
OBJS:=$(SRCS:.c=.o)
LDFLAGS:=-llink_core -lmiddleware_implementation -lplatform_port -lutils_modules -largp -lblobmsg_json -lubox -lubus

CFLAGS:=-Wall

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) 

clean:
	$(RM) $(BIN) $(OBJS)
