
# 设置源文件列表

SOURCES =

# 是否启用 tiny pe; TRUE or FALSE

TINY_PE = TRUE

# 设置 TARGET 

TARGET_DIR = ..\BUILD\$(Platform)\$(Configuration)
TARGET = 
TARGET_TYPE = lib

# 设置 LIB_OPTION 

!IF "$(Platform)"=="Win32"
LIB_OPTION = /MACHINE:x86 
!ELSEIF "$(Platform)"=="x64"
LIB_OPTION = /MACHINE:x64
!ENDIF

LIB_OPTION = $(LIB_OPTION) /def:msvcrt.def


CFLAGS = 
MY_LIBS = 
SYS_LIBS = 
LFLAGS =


# 引入 ..\Comm_MakeFile
!INCLUDE ..\Comm_MakeFile
