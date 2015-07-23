//===========================================================================
//
//  XMMLIB.CPP -- XMM API routines, Copyright 1994, Paul Chang
//
//---------------------------------------------------------------------------
//
//  Credit:
//
//    This code was developed based on the XMS version 2.0 specification,
//	copyright (c) 1988, Microsoft Corporation, Lotus Development
//	Corporation, Intel Corporation, and AST Research, Inc.
//
//---------------------------------------------------------------------------
//
//  Legal speak:
//
//    This code is public domain and free, and may be distributed free of any
//	charge or royalty, in the spirit of free software.
//
//    All code, including source, object, and executable, may be used, free
//	of any charge and royalty, provided that the developer gives credit
//	to the original author should any of said code be used in either
//	public domain or commercial software products.
//
//    The developer may use this code with the understanding that the
//	original author is in no way held responsible for any damage that may
//	arise from usage of any of said code.
//
//    Usage of said code includes incorporation into larger programs,
//	possible alteration of original code, and redistribution.
//
//---------------------------------------------------------------------------
//
//  Translation:
//
//    You can give this code away for free because this code is free.
//
//    You can use this code for free, but if you decide to build something
//	useful with it, give me some credit, will you?
//
//    If you use this code and it somehow screws you or your system over,
//	I'm not responsible, because I told you so.  Besides, I'm too poor
//	to be sued.
//
//    You can compile stuff with this code, you can even change this code,
//	and you can redistribute it, as long as you play nice and give me
//	some credit.
//
//---------------------------------------------------------------------------
//
//  Why is this freeware?
//
//    Because I doubt that anything I write could be commercially successful.
//	Besides, I have a job that feeds me, so I don't really need your
//	money.
//
//  Why do I include source code?
//
//    Because I know how frustrating it is to link a library without having
//	the ability to look at the source code.
//
//  Why do I give you permission to alter code?
//
//    Because I know how frustrating it is to link a library without having
//	the ability to alter the source code.
//
//  Why do I want you to give me some credit?
//
//    Because I've spent some time on this code, and I'd like to be
//	recognized for that effort if you choose to use it.
//
//  Why is this written in C++?
//
//    Because I hate C.  Besides, double-slash comments are nice.  If you
//	don't like it, tough -- try writing your OWN XMM library then.
//
//===========================================================================

#ifndef _XMMLIB_CPP
#define _XMMLIB_CPP

#include "xmmlib.h"

//===========================================================================
//
//  Global Variables
//
//===========================================================================

const char XMMLIB_Version[] = "XMMLIB Version 1.0 Beta";  //  XMMLIB version

//  XMM_GetControl() finds the 32-bit address of the XMM control function
//    and places it here

dword XMM_Control = 0;		//  Stores address of XMM control function

//  XMM_GetVersion() finds the 16-bit BCD version of the XMM and places it
//    in XMM_Version and, in string form, in XMM_VerString

word XMM_Version = 0;		//  16-bit BCD of XMM version
char XMM_VerString[] = "00.00";	//  String contains XMM version

//  Believe it or not, XMM_GetVersion() finds out if the HMA is available and
//    reports it with this global variable

word XMM_HMA = 0;		//  Contains 1 if HMA is available

//  I was going to declare this as a far pointer to something allocated from
//    the heap, but when I load DS:SI with the address of XMM_MoveStruct, I
//    can't make a "call [XMM_Control]" because XMM_Control is in the data
//    segment, while things in the heap are often in a different segment.  In
//    other words, XMM_MoveStruct and XMM_Control should be in the same
//    segment, or else bad things will happen (program crash).

XMM_Move XMM_MoveStruct;	//  Contains move information

//===========================================================================
//
//  Function Declarations
//
//===========================================================================

//---------------------------------------------------------------------------
//
//  XMM_Installed()
//
//    Returns 1 if an XMM exists, 0 otherwise
//
//---------------------------------------------------------------------------

byte XMM_Installed()
{
    byte RetVal;

    asm {
	mov	ax, XMM_INSTALL			// Test for XMM
	int	XMM_CALL
	mov	RetVal, al
    }

    if (RetVal == XMM_INSTALLED) {
	return(TRUE);
    } else {
	return(FALSE);
    }
}

