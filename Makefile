BASEDIR=.
OUTDIR= $(BASEDIR)/output
CC=gcc
CPP=g++
LN=g++
AR=ar
CP=cp

#-include $(EPROSIMADIR)/building/makefiles/dds.mk
-include $(BASEDIR)/thirdparty/dev-env/building/makefiles/eProsima.mk
#Build with RTI DDS 4.4d
-include $(BASEDIR)/building/makefiles/DDSRecorder.mk

.PHONY: all

all: DDSRecorder

clean:
	@rm -f $(OBJS)
	@rm -f $(DEPS)

ifneq ($(MAKECMDGOALS), clean)
-include $(DEPS)
endif

