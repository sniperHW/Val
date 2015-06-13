CFLAGS   = -g -fno-strict-aliasing -Wall
LDFLAGS  = -llua 
INCLUDE  = -I./

uname_S := $(shell sh -c 'uname -s 2>/dev/null || echo not')
ifeq ($(uname_S),Linux)
	LDFLAGS += -ldl -lrt -lm
	DEFINE  += -D_LINUX
endif

ifeq ($(uname_S),FreeBSD)
	LDFLAGS += -lexecinfo
	DEFINE  += -D_BSD
endif

ifeq ($(uname_S),MINGW32_NT-6.1)
	DEFINE  += -D_WIN
endif

source=		\
Val.c		\
lookup8.c


test:$(source)
	gcc $(SHARED) $(CFLAGS) -c $(source) test.c $(DEFINE) $(INCLUDE)
	gcc $(SHARED) $(CFLAGS) -o test *.o $(LDFLAGS)
	rm *.o