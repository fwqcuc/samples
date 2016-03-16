# 开发能力清单

## C语言

* 变量
* 数据类型
* 函数
* 语句
* 函数调用、参数、返回值
* 赋值语句
* 流程控制语句
* 数学运算
* 逻辑运算
* 位运算
* 结构体
* 枚举类型
* typedef
* 定义和声明的区别
* 头文件和源文件的区别、跨文件函数调用
* 预编译处理、宏和常量 #include #define 
* 条件编译 #if #ifdef #endif等
* 指针、内存地址，理解一切都在内存中，指针既内存地址。
* 取地址操作符 &
* 结构体指针类型成员访问 ->
* 函数指针、回调。
* 命令行和main函数参数的关系。

了解C语言的主要应用范围：Windows系统编程、Linux系统编程。


## 了解学习编程的技能象限

要完整的学会一门编程技术，必须是以下4个方面：
* 语言，比如C语言。
* 工具，会C语言语法是不够的，还必须熟练掌握编译链接器器、调试器、文本编辑器、IDE的使用。
* 平台机制，比如在Windows系统的应用程序，就必须掌握消息机制、回调、动态链接和DLL、进程、线程、多线程、线程同步等。
* 接口，程序运行的底层环境提供的接口函数，一般称为API，习称“库函数”。熟练使用API是提高编程效率的必要条件。
*　基本逻辑方法，比如MVC、比如封装。

因此学完C语言并不能成为一个合格的程序员。任何一门编程技术都是这样。

## 学会使用google
* 能上google
* 搜索特定站点
* 搜索特定文件类型
* 精确匹配
* 按时间排序
* 垂直搜索、分类搜索

## 操作系统的基本使用：Windows

* 任务管理器
* cmd.exe
* 系统自带实用工具 notepad calc
* 常用快捷键：WinKey系列等。
* 文件和路径
* 系统目录和系统文件的内容和功能
* 设备管理器、驱动程序安装
* 控制面板
* 环境变量
* PATH环境变量
* 常用系统命令 cd dir copy del mkdir set ipconfig ping netsh xcopy
* 批处理程序
* 安装系统更新
* 防火墙配置和操作 
* 设置、禁用启动项，让程序开机自启动。
* 修改注册表
* 在虚拟机中安装Windows
* 格式化硬盘、在物理机中安装Windows系统
* 修改启动参数
* 安全模式
* 制作启动U盘、使用U盘启动的运维系统，如WinPE.
* 硬盘分区和克隆
* 设置浏览器代理
* 修改组策略
* 通过命令行建用户
* 查看本机IP地址
* 设置静态IP地址和网关
* hosts文件
* dll文件和sys文件分别是什么
* MAX_PATH

## 操作系统的基本使用：Linux（常用Ubuntu）

* 打开shell，以及快捷键
* 常用命令 ls cd cp rm mkdir
* 用户、root用户、用户组、文件权限的管理方式、chmod
* apt-get、sources.list
* home目录是啥？
* 了解文件系统目录划分，各个系统目录的作用。/bin /dev /opt /var /etc /lib /mnt 都是啥。
* 在虚拟机中安装Linux服务器版本，并开放ssh服务。
* ssh
* 基于证书认证的ssh
* vim (这个可以单开一个专题)
* 让程序开机自启动
* gcc/make，使用源码安装软件。


## 工具：Viusual Studio 技能
* 建立空工程
* 添加源码到工程。添加.c文件到工程
* 成功build得到exe文件。
* 在release和debug配置下均编译成功，并得到可执行程序。
* 编译得到x64版本的可执行程序。
* sln文件和vcxproj文件的关系和作用。
* 使用文本编辑器查看 sln 文件和vcxproj文件，并理解其中的内容，并对应IDE中的显示。
* 找到 Visual Studio Command Prompt，并通过cl和link得到所手工编译链接代码得到可执行程序。
* 观察 Visual Studio Command Prompt 和直接运行cmd环境变量的不同。
* TOOL->exterl tool中找到Visual Studio Command Prompt 的启动命令，并分析原理。
* obj文件的作用。
× 常用编译选项及其作用 /nologo /c /GS /MT /MD /ZI /Od /Fo /D 观察修改这些编译选型以后的变化。
* 常用链接选项及其作用 /OUT /PDB /NOLOGO /MACHINE: /SUBSYSTEM: /DEBUG 以及obj和lib输入文件。
* 在vs工程中修改编译链接选项，在命令中调用cl和link时设置不同的编译链接选项。
* 将链表源代码（贪吃蛇）文件编译为lib
* LNK2019错误的排除。
* 其他常见编译链接错误的排除（TODO)
* 启动调试
* 设置调试执行时程序的启动参数。
* 下断点
* 单步执行
* 程序中断时，查看变量值。
* 查看指针值，并在内存查看窗口中查看内存中的值。
* 反汇编，并观察C代码和汇编代码的对应关系
* 反汇编状态下单步执行，并观察寄存器的变化。
* 观察call stack
* 修改代码编辑器字体
* 搜索和替换
* 注释和取消注释快捷键、大小写转换快捷键、代码整理快捷键。
* 代码自动不全相关快捷键
* 调试相关的快捷键
* 建立makefile工程，并使用makefile编译工程。
* 使用nmake编译链接得到可执行程序
* 阅读和分析所给的makefile

## 网络

* wireshark抓包，通过规则进行包过滤
* socket server / client 程序编写，使用TCP传输数据和文件。
* 从抓包数据中过滤出自行编写的socket程序的收发包，并能清楚各类数据包和socket函数调用的对应关系。
* 通过抓包理解TCP三次握手、滑动窗口、基于连接的传输。并能解析包层次结构。
* 内存结构化数据的序列化和反序列化：将一个带有指针类型的结构体数据发送到远程主机。
* 多线程socket server 并发处理多个客户端的链接。
* ICMP IP TCP UDP HTTP SMTP 各自位于7层模型的哪一层。
* HTTP 会话过程。
* URL的构成
* GET 和 POST请求。
* 使用curl和libcurl发送HTTP请求获得返回结果。
* 抓包对比HTTP和HTTPS
* 在Linux系统中搭建HTTP服务器（Appache、Nigix）并能通过浏览器成功访问。


## Windows系统编程基础（软件安全方向必学）
* typedef和Windows Data Type
* WinMain入口函数
* API概念
* 函数调用方式
* MSDN的使用
* 创建窗口
* 消息循环、消息队列、消息处理回调函数
* CreateFile 、ReadFile、WriteFile、CloseHandle
* 系统对象和Handle
* 控件，创建控件、设置控件大小位置等属性、控件的父窗口处理NOTIFY\COMMAND消息，通过宏和SendMessage控制消息。
* CreateThread
* Event\Mutex
* CreateProcess
* ANSI和Unicode字符编码、UNICODE宏定义和条件编译（及VS工程配置）、A和W版本的字符串函数。字符编码转换函数。


## Linux系统编程入门（软件安全方向必学）
* linux下的socket程序
* getopt
* fork、pthread

## 工具：Gcc、Gdb、make（软件安全方向必学）
* 使用源码安装软件。
* 使用gcc编译源码。
* 编写makefile。


## python——最方便的脚本，提高你的工作效率
语法
工具
库

## HTTP/javasrcipt/html/html5 (互联网应用开发前端必学)
TODO 粗线条待补充
HTTP
API
JSON
XML
curl

## LNMP--Linux/Nigix/MySql/PHP （互联网应用开发后端必学）
TODO 粗线条待补充
HTTP
API
JSON
XML
安装Nigix
配置Nigix
安装Mysql
安装php开发环境
编写sql语句


