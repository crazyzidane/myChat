#
# Makefile for ChatSys PDU Parser Module
#
include ../make.h


OBJS =	parser.o

all:	$(OBJS) 
	$(AR) $(AR_FLAGS) $(PROTOCOL_LIB) $(OBJS) 


.c.o:
	$(CC) $(CC_FLAGS)  $(COMMON_INCLUDE_DIRS) $<

clean:
	$(RM) -f  $(OBJS) $(PROTOCOL_LIB) *.bak