//---------------------------------------------------------------------------
//
//  XMM_GetControl()
//
//    Returns address of XMM control function
//
//    XMM_Control contains XMM control function 32-bit address
//
//---------------------------------------------------------------------------

dword XMM_GetControl()
{
    asm {
	push	es
	mov	ax, XMM_CONTROL			//  Get Control Function
	int	XMM_CALL
	mov	word ptr [XMM_Control], bx	//  Standard Intel LE
	mov	word ptr [XMM_Control+2], es	//    Segment:Offset notation
	pop	es
    }

    return(XMM_Control);
}

//---------------------------------------------------------------------------
//
//  XMM_GetVersion()
//
//    Returns 16-bit BCD of XMM version, or 0 if XMM_Control is 0
//
//    XMM_Version contains 16-bit BCD of XMM version
//    XMM_HMA contains 1 if HMA exists, 0 otherwise
//
//---------------------------------------------------------------------------

word XMM_GetVersion()
{
    if (XMM_Control == 0) {
	return(0);
    }

    asm {
	mov	ah, XMM_GET_VERSION
	call	[XMM_Control]
	mov	XMM_HMA, dx
	mov	XMM_Version, bx
    }

    return(XMM_Version);
}

//---------------------------------------------------------------------------
//
//  XMM_GetVerHigh()
//  XMM_GetVerLow()
//  XMM_GetVerString()
//
//    XMM_GetVerHigh() returns the whole part of the XMM version number
//    XMM_GetVerLow() returns the fractional part of the XMM version number
//    XMM_GetVerString() updates XMM_VerString with the XMM version number,
//	and returns that string
//
//    All three functions call upon XMM_GetVersion() if it XMM_Version is 0
//
//---------------------------------------------------------------------------

int XMM_GetVerHigh()
{
    if (XMM_Version == 0) {
	XMM_GetVersion();
    }

    return(((XMM_Version >> 12) & 0x0f) * 10 + ((XMM_Version >> 8) & 0x0f));
}

int XMM_GetVerLow()
{
    if (XMM_Version == 0) {
	XMM_GetVersion();
    }

    return(((XMM_Version >> 4) & 0x0f) * 10 + (XMM_Version & 0x0f));
}

char* XMM_GetVerString()
{
    int index;

    if (XMM_Version == 0) {
	XMM_GetVersion();
    }

    index = 0;
    XMM_VerString[index] = ((XMM_Version >> 12) & 0x0f) + '0';
    if (XMM_VerString[index] != '0') {
	index ++;
    }
    XMM_VerString[index ++] = ((XMM_Version >> 8) & 0x0f) + '0';
    XMM_VerString[index ++] = '.';
    XMM_VerString[index ++] = ((XMM_Version >> 4) & 0x0f) + '0';
    XMM_VerString[index ++] = (XMM_Version & 0x0f) + '0';
    XMM_VerString[index] = 0;

    return(XMM_VerString);
}

//---------------------------------------------------------------------------
//
//  XMM_Initialize()
//
//    Calls upon XMM_Installed(), XMM_GetControl(), and XMM_GetVersion()
//
//    Returns XMM_Control if successful, 0 othersize
//
//    It is highly suggested that XMM_Initialize() be called before anything
//	else.  If you don't, your system WILL crash.
//
//---------------------------------------------------------------------------

dword XMM_Initialize()
{
    if (XMM_Installed() == 0) {
	return(0);
    }

    if (XMM_GetControl() == 0 || XMM_GetVersion() == 0) {
	return(0);
    }

    return(XMM_Control);
}

//---------------------------------------------------------------------------
//
//  XMM_QueryTotalFree()
//
//    Returns total XMS memory available in kilobytes
//
//---------------------------------------------------------------------------

word XMM_QueryTotalFree()
{
    word TotalFree;

    asm {
	mov	ah, XMM_QUERY_FREE
	call	[XMM_Control]
	mov	TotalFree, dx
    }

    return(TotalFree);
}

