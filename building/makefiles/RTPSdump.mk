RTPSDUMP_OUTDIR= $(OUTDIR)/RTPSdump
RTPSDUMP_OUTDIR_DEBUG = $(RTPSDUMP_OUTDIR)/debug
RTPSDUMP_OUTDIR_RELEASE = $(RTPSDUMP_OUTDIR)/release

RTPSDUMP_SED_OUTPUT_DIR_DEBUG= $(subst /,\\/,$(RTPSDUMP_OUTDIR_DEBUG))
RTPSDUMP_SED_OUTPUT_DIR_RELEASE= $(subst /,\\/,$(RTPSDUMP_OUTDIR_RELEASE))

RTPSDUMP_CFLAGS = $(CFLAGS) -std=c++0x -DRTI_ENDIAN_LITTLE
RTPSDUMP_CFLAGS_DEBUG = $(CFLAGS_DEBUG) -std=c++0x -DRTI_ENDIAN_LITTLE

RTPSDUMP_TARGET_DEBUG= $(BASEDIR)/lib/$(EPROSIMA_TARGET)/RTPSdumpd
RTPSDUMP_TARGET= $(BASEDIR)/lib/$(EPROSIMA_TARGET)/RTPSdump

RTPSDUMP_INCLUDE_DIRS= $(INCLUDE_DIRS) -I$(BASEDIR)/include \
		       -I$(BASEDIR)/../CDR/include/cpp \
		       -I$(EPROSIMADIR)/code

RTPSDUMP_LIBS_DEBUG= $(LIBS_DEBUG) -ldl -lpcap -lsqlite3
RTPSDUMP_LIBS_RELEASE= $(LIBS) -ldl -lpcap -lsqlite3

RTPSDUMP_SRC_CFILES= $(EPROSIMADIR)/code/eProsima_c/eProsimaLog.c

RTPSDUMP_SRC_CPPFILES= $(EPROSIMADIR)/code/eProsima_cpp/eProsimaLog.cpp \
		       $(BASEDIR)/src/reader/pcapReader.cpp \
		       $(BASEDIR)/src/reader/ipDefragmenter.cpp \
		       $(BASEDIR)/src/RTPSPacketAnalyzer.cpp \
		       $(BASEDIR)/src/RTPSdump.cpp \
		       $(BASEDIR)/src/database/TypeCodeDB.cpp \
		       $(BASEDIR)/src/database/EntitiesDB.cpp \
		       $(BASEDIR)/src/database/DynamicDataDB.cpp \
		       $(BASEDIR)/src/cdr/ArrayTypeCode.cpp \
		       $(BASEDIR)/src/cdr/ContentTypeCode.cpp \
		       $(BASEDIR)/src/cdr/EnumTypeCode.cpp \
		       $(BASEDIR)/src/cdr/MemberedTypeCode.cpp \
		       $(BASEDIR)/src/cdr/PrimitiveTypeCode.cpp \
		       $(BASEDIR)/src/cdr/SequenceTypeCode.cpp \
		       $(BASEDIR)/src/cdr/StringTypeCode.cpp \
		       $(BASEDIR)/src/cdr/StructTypeCode.cpp \
		       $(BASEDIR)/src/cdr/TypeCode.cpp \
		       $(BASEDIR)/src/cdr/UnicodeTypeCode.cpp \
		       $(BASEDIR)/src/util/IDLPrinter.cpp \
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
	$(LN) -o $(RTPSDUMP_TARGET_DEBUG) $(LIBRARY_PATH) $(RTPSDUMP_LIBS_DEBUG) $(RTPSDUMP_OBJS_DEBUG) $(RTPSDUMP_STATIC_LIBS)

$(RTPSDUMP_TARGET): $(RTPSDUMP_OBJS_RELEASE)
	$(LN) -o $(RTPSDUMP_TARGET) $(LIBRARY_PATH) $(RTPSDUMP_LIBS_RELEASE) $(RTPSDUMP_OBJS_RELEASE) $(RTPSDUMP_STATIC_LIBS)

vpath %.c $(RTPSDUMP_SOURCES_DIRS)
vpath %.cpp $(RTPSDUMP_SOURCES_DIRS)

