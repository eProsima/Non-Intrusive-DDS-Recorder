bin_PROGRAMS = ddsrecorder
ddsrecorder_SOURCES = src/log/eProsimaLog.cpp \
					  src/reader/pcapReader.cpp \
					  src/reader/ipDefragmenter.cpp \
					  src/RTPSPacketAnalyzer.cpp \
					  src/DDSRecorder.cpp \
					  src/database/TypeCodeDB.cpp \
					  src/database/EntitiesDB.cpp \
					  src/database/DynamicDataDB.cpp \
					  src/cdr/ArrayTypeCode.cpp \
					  src/cdr/ContentTypeCode.cpp \
					  src/cdr/EnumTypeCode.cpp \
					  src/cdr/MemberedTypeCode.cpp \
					  src/cdr/PrimitiveTypeCode.cpp \
					  src/cdr/SequenceTypeCode.cpp \
					  src/cdr/StringTypeCode.cpp \
					  src/cdr/StructTypeCode.cpp \
					  src/cdr/TypeCode.cpp \
					  src/cdr/UnionTypeCode.cpp \
					  src/cdr/TypeCodeCopy.cpp \
					  src/util/IDLPrinter.cpp \
					  src/main.cpp \
					  src/idlparser/IDLParser.cc \
					  src/idlparser/IDLScanner.cc \
					  src/idlparser/UserTypeCodeProvider.cpp 

ddsrecorder_LDFLAGS = -lfastcdr -lpcap -lsqlite3 -lboost_system

AM_CPPFLAGS = -std=c++0x -DSQLITE_PREPARE_V2 -Iinclude

ddsrecorder_licenciasdir = $(datadir)/doc/ddsrecorder
ddsrecorder_licencias_DATA = DDSRECORDER_LICENSE.txt LGPLv3_LICENSE.txt

install-data-hook:
	mkdir -p $(DESTDIR)$(datadir)/doc/ddsrecorder; \
	cp -r doc/* $(DESTDIR)$(datadir)/doc/ddsrecorder; \
	mkdir -p $(DESTDIR)$(datadir)/ddsrecorder; \
	cp -r examples $(DESTDIR)$(datadir)/ddsrecorder/;

uninstall-hook:
	rm -r $(DESTDIR)$(datadir)/doc/ddsrecorder; \
	rm -r $(DESTDIR)$(datadir)/ddsrecorder