//---------------------------------------------------------------------------
//
//  XMM_QueryTotalFree()
//
//    Returns largest extended memory block (EMB) available in kilobytes
//
//---------------------------------------------------------------------------

word XMM_QueryLargestFree()
{
    word LargestFree;

    asm {
	mov	ah, XMM_QUERY_FREE
	call	[XMM_Control]
	mov	LargestFree, ax
    }

    return(LargestFree);
}

//---------------------------------------------------------------------------
//
//  XMM_AllocateBlock(size)
//
//    Allocates EMB in size kilobytes and returns the handle to the EMB
//
//---------------------------------------------------------------------------

word XMM_AllocateBlock(word size)
{
    word handle;

    asm {
	mov	dx, size
	mov	ah, XMM_ALLOCATE_BLOCK
	call	[XMM_Control]
	mov	handle, dx
    }

    return(handle);
}

//---------------------------------------------------------------------------
//
//  XMM_FreeBlock(handle)
//
//    Frees EMB of particular handle
//
//    Returns 0 upon success, errorcode otherwise
//
//---------------------------------------------------------------------------

byte XMM_FreeBlock(word handle)
{
    word RetVal;
    byte ErrorCode;

    asm {
	mov	dx, handle
	mov	ah, XMM_FREE_BLOCK
	call	[XMM_Control]
	mov	RetVal, ax
	mov	ErrorCode, bl
    }

    if (RetVal == 0) {
	return(ErrorCode);
    } else {
	return(0);
    }
}

//---------------------------------------------------------------------------
//
//  XMM_MoveMemory(length, srchnd, srcoff, dsthnd, dstoff)
//
//    Move memory to and from an EMB
//
//    Returns 1 upon success, 0 otherwise
//
//    XMM_MoveStruct is updated to hold move information
//	XMM_Move structure is defined in xmmlib.h
//
//    Note:  You need not lock a block first before moving memory
//
//---------------------------------------------------------------------------

word XMM_MoveMemory(dword length,
		    word srchnd, dword srcoff,
		    word dsthnd, dword dstoff)
{
    word MoveStructOff = FP_OFF(&XMM_MoveStruct);
    word RetVal;

    XMM_MoveStruct.Length = length;
    XMM_MoveStruct.SourceHandle = srchnd;
    XMM_MoveStruct.SourceOffset = srcoff;
    XMM_MoveStruct.DestHandle = dsthnd;
    XMM_MoveStruct.DestOffset = dstoff;

    asm {
	mov	si, MoveStructOff
	mov	ah, XMM_MOVE_MEMORY
	call	[XMM_Control]
	mov	RetVal, ax
    }

    return(RetVal);
}

//---------------------------------------------------------------------------
//
//  XMM_LockBlock(handle)
//
//    Locks a particular EMB
//
//    Returns DWORD containing 32-bit physical address of block, 0 if failure
//
//    Note:  You don't need to lock a block to call upon XMM_MoveMemory()
//
//---------------------------------------------------------------------------

dword XMM_LockBlock(word handle)
{
    word EMBSeg;
    word EMBOff;
    word RetVal;

    asm {
	mov	dx, handle
	mov	ah, XMM_LOCK_BLOCK
	call	[XMM_Control]
	mov	RetVal, ax
	mov	EMBSeg, dx
	mov	EMBOff, bx
    }

    if (RetVal == 0) {
	return(0);
    }

    return(((dword) EMBSeg << 16) + EMBOff);
}

//---------------------------------------------------------------------------
//
//  XMM_UnlockBlock(handle)
//
//    Unlocks a particular EMB
//
//    Returns 1 upon success, 0 otherwise
//
//---------------------------------------------------------------------------

word XMM_UnlockBlock(word handle)
{
    word RetVal;

    asm {
	mov	dx, handle
	mov	ah, XMM_UNLOCK_BLOCK
	call	[XMM_Control]
	mov	RetVal, ax
    }

    return(RetVal);
}

