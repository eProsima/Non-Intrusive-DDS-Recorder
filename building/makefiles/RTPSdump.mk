RTPSDUMP_OUTDIR= $(OUTDIR)/RTPSdump
RTPSDUMP_OUTDIR_DEBUG = $(RTPSDUMP_OUTDIR)/debug
RTPSDUMP_OUTDIR_RELEASE = $(RTPSDUMP_OUTDIR)/release

RTPSDUMP_SED_OUTPUT_DIR_DEBUG= $(subst /,\\/,$(RTPSDUMP_OUTDIR_DEBUG))
RTPSDUMP_SED_OUTPUT_DIR_RELEASE= $(subst /,\\/,$(RTPSDUMP_OUTDIR_RELEASE))

RTPSDUMP_TARGET_DEBUG= $(BASEDIR)/lib/i86Linux2.6gcc4.1.2/RTPSdumpd
RTPSDUMP_TARGET= $(BASEDIR)/lib/i86Linux2.6gcc4.1.2/RTPSdump

RTPSDUMP_INCLUDE_DIRS= $(INCLUDE_DIRS) -I$(BASEDIR)/include \
					-I$(EPROSIMADIR)/code

RTPSDUMP_LIBS_DEBUG= $(LIBS_DEBUG) -ldl -lpcap
RTPSDUMP_LIBS_RELEASE= $(LIBS) -ldl -lpcap

RTPSDUMP_SRC_CFILES= $(EPROSIMADIR)/code/eProsima_c/eProsimaLog.c

RTPSDUMP_SRC_CPPFILES= $(EPROSIMADIR)/code/eProsima_cpp/eProsimaLog.cpp \
		       $(BASEDIR)/src/reader/pcapReader.cpp \
		       $(BASEDIR)/src/RTPSPacketAnalyzer.cpp \
		       $(BASEDIR)/src/RTPSdump.cpp \
		       $(BASEDIR)/src/main.cpp

# Project sources are copied to the current directory
RTPSDUMP_SRCS= $(RTPSDUMP_SRC_CFILES) $(RTPSDUMP_SRC_CPPFILES)

# Source directories
RTPSDUMP_SOURCES_DIRS_AUX= $(foreach srcdir, $(dir $(RTPSDUMP_SRCS)), $(srcdir))
RTPSDUMP_SOURCES_DIRS= $(shell echo $(RTPSDUMP_SOURCES_DIRS_AUX) | tr " " "\n" | sort | uniq | tr "\n" " ")

RTPSDUMP_OBJS_DEBUG = $(foreach obj,$(notdir $(addsuffix .o, $(RTPSDUMP_SRCS))), $(RTPSDUMP_OUTDIR_DEBUG)/$(obj))
RTPSDUMP_DEPS_DEBUG = $(foreach dep,$(notdir $(addsuffix .d, $(RTPSDUMP_SRCS))), $(RTPSDUMP_OUTDIR_DEBUG)/$(dep))
RTPSDUMP_OBJS_RELEASE = $(foreach obj,$(notdir $(addsuffix .o, $(RTPSDUMP_SRCS))), $(RTPSDUMP_OUTDIR_RELEASE)/$(obj))
RTPSDUMP_DEPS_RELEASE = $(foreach dep,$(notdir $(addsuffix .d, $(RTPSDUMP_SRCS))), $(RTPSDUMP_OUTDIR_RELEASE)/$(dep))

OBJS+= $(RTPSDUMP_OBJS_DEBUG) $(RTPSDUMP_OBJS_RELEASE)
DEPS+= $(RTPSDUMP_DEPS_DEBUG) $(RTPSDUMP_DEPS_RELEASE)

.PHONY: RTPSdump checkRTPSdumpDirectories

RTPSdump: checkRTPSdumpDirectories $(RTPSDUMP_TARGET_DEBUG) $(RTPSDUMP_TARGET)

checkRTPSdumpDirectories:
	@mkdir -p $(OUTDIR)
	@mkdir -p $(RTPSDUMP_OUTDIR)
	@mkdir -p $(RTPSDUMP_OUTDIR_DEBUG)
	@mkdir -p $(RTPSDUMP_OUTDIR_RELEASE)

$(RTPSDUMP_TARGET_DEBUG): $(RTPSDUMP_OBJS_DEBUG)
	$(LN) -o $(RTPSDUMP_TARGET_DEBUG) $(LIBRARY_PATH) $(RTPSDUMP_LIBS_DEBUG) $(RTPSDUMP_OBJS_DEBUG)

