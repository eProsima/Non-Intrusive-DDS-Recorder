DDSRECORDER_OUTDIR= $(OUTDIR)/DDSRecorder
DDSRECORDER_OUTDIR_DEBUG = $(DDSRECORDER_OUTDIR)/debug
DDSRECORDER_OUTDIR_RELEASE = $(DDSRECORDER_OUTDIR)/release

DDSRECORDER_SED_OUTPUT_DIR_DEBUG= $(subst /,\\/,$(DDSRECORDER_OUTDIR_DEBUG))
DDSRECORDER_SED_OUTPUT_DIR_RELEASE= $(subst /,\\/,$(DDSRECORDER_OUTDIR_RELEASE))

DDSRECORDER_CFLAGS = $(CFLAGS) -std=c++0x -DSQLITE_PREPARE_V2
DDSRECORDER_CFLAGS_DEBUG = $(CFLAGS_DEBUG) -std=c++0x -DSQLITE_PREPARE_V2

DDSRECORDER_TARGET_DEBUG= $(BASEDIR)/lib/$(EPROSIMA_TARGET)/DDSRecorderd
DDSRECORDER_TARGET= $(BASEDIR)/lib/$(EPROSIMA_TARGET)/DDSRecorder

DDSRECORDER_INCLUDE_DIRS= $(INCLUDE_DIRS) -I$(BASEDIR)/include \
		       -I$(BASEDIR)/../CDR/include \
		       -I$(EPROSIMADIR)/code

DDSRECORDER_LIBS_DEBUG= $(LIBS_DEBUG) -L$(BASEDIR)/../CDR/lib/$(EPROSIMA_TARGET) \
			-Bdynamic -ldl -lpcap -lsqlite3 -lboost_system-mt \
			-Bstatic -lcdrd
DDSRECORDER_LIBS_RELEASE= $(LIBS) -L$(BASEDIR)/../CDR/lib/$(EPROSIMA_TARGET) \
			  -Bdynamic -ldl -lpcap -lsqlite3 -lboost_system-mt \
			  -Bstatic -lcdr

DDSRECORDER_SRC_CFILES=

DDSRECORDER_SRC_CPPFILES= $(EPROSIMADIR)/code/eProsima_cpp/eProsimaLog.cpp \
		       $(BASEDIR)/src/reader/pcapReader.cpp \
		       $(BASEDIR)/src/reader/ipDefragmenter.cpp \
		       $(BASEDIR)/src/RTPSPacketAnalyzer.cpp \
		       $(BASEDIR)/src/DDSRecorder.cpp \
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
		       $(BASEDIR)/src/cdr/UnionTypeCode.cpp \
		       $(BASEDIR)/src/util/IDLPrinter.cpp \
		       $(BASEDIR)/src/main.cpp

# Project sources are copied to the current directory
DDSRECORDER_SRCS= $(DDSRECORDER_SRC_CFILES) $(DDSRECORDER_SRC_CPPFILES)

# Source directories
DDSRECORDER_SOURCES_DIRS_AUX= $(foreach srcdir, $(dir $(DDSRECORDER_SRCS)), $(srcdir))
DDSRECORDER_SOURCES_DIRS= $(shell echo $(DDSRECORDER_SOURCES_DIRS_AUX) | tr " " "\n" | sort | uniq | tr "\n" " ")

DDSRECORDER_OBJS_DEBUG = $(foreach obj,$(notdir $(addsuffix .o, $(DDSRECORDER_SRCS))), $(DDSRECORDER_OUTDIR_DEBUG)/$(obj))
DDSRECORDER_DEPS_DEBUG = $(foreach dep,$(notdir $(addsuffix .d, $(DDSRECORDER_SRCS))), $(DDSRECORDER_OUTDIR_DEBUG)/$(dep))
DDSRECORDER_OBJS_RELEASE = $(foreach obj,$(notdir $(addsuffix .o, $(DDSRECORDER_SRCS))), $(DDSRECORDER_OUTDIR_RELEASE)/$(obj))
DDSRECORDER_DEPS_RELEASE = $(foreach dep,$(notdir $(addsuffix .d, $(DDSRECORDER_SRCS))), $(DDSRECORDER_OUTDIR_RELEASE)/$(dep))

OBJS+= $(DDSRECORDER_OBJS_DEBUG) $(DDSRECORDER_OBJS_RELEASE)
DEPS+= $(DDSRECORDER_DEPS_DEBUG) $(DDSRECORDER_DEPS_RELEASE)

.PHONY: DDSRecorder checkDDSRecorderDirectories

DDSRecorder: checkDDSRecorderDirectories $(DDSRECORDER_TARGET_DEBUG) $(DDSRECORDER_TARGET)

checkDDSRecorderDirectories:
	@mkdir -p $(OUTDIR)
	@mkdir -p $(DDSRECORDER_OUTDIR)
	@mkdir -p $(DDSRECORDER_OUTDIR_DEBUG)
	@mkdir -p $(DDSRECORDER_OUTDIR_RELEASE)
	@mkdir -p lib
	@mkdir -p lib/$(EPROSIMA_TARGET)

