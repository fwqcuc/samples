## exe程序
* 根据目标进程的进程名，获得了进程句柄 OpenProcess，有了进程句柄就可以对目标进程实施后续操作。
* 使用VirtualAllocEx给目标进程分配了一段内存。
* 使用WriteProcessMemory给目标进程写入了一段数据，这里只需写入需要目标进程加载的dll名称，作为创建远程线程时的参数。
* 使用CreateRemoteThread，在目标进程中创建一个线程，运行一段程序。目标进程是被动运行的程序。
* 所运行的程序是LoadLibraryA。在第3部还有一个准备工作，是获得LoadLibraryA函数的地址，使得CreateRemoteThread的参数可以正确设置。
* 这里有一个假设：本exe程序进程中的LoadLibraryA函数的地址和目标进程中的是一个虚拟地址。只有这个假设成立的时候，才直接可以创建LoadLibraryA线程。


## dll程序
### 实施IAT hook.
* 编写一个假的被替换函数，需要调用真的目标函数去获得真的信息。在真信息的基础上实施篡改或截获。
* 通过ImageHlp系列函数查找IAT，找到目标函数指针在IAT中的位置。
* 使用假函数替换IAT中的目标函数指针。替换之前，需要使用VitrualProctect函数修改内存的属性，由只读，变为可写。
* 注意通过GetLastError和SetLastError函数将系统的错误代码修改正确。