$(RTPSDUMP_OUTDIR_DEBUG)/%.o:%.c
	@echo Calculating dependencies \(DEBUG mode\) $<
	@$(CC) $(RTPSDUMP_CFLAGS_DEBUG) -MM $(RTPSDUMP_INCLUDE_DIRS) $< | sed "s/^.*:/$(RTPSDUMP_SED_OUTPUT_DIR_DEBUG)\/&/g" > $(@:%.o=%.d)
	@echo Compiling \(DEBUG mode\) $<  
	@$(CC) $(RTPSDUMP_CFLAGS_DEBUG) $(RTPSDUMP_INCLUDE_DIRS) $< -o $@

$(RTPSDUMP_OUTDIR_RELEASE)/%.o:%.c
	@echo Calculating dependencies \(RELEASE mode\) $<
	@$(CC) $(RTPSDUMP_CFLAGS) -MM $(RTPSDUMP_CFLAGS) $(RTPSDUMP_INCLUDE_DIRS) $< | sed "s/^.*:/$(RTPSDUMP_SED_OUTPUT_DIR_RELEASE)\/&/g" > $(@:%.o=%.d)
	@echo Compiling \(RELEASE mode\) $<
	@$(CC) $(RTPSDUMP_CFLAGS) $(RTPSDUMP_INCLUDE_DIRS) $< -o $@

$(RTPSDUMP_OUTDIR_DEBUG)/%.c.o:%.c
	@echo Calculating dependencies \(DEBUG mode\) $<
	@$(CC) $(RTPSDUMP_CFLAGS_DEBUG) -MM $(RTPSDUMP_INCLUDE_DIRS) $< | sed "s/^.*:/$(RTPSDUMP_SED_OUTPUT_DIR_DEBUG)\/&/g" > $(@:%.o=%.d)
	@echo Compiling \(DEBUG mode\) $<  
	@$(CC) $(RTPSDUMP_CFLAGS_DEBUG) $(RTPSDUMP_INCLUDE_DIRS) $< -o $@

$(RTPSDUMP_OUTDIR_RELEASE)/%.c.o:%.c
	@echo Calculating dependencies \(RELEASE mode\) $<
	@$(CC) $(RTPSDUMP_CFLAGS) -MM $(RTPSDUMP_CFLAGS) $(RTPSDUMP_INCLUDE_DIRS) $< | sed "s/^.*:/$(RTPSDUMP_SED_OUTPUT_DIR_RELEASE)\/&/g" > $(@:%.o=%.d)
	@echo Compiling \(RELEASE mode\) $<
	@$(CC) $(RTPSDUMP_CFLAGS) $(RTPSDUMP_INCLUDE_DIRS) $< -o $@

$(RTPSDUMP_OUTDIR_DEBUG)/%.cpp.o:%.cpp
	@echo Calculating dependencies \(DEBUG mode\) $<
	@$(CPP) $(RTPSDUMP_CFLAGS_DEBUG) -MM $(RTPSDUMP_INCLUDE_DIRS) $< | sed "s/^.*:/$(RTPSDUMP_SED_OUTPUT_DIR_DEBUG)\/&/g" > $(@:%.o=%.d)
	@echo Compiling \(DEBUG mode\) $<
	@$(CPP) $(RTPSDUMP_CFLAGS_DEBUG) $(RTPSDUMP_INCLUDE_DIRS) $< -o $@

$(RTPSDUMP_OUTDIR_RELEASE)/%.cpp.o:%.cpp
	@echo Calculating dependencies \(RELEASE mode\) $<
	@$(CPP) $(RTPSDUMP_CFLAGS) -MM $(RTPSDUMP_CFLAGS) $(RTPSDUMP_INCLUDE_DIRS) $< | sed "s/^.*:/$(RTPSDUMP_SED_OUTPUT_DIR_RELEASE)\/&/g" > $(@:%.o=%.d)
	@echo Compiling \(RELEASE mode\) $<
	@$(CPP) $(RTPSDUMP_CFLAGS) $(RTPSDUMP_INCLUDE_DIRS) $< -o $@