$(DDSRECORDER_TARGET_DEBUG): $(DDSRECORDER_OBJS_DEBUG)
	$(LN) $(LDFLAGS) -o $(DDSRECORDER_TARGET_DEBUG) $(LIBRARY_PATH) $(DDSRECORDER_LIBS_DEBUG) $(DDSRECORDER_OBJS_DEBUG) $(DDSRECORDER_STATIC_LIBS)

$(DDSRECORDER_TARGET): $(DDSRECORDER_OBJS_RELEASE)
	$(LN) $(LDFLAGS) -o $(DDSRECORDER_TARGET) $(LIBRARY_PATH) $(DDSRECORDER_LIBS_RELEASE) $(DDSRECORDER_OBJS_RELEASE) $(DDSRECORDER_STATIC_LIBS)

vpath %.c $(DDSRECORDER_SOURCES_DIRS)
vpath %.cpp $(DDSRECORDER_SOURCES_DIRS)

$(DDSRECORDER_OUTDIR_DEBUG)/%.o:%.c
	@echo Calculating dependencies \(DEBUG mode\) $<
	@$(CC) $(DDSRECORDER_CFLAGS_DEBUG) -MM $(DDSRECORDER_INCLUDE_DIRS) $< | sed "s/^.*:/$(DDSRECORDER_SED_OUTPUT_DIR_DEBUG)\/&/g" > $(@:%.o=%.d)
	@echo Compiling \(DEBUG mode\) $<  
	@$(CC) $(DDSRECORDER_CFLAGS_DEBUG) $(DDSRECORDER_INCLUDE_DIRS) $< -o $@

$(DDSRECORDER_OUTDIR_RELEASE)/%.o:%.c
	@echo Calculating dependencies \(RELEASE mode\) $<
	@$(CC) $(DDSRECORDER_CFLAGS) -MM $(DDSRECORDER_CFLAGS) $(DDSRECORDER_INCLUDE_DIRS) $< | sed "s/^.*:/$(DDSRECORDER_SED_OUTPUT_DIR_RELEASE)\/&/g" > $(@:%.o=%.d)
	@echo Compiling \(RELEASE mode\) $<
	@$(CC) $(DDSRECORDER_CFLAGS) $(DDSRECORDER_INCLUDE_DIRS) $< -o $@

$(DDSRECORDER_OUTDIR_DEBUG)/%.c.o:%.c
	@echo Calculating dependencies \(DEBUG mode\) $<
	@$(CC) $(DDSRECORDER_CFLAGS_DEBUG) -MM $(DDSRECORDER_INCLUDE_DIRS) $< | sed "s/^.*:/$(DDSRECORDER_SED_OUTPUT_DIR_DEBUG)\/&/g" > $(@:%.o=%.d)
	@echo Compiling \(DEBUG mode\) $<  
	@$(CC) $(DDSRECORDER_CFLAGS_DEBUG) $(DDSRECORDER_INCLUDE_DIRS) $< -o $@

$(DDSRECORDER_OUTDIR_RELEASE)/%.c.o:%.c
	@echo Calculating dependencies \(RELEASE mode\) $<
	@$(CC) $(DDSRECORDER_CFLAGS) -MM $(DDSRECORDER_CFLAGS) $(DDSRECORDER_INCLUDE_DIRS) $< | sed "s/^.*:/$(DDSRECORDER_SED_OUTPUT_DIR_RELEASE)\/&/g" > $(@:%.o=%.d)
	@echo Compiling \(RELEASE mode\) $<
	@$(CC) $(DDSRECORDER_CFLAGS) $(DDSRECORDER_INCLUDE_DIRS) $< -o $@

$(DDSRECORDER_OUTDIR_DEBUG)/%.cpp.o:%.cpp
	@echo Calculating dependencies \(DEBUG mode\) $<
	@$(CPP) $(DDSRECORDER_CFLAGS_DEBUG) -MM $(DDSRECORDER_INCLUDE_DIRS) $< | sed "s/^.*:/$(DDSRECORDER_SED_OUTPUT_DIR_DEBUG)\/&/g" > $(@:%.o=%.d)
	@echo Compiling \(DEBUG mode\) $<
	@$(CPP) $(DDSRECORDER_CFLAGS_DEBUG) $(DDSRECORDER_INCLUDE_DIRS) $< -o $@

$(DDSRECORDER_OUTDIR_RELEASE)/%.cpp.o:%.cpp
	@echo Calculating dependencies \(RELEASE mode\) $<
	@$(CPP) $(DDSRECORDER_CFLAGS) -MM $(DDSRECORDER_CFLAGS) $(DDSRECORDER_INCLUDE_DIRS) $< | sed "s/^.*:/$(DDSRECORDER_SED_OUTPUT_DIR_RELEASE)\/&/g" > $(@:%.o=%.d)
	@echo Compiling \(RELEASE mode\) $<
	@$(CPP) $(DDSRECORDER_CFLAGS) $(DDSRECORDER_INCLUDE_DIRS) $< -o $@



