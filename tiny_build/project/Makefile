

# 所有源文件列表
#### LIST ALL YOUR SOURCES FILE HERE ###
SOURCES = test_exe.c
ASM_SOURCES = 
RC_SOURCES = 

###### SET USE tiny pe BUILD OPTION; ###
###### TRUE or FALSE ###################
TINY_PE = TRUE

###### SET YOUR BIB FILE TYPE; #########
###### EXE DLL LIB or exe dll lib ######
TARGET_TYPE = exe

###### BIN FILE NAME ###################
###### 如果留空，则使用ProjectName   #####
TARGET = 

###### 编译链接选项 #####################

### cl.exe options
CFLAGS = /D "WIN32" /Gy /GS- /MT
### ml.exe or ml64.exe options
ASMFLAGS = 
### rc.exe options
RCFLAGS = 

### 自定义库文件，本project用到的本sln中的lib
MY_LIBS = 

### 系统库文件
SYS_LIBS = kernel32.lib user32.lib


### link.exe options
LFLAGS = /SUBSYSTEM:CONSOLE


### lib.exe的参数 if TARGET_TYPE == lib 才用到。
LIB_OPTION =

###################################
!INCLUDE ..\Comm_MakeFile
