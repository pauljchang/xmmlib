# xmmlib
An ancient XMS library I wrote back in 1994 in C++ and assembly

Edited the original README.TXT

## XMMLIB 1.0 Beta -- Copyright 1994, Paul Chang

* XMMLIB is freeware.
* This code is public domain and free, and may be distributed free of any charge or royalty, in the spirit of freeware.
* All code, including source, object, and executable, may be used, free of any charge and royalty, provided that the developer gives credit to the original author should any of said code be used in either public domain or commercial software products.
* The developer may use this code with the understanding that the original author is in no way held responsible for any damage that may arise from usage of any of said code.
* Usage of said code includes incorporation into larger programs, possible alteration of original code, and redistribution.


## Files Included

File Name | Description
--------- | -----------
XMMLIB.OBJ | Object code.  Include this in your makefile.
XMMLIB.H | Header file.  Include this in your source.
XMMLIB.CPP | Source code.
XMMTEST.OBJ | Object code for example program.
XMMTEST.CPP | Source code for it.
XMMTEST.EXE | The example program itself.
XMMLIB.TXT | This file, you dumbass.


## Development System

This code was developed on a 486 DX/33 with himem.sys version 3.09 of the extended memory manager.  The code has also been tested within Windows 3.1, which emulates version 2.0 of XMS in a DOS box.  The code was written with Borland C++ 4.0, compiled under the large memory model.

## Frequently (and Infrequently) Asked Questions

### What is XMMLIB?

XMMLIB is a set of functions that provide a simple API to the eXtended Memory Specification (XMS) functions, as described in XMS 2.0, copyright 1988, Microsoft Corporation, Lotus Development Corporation, Intel Corporation, and
AST Research, Inc.

### Okay, what is XMS?

XMS gives you the ability to access memory outside the conventional 640K imposed by DOS.  This includes Upper Memory Blocks (UMBs), memory between 640K and 1024K;  the High Memory Area (HMA), memory between 1024K and 1088K;  and
Extended Memory Blocks (EMBs), memory above 1088K.

### Why do I need this?

Because if you try to write a standard DOS program, it can't access more than 640K, even if you have oodles and oodles of memory in your machine.  DOS just won't let you.

### Why is DOS so stupid?

I don't know.  When the PC was originally introduced, a machine that came with 64K was really hot stuff.  So the designers said, okay, let's let this machine have a whole lot of memory, like, say, 640K!  This means it'll take
2.5 bytes to address it all, and we'll say that video drivers and stuff will exist between 640K and 1024K.  But 2.5 bytes of addressing is pretty weird, so let's say it's normally two bytes (called near addressing) within a segment, so that a segment can have 64K.  We'll call the address within the segment the offset.  And then let's use another two bytes for the segment address to address within 1024K, allowing segments to overlap.  That means the real address is the segment address shifted left four bits, plus the offset address. Pretty hokey, eh?

But that was a long time ago.  Today, you can do 32-bit protected mode programming, which is available on only 386 machines and above.

### Okay, then why don't you just do 32-bit protected mode programming?

Well, you can.  But I won't.

### Why?

Because I'm afraid of it.  You can learn how to from someone else, but right here, you've got the XMS.

### Wait!  You forgot EMS!

Oh, that.  (Groan.)  Okay, the Expanded Memory Specification (EMS) also gives you the same capabilities as XMS, but the structure is different.  In EMS, you map the physical expanded memory into small 16K windows somewhere in
upper memory.  So you kind of move your window around to look at all of the physical memory.  The problem with this is that you must use precious upper memory to do this, and upper memory is where you usually load drivers (unless it's full, in which case you'd be stuck stuffing them in conventional memory). And the API to EMS uses interrupt calls, which can be kind of slow.

### Okay, then I'm stuck with XMS for now.

Yup.

### So... how do I use it?

Do you know how to program in C++?

### Sure.

When you write your next "big" program that requires extended memory, just include the "xmmlib.h" header file and the "xmmlib.obj" object file.  All of the functions you need are prototyped in the header file.  I'd suggest using the large memory model, because all pointers become far pointers, and, in fact, the object code is compiled for that memory model.  If you choose to use a different memory model, recompile "xmmlib.cpp" and link "xmmlib.obj" into your program.

You probably need only use the basic functions, like XMM_Initialize(), XMM_AllocateBlock(), XMM_FreeBlock(), and XMM_memcpy(), which mimics regular _fmemcpy(), only with extended memory.

### Wait a minute...  How about the HMA, UMBs, and A20 line stuff?

Sorry, I only implemented the EMB portion of the XMS.  I figured that if I could access EMBs, that'd be all I need.  Besides, EMBs consist of all memory above 1088K, while the HMA is only 64K and the UMBs are only 384K at most.  The A20 line is the 21st addressing line used to access the HMA.  If you don't know what it is or how to use it, don't.

### So... can I include your source code?

Sure, I don't care.  I know how frustrating it is to use a library without being able to see the source code, so I've included it here.  Just give me some credit (no money) if you decide to use this.

### All right...  can I... change your code too?  I don't like some of it.

I'll admit I'm not a perfect programmer, so sure, I don't care.  I know how frustrating it is to use a library without being able to change the source code, so I'm giving you permission to do so.  As long you give me some credit, I'll be happy.

### I can use your code, I can alter it... for free?  What's the catch?

No catch.  This is freeware.  Use it as you wish.  Just give me some credit for the code that you do use, and if you distribute this archive, please include all the files, unaltered.

### Why did you write XMMLIB?

I wrote XMMLIB because I needed to access more memory than the pathetic 640K upper limit that DOS currently imposes.  I'm writing a game, and I can't seem to fit all the sprites that I need in memory (these are big sprites).

Actually, the truth is, I wrote XMMLIB because I received the XMS in the mail from Microsoft before I got the EMS from Intel.  If you want a copy of the XMS (free of charge), call Microsoft Customer Support.  Or, if you're a masochist and want the EMS (free of charge), call Intel Customer Support.

### Why is this freeware?

Because I don't need your money.  Besides, I doubt that anything that I write would be commercially successful.

### What is your favorite color?

I kind of like Teal-Gray, but I'll settle for California Navy Blue and Gold.

### Do you sleep with sheep?

Why, is your mother available?

### What do you do for a living?

I work.  I'm a programmer, working for an undisclosed firm.

### Mother, may I?

Ask your father, damn it!

### How do I get in contact with you?

You can e-mail me at:  ~~chang@alumni.eecs.berkeley.edu~~ (Yes, I'm a Cal grad) or ~~paulibus@rahul.net~~ (my internet service provider).

EDIT: pauljchang@gmail.com

You can send all comments, suggestions, fan mail, and death threats to the above addresses.  If you don't have internet access, well, tough beans.

### Release Information

Version | Release | Description
------- | ------- | -----------
0.1 Alpha | Prerelease | Basic XMS EMB functions are implemented, but no HMA, UMBs, or A20 line.
1.0 Beta | First release | I fixed up the documentation.
