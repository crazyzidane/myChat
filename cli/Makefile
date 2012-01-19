#
# Makefile for ALL Workspace
#
include ../make.h

CLIENT_TARGET = client

TARGETS	 =  $(CLIENT_TARGET)


CLIENT_OBJS = tcpcli.o 

OBJS     =  $(CLIENT_OBJS) 

all: $(LIBS) $(TARGETS)

$(CLIENT_TARGET):$(CLIENT_OBJS)
	$(CC) $(CC_OUTPUT_FLAGS) $(CLIENT_TARGET) $(CLIENT_OBJS) $(LIBS) $(CC_PTHREAD_FLAGS)
	
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

