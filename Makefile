include ./make.h

SERVER_TARGET = server
CLIENT_TARGET = client

all:$(SERVER_TARGET) $(CLIENT_TARGET)

$(SERVER_TARGET):
	make -w -C $(SERVER_BLOCK) -f Makefile
	$(CP) $(SERVER_BLOCK)/$(SERVER_TARGET) ./
	
$(CLIENT_TARGET):
	make -w -C $(CLIENT_BLOCK) -f Makefile
	$(CP) $(CLIENT_BLOCK)/$(CLIENT_TARGET) ./	
clean:
	make -w -C  $(SERVER_BLOCK)  -f  Makefile clean
	make -w -C  $(CLIENT_BLOCK)  -f  Makefile clean
	$(RM) $(RM_FLAGS) $(OBJS) $(TARGETS)
	$(RM) $(RM_FLAGS) *.lib *.bak *.o $(SERVER_TARGET) $(CLIENT_TARGET)


