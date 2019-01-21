## File IO

Memory is great and all, but what happens when you want something less volatile? You use the disk of course!

### In this tutorial we will...
* Discuss elements of the Linux file system
* Cover Linux system calls (open, read, write, seek, and close)
* Cover c library calls with FILE pointers

#### The Linux File System

A few things to know:
* Everything in Linux is either a file or a directory.
* Every directory has a "." member which references itself, and a "../" member which references its parent directory
* A directory can have an infinite amount of children (without factoring disk space or set system limits)
* There are some special types of files suchas character or block files, but everything is still a file or directory
* The Linux kernel provides system calls in order to interact with the base OS
* These system calls allow us to do operations on the file system from within a program
* "C" is the api for these system calls. "C" also provides a set of functions that make the system calls easier to use

#### System Calls

System calls provide a doorway to the operating system. Through them you can retrieve file info, remove or add files, create or destroy processes, display stuff on screen, communicate over the network, notify other processes, and even control devices. In this tutorial we will learn about file system calls, which are open, close, write, read, and seek. These form the basis of all disk operations performed.

#### File IO Concepts

* Processes do **not** own files. They simply hold a "pointer" to them. The kernel is the true owner of all files
* Processes obtain something called a *file descriptor* which points to a table in the kernel. This table then points to the actual files. (Two levels of indirection)
* Files are stored as iNodes, which represent info about the file on the disk. 
