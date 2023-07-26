CC = gcc
CFLAGS = -Wall -Werror
LDFLAGS =
LIBS =

TARGET = hitokoto

# 检查操作系统类型
ifeq ($(shell uname -s), Linux)
    # Linux 平台
    CFLAGS += -I/usr/include/json-c/
    LDFLAGS += -L/usr/lib/
else ifeq ($(shell uname -s), Darwin)
    # macOS 平台
    # 检查处理器架构
    ifeq ($(shell uname -p), arm)
        CFLAGS += -I/opt/homebrew/include/
        LDFLAGS += -L/opt/homebrew/lib
    else
        CFLAGS += -I/usr/local/include/
        LDFLAGS += -L/usr/local/lib
    endif
endif

LIBS += -ljson-c -lcurl

.PHONY: all clean

all: $(TARGET)

$(TARGET): hitokoto.c
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@ $(LIBS)

clean:
	rm -f $(TARGET)
