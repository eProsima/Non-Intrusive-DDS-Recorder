AC_INIT([DDSRecorder], [VERSION], [support@eprosima.com], [ddsrecorder], [http://eprosima.com/])
AC_PREREQ([2.59])
AC_CHECK_HEADER([fastcdr/FastCdr_version.h],
	[AC_MSG_NOTICE([Found eProsima fastcdr])],
	[AC_MSG_ERROR([Could not find eProsima fastcdr])],
	[])
AM_INIT_AUTOMAKE([1.10 no-define foreign subdir-objects])
AC_PROG_CXX
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_FILES([Makefile])

# Check endianess
AC_C_BIGENDIAN(
  AC_DEFINE(__BIG_ENDIAN__, 1, [machine is bigendian]),
  AC_DEFINE(__LITTLE_ENDIAN__, 1, [machine is littleendian]),
  AC_MSG_ERROR(unknown endianess),
  AC_MSG_ERROR(universial endianess not supported)
)

AC_OUTPUT
