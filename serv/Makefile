#
# Makefile for ALL Workspace
#
include ../make.h

SERVER_TARGET = server

TARGETS	 =  $(SERVER_TARGET) 


SERVER_OBJS = tcpserv.o 

OBJS     =   $(SERVER_OBJS) 

all: $(LIBS) $(TARGETS)

$(SERVER_TARGET):$(SERVER_OBJS)
	$(CC) $(CC_OUTPUT_FLAGS) $(SERVER_TARGET) $(SERVER_OBJS) $(LIBS) $(CC_PTHREAD_FLAGS)

.c.o:
	$(CC) $(CC_FLAGS)  $(COMMON_INCLUDE_DIRS)  $<

# Make for ChatSys PDU Parser Module
# Output PDU_PARSER_LIB - stack.lib
$(PROTOCOL_LIB):
	make -w -C $(CHATSYS_PROTOCOL_DIR) -f Makefile	all
	$(CP) $(CHATSYS_PROTOCOL_DIR)/$(PROTOCOL_LIB) ./

$(WARP_LIB):
	make -w -C $(CHATSYS_WARP_DIR) -f Makefile	all
	$(CP) $(CHATSYS_WARP_DIR)/$(WARP_LIB) ./


clean:
	make -w -C $(CHATSYS_PROTOCOL_DIR) -f Makefile clean
	make -w -C $(CHATSYS_WARP_DIR) -f Makefile clean
	$(RM) $(RM_FLAGS) $(OBJS) $(TARGETS)
	$(RM) $(RM_FLAGS) *.lib *.bak