//---------------------------------------------------------------------------
//
//  XMM_LockCount(handle)
//
//    Returns the number of locks on a particular EMB, -1 upon failure
//
//---------------------------------------------------------------------------

int XMM_LockCount(word handle)
{
    word RetVal;
    byte LockCount;

    asm {
	mov	dx, handle
	mov	ah, XMM_GET_HANDLE_INFO
	call	[XMM_Control]
	mov	RetVal, ax
	mov	LockCount, bh
    }

    if (RetVal == 0) {
	return(-1);
    }

    return((int) LockCount);
}

//---------------------------------------------------------------------------
//
//  XMM_NumHandles(handle)
//
//    Returns the number of handles left for EMBs, -1 upon failure
//
//    Don't ask me why you need to pass a handle to obtain the number of free
//	handles
//
//---------------------------------------------------------------------------

int XMM_NumHandles(word handle)
{
    word RetVal;
    byte NumHandles;

    asm {
	mov	dx, handle
	mov	ah, XMM_GET_HANDLE_INFO
	call	[XMM_Control]
	mov	RetVal, ax
	mov	NumHandles, bl
    }

    if (RetVal == 0) {
	return(-1);
    }

    return((int) NumHandles);
}

//---------------------------------------------------------------------------
//
//  XMM_BlockSize(handle)
//
//    Returns the length of a perticular block, 0 upon failure
//
//    Don't ask me why you need to pass a handle to obtain the number of free
//	handles
//
//---------------------------------------------------------------------------

word XMM_BlockSize(word handle)
{
    word RetVal;
    word BlockLength;

    asm {
	mov	dx, handle
	mov	ah, XMM_GET_HANDLE_INFO
	call	[XMM_Control]
	mov	RetVal, ax
	mov	BlockLength, dx
    }

    if (RetVal == 0) {
	return(0);
    }

    return(BlockLength);
}

//---------------------------------------------------------------------------
//
//  XMM_ReallocateBlock(handle, length)
//
//    Tries to reallocate block to size length (in kilobytes)
//
//    Returns 1 upon success, 0 otherwise
//
//    If length is smaller than original size, data will be truncated
//    Block must be unlocked before reallocation
//
//---------------------------------------------------------------------------

word XMM_ReallocateBlock(word handle, word length)
{
    word RetVal;

    asm {
	mov	dx, handle
	mov	bx, length
	mov	ah, XMM_REALLOC_BLOCK
	call	[XMM_Control]
	mov	RetVal, ax
    }

    return(RetVal);
}

//---------------------------------------------------------------------------
//
//  XMM_memcpy(<destination>, <source>, n)
//
//    Calls upon XMM_MoveMemory()
//
//    These four overloaded functions provide the API to copy data between
//	conventional memory and EMBs.  If the data location is in the EMB,
//	a handle and offset are necessary;  otherwise, just a far pointer
//	is sufficient for conventional memory.
//
//    Returns 1 upon success, 0 otherwise
//
//---------------------------------------------------------------------------

word XMM_memcpy(word dsthnd, dword dstoff,
		word srchnd, dword srcoff,
		dword n)
{
    return(XMM_MoveMemory(n, srchnd, srcoff, dsthnd, dstoff));
}

word XMM_memcpy(word dsthnd, dword dstoff,
		byte far* source,
		dword n)
{
    word srchnd = 0;
    dword srcoff = MK_DWORD(source);

    return(XMM_MoveMemory(n, srchnd, srcoff, dsthnd, dstoff));
}

word XMM_memcpy(byte far* dest,
		word srchnd, dword srcoff,
		dword n)
{
    word dsthnd = 0;
    dword dstoff = MK_DWORD(dest);

    return(XMM_MoveMemory(n, srchnd, srcoff, dsthnd, dstoff));
}

word XMM_memcpy(byte far* dest, byte far* source, dword n)
{
    word srchnd = 0;
    dword srcoff = MK_DWORD(source);
    word dsthnd = 0;
    dword dstoff = MK_DWORD(dest);

    return(XMM_MoveMemory(n, srchnd, srcoff, dsthnd, dstoff));
}

#endif _XMMLIB_CPP

