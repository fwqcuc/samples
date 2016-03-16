# 软件安全方向能力清单，在开发能力清单基础上。

## Windows系统安全
* HeapAlloc HeapFree函数
* FindFirstFile FindNextFile
* ToolHelper，列举线程、进程。
* 编写Dll、导出指定的函数，并在Exe中调用导出函数。
* dupmbin PE文件结构。
* VirtualAlloc等虚拟内存管理相关函数，尤其是VitrulProtect。
* ImageHelper
* Message Hook
* tiny pe相关技术
* PEB \ TEB 编程访问PEB和TEB，并打印出各个成员变量的内容，了解各成员变量的意义。
* 虚拟内存管理的底层机制，分页机制，ring0，系统寄存器。
* 通过导入表导出表获得API函数的地址。
* API hook进行文件和进程隐藏。
* Copy On Write
* 通过PEB \ TEB 获取API函数在内存中的地址。
* 完成一次实战的漏洞的利用。（TODO哪个漏洞？)
* 编写sys，验证Copy On Write。
* 使用DKOM方式隐藏进程和文件。
* 使用NtAPI hook方式隐藏文件和进程。
* 使用过滤驱动实施包过滤。
* 使用过滤驱动实施文件隐藏。
* 使用windbg双机内核调试，虚拟机环境配置，加载系统符号文件。
* 使用Windbg等工具单步跟踪程序执行。


## 漏洞攻防
* 缓冲区溢出攻击——给定示例，通过输入控制EIP寄存器的值。
* 编写shellcode
* 使用C语言编写shellcode