$(RTPSDUMP_TARGET): $(RTPSDUMP_OBJS_RELEASE)
	$(LN) -o $(RTPSDUMP_TARGET) $(LIBRARY_PATH) $(RTPSDUMP_LIBS_RELEASE) $(RTPSDUMP_OBJS_RELEASE)

vpath %.c $(RTPSDUMP_SOURCES_DIRS)
vpath %.cpp $(RTPSDUMP_SOURCES_DIRS)

$(RTPSDUMP_OUTDIR_DEBUG)/%.o:%.c
	@echo Calculating dependencies \(DEBUG mode\) $<
	@$(CC) $(CFLAGS_DEBUG) -MM $(RTPSDUMP_INCLUDE_DIRS) $< | sed "s/^.*:/$(RTPSDUMP_SED_OUTPUT_DIR_DEBUG)\/&/g" > $(@:%.o=%.d)
	@echo Compiling \(DEBUG mode\) $<  
	@$(CC) $(CFLAGS_DEBUG) $(RTPSDUMP_INCLUDE_DIRS) $< -o $@

$(RTPSDUMP_OUTDIR_RELEASE)/%.o:%.c
	@echo Calculating dependencies \(RELEASE mode\) $<
	@$(CC) $(CFLAGS) -MM $(CFLAGS) $(RTPSDUMP_INCLUDE_DIRS) $< | sed "s/^.*:/$(RTPSDUMP_SED_OUTPUT_DIR_RELEASE)\/&/g" > $(@:%.o=%.d)
	@echo Compiling \(RELEASE mode\) $<
	@$(CC) $(CFLAGS) $(RTPSDUMP_INCLUDE_DIRS) $< -o $@

$(RTPSDUMP_OUTDIR_DEBUG)/%.c.o:%.c
	@echo Calculating dependencies \(DEBUG mode\) $<
	@$(CC) $(CFLAGS_DEBUG) -MM $(RTPSDUMP_INCLUDE_DIRS) $< | sed "s/^.*:/$(RTPSDUMP_SED_OUTPUT_DIR_DEBUG)\/&/g" > $(@:%.o=%.d)
	@echo Compiling \(DEBUG mode\) $<  
	@$(CC) $(CFLAGS_DEBUG) $(RTPSDUMP_INCLUDE_DIRS) $< -o $@

$(RTPSDUMP_OUTDIR_RELEASE)/%.c.o:%.c
	@echo Calculating dependencies \(RELEASE mode\) $<
	@$(CC) $(CFLAGS) -MM $(CFLAGS) $(RTPSDUMP_INCLUDE_DIRS) $< | sed "s/^.*:/$(RTPSDUMP_SED_OUTPUT_DIR_RELEASE)\/&/g" > $(@:%.o=%.d)
	@echo Compiling \(RELEASE mode\) $<
	@$(CC) $(CFLAGS) $(RTPSDUMP_INCLUDE_DIRS) $< -o $@

$(RTPSDUMP_OUTDIR_DEBUG)/%.cpp.o:%.cpp
	@echo Calculating dependencies \(DEBUG mode\) $<
	@$(CPP) $(CFLAGS_DEBUG) -MM $(RTPSDUMP_INCLUDE_DIRS) $< | sed "s/^.*:/$(RTPSDUMP_SED_OUTPUT_DIR_DEBUG)\/&/g" > $(@:%.o=%.d)
	@echo Compiling \(DEBUG mode\) $<
	@$(CPP) $(CFLAGS_DEBUG) $(RTPSDUMP_INCLUDE_DIRS) $< -o $@

$(RTPSDUMP_OUTDIR_RELEASE)/%.cpp.o:%.cpp
	@echo Calculating dependencies \(RELEASE mode\) $<
	@$(CPP) $(CFLAGS) -MM $(CFLAGS) $(RTPSDUMP_INCLUDE_DIRS) $< | sed "s/^.*:/$(RTPSDUMP_SED_OUTPUT_DIR_RELEASE)\/&/g" > $(@:%.o=%.d)
	@echo Compiling \(RELEASE mode\) $<
	@$(CPP) $(CFLAGS) $(RTPSDUMP_INCLUDE_DIRS) $< -o $@



