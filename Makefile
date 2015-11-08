
CC=gcc
program_NAME :=main
program_C_SRCS := $(wildcard *.c)
program_C_OBJS := ${program_C_SRCS:.c=.o}
program_OBJS := $(program_C_OBJS) 
program_INCLUDE_DIRS :=
program_LIBRARY_DIRS :=
program_LIBRARIES :=m

CPPFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))
LDFLAGS += $(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir))
LDFLAGS += $(foreach library,$(program_LIBRARIES),-l$(library))
CFLAGS:=-std=c99 -Wall


program_deps += $(foreach srs, $(program_C_SRCS), $(srs) $(LDFLAGS))
.PHONY: all clean distclean

all: $(program_NAME)

$(program_NAME):
	$(CC) $(CFLAGS) $(program_deps) -o $(program_NAME)

clean:
	@- $(RM) $(program_NAME)
	@- $(RM) $(program_OBJS)

distclean: clean
