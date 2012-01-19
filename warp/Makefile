#
# Makefile for ChatSys PDU Parser Module
#
include ../make.h


OBJS =	warpsock.o

all:	$(OBJS) 
	$(AR) $(AR_FLAGS) $(WARP_LIB) $(OBJS) 


.c.o:
	$(CC) $(CC_FLAGS)  $(COMMON_INCLUDE_DIRS) $<

clean:
	$(RM) -f  $(OBJS) $(WARP_LIB) *.bak


