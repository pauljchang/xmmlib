//===========================================================================
//
//  XMMLIB.H -- Header file for XMMLIB routines, Copyright 1994, Paul Chang
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

#ifndef _XMMLIB_H
#define _XMMLIB_H

//---------------------------------------------------------------------------
//
//  XMM Function Numbers
//
//---------------------------------------------------------------------------

//  To check if XMM is installed, int 2Fh is called with AX=4300h and the
//  contents of AL are compared to 0x80.  This is confusing, because most XMM
//  functions return 0x80 when a particular function is not implemented.  To
//  obtain the address of the XMM control function, call int 2Fh once again,
//  only with AX=4310h, and the address of the XMM control function is
//  returned in ES:BX.  This control function is referenced in all subsequent
//  XMM API calls.

#define XMM_CALL		0x2f
#define XMM_INSTALL		0x4300
#define XMM_INSTALLED		0x80
#define XMM_CONTROL		0x4310

//  XMM control functions

#define XMM_GET_VERSION		0x00
#define XMM_REQUEST_HMA		0x01	//  Not implemented -- dangerous!
#define XMM_RELEASE_HMA		0x02	//  Not implemented -- dangerous!
#define XMM_ENABLE_A20		0x03	//  Not implemented -- dangerous!
#define XMM_DISABLE_A20		0x04	//  Not implemented -- dangerous!
#define XMM_LOC_ENABLE_A20	0x05	//  Not implemented -- dangerous!
#define XMM_LOC_DISABLE_A20	0x06	//  Not implemented -- dangerous!
#define XMM_QUERY_A20		0x07	//  Not implemented -- dangerous!
#define	XMM_QUERY_FREE		0x08
#define XMM_ALLOCATE_BLOCK	0x09
#define XMM_FREE_BLOCK		0x0A
#define XMM_MOVE_MEMORY		0x0B
#define XMM_LOCK_BLOCK		0x0C
#define XMM_UNLOCK_BLOCK	0x0D
#define XMM_GET_HANDLE_INFO	0x0E
#define XMM_REALLOC_BLOCK	0x0F
#define XMM_REQUEST_UMB		0x10	//  Not implemented -- I'm lazy!
#define XMM_RELEASE_UMB		0x11	//  Not implemented -- I'm lazy!
#define XMM_REALLOC_UMB		0X12	//  Not implemented -- I'm lazy!
#define XMM_SUPER_QUERY_FREE	0X88	//  Don't use Super XMS functions yet!
#define XMM_SUPER_ALLOCATE	0X89	//  Don't use Super XMS functions yet!
#define XMM_SUPER_GET_INFO	0X8E	//  Don't use Super XMS functions yet!
#define XMM_SUPER_REALLOC	0X8F	//  Don't use Super XMS functions yet!

//---------------------------------------------------------------------------
//
//  XMM error codes
//
//---------------------------------------------------------------------------

//  Most XMM functions will return an error code in BX if AX contains 0x0000,
//  signalling an error.  Otherwise, AX will usually return 0x0001.

#define XMM_NOT_IMPLEMENTED	0x80	//  Means function is not implemented
#define XMM_VDISK_DETECTED	0x81	//  Means VDISK was found
#define XMM_A20_ERROR		0x82	//  Means A20 error occurred
#define XMM_DRIVER_ERROR	0x8E	//  Means general driver error occurred
#define XMM_FATAL_ERROR		0x8F	//  Means unrecoverable driver error
#define XMM_NO_HMA		0x90	//  Means no HMA available
#define XMM_HMA_IN_USE		0x91	//  Means HMA already in use
#define XMM_DX_LESS_HMAMIN	0x92	//  Means DX < HMAMIN
#define XMM_HMA_NO_ALLOC	0x93	//  Means HMA was not allocated
#define XMM_A20_ENABLED		0x94	//  Means A20 line still enabled
#define XMM_NO_FREE_EMB		0xA0	//  Means all EMBs allocated
#define XMM_NO_FREE_HANDLE	0xA1	//  Means all handles allocated
#define XMM_INVALID_HANDLE	0xA2	//  Means invalid handle
#define XMM_BAD_SOURCE_HANDLE	0xA3	//  Means source handle is invalid
#define XMM_BAD_SOURCE_OFFSET	0xA4	//  Means source offset is invalid
#define XMM_BAD_DEST_HANDLE	0xA5	//  Means destination handle is invalid
#define XMM_BAD_DEST_OFFSET	0xA6	//  Means destination offset is invalid
#define XMM_BAD_LENGTH		0xA7	//  Means length is invalid
#define XMM_BAD_OVERLAP		0xA8	//  Means move has invalid overlap
#define XMM_PARITY_ERROR	0xA9	//  Means parity error occurred
#define XMM_BLOCK_NOT_LOCKED	0xAA	//  Means the block is not locked
#define XMM_BLOCK_LOCKED	0xAB	//  Means the block is locked
#define XMM_BLOCK_COUNT		0xAC	//  Means locked block count overflowed
#define XMM_LOCK_FAILED		0xAD	//  Means lock failed
#define XMM_SMALLER_UMB		0xB0	//  Means smaller UMB is available
#define XMM_NO_UMB		0xB1	//  Means no UMB available
#define XMM_BAD_UMB_SEG		0xB2	//  Means bad UMB segment number

//---------------------------------------------------------------------------
//
//  Macros
//
//---------------------------------------------------------------------------

//  Far pointer conversion macros were snarfed from Borland C++ dos.h file

#ifndef MK_FP
#  define MK_FP( seg,ofs )( (void _seg * )( seg ) + ( void near * )( ofs ))
#endif MK_FP

#ifndef FP_SEG
#  define FP_SEG( fp )( (unsigned )( void _seg * )( void far * )( fp ))
#endif FP_SEG

#ifndef FP_OFF
#  define FP_OFF( fp )( (unsigned )( fp ))
#endif FP_OFF

//  Used to turn far pointers into Intel LE 32-bit SEG:OFF far pointer

#define MK_DWORD( fp )( (dword) FP_SEG(( fp )) << 16) + FP_OFF(( fp ))

//  Do you like booleans?  I like booleans.

#ifndef TRUE
#  define TRUE	1
#endif TRUE

#ifndef FALSE
#  define FALSE 0
#endif FALSE

#ifndef MAYBE
#  define MAYBE Gee... uh... I dunno... maybe.
#endif MAYBE

//---------------------------------------------------------------------------
//
//  Type Definitions
//
//---------------------------------------------------------------------------

//  DWORDs are primarily used for far calls, like the pointer to the control
//  function, and for offsets into EMBs.  WORDs should be used for handles
//  and most other data types.

typedef unsigned long int	dword;	//  32-bit double word
typedef unsigned int		word;	//  16-bit word
typedef unsigned char		byte;	//  8-bit byte

//---------------------------------------------------------------------------
//
//  Structures
//
//---------------------------------------------------------------------------

//  XMM spec says handles are words and offsets are double words.
//  This structure is passed to XMM MoveMemory function 0x0B.
//  If a NULL handle (0x0000) is passed, the offset is assumed to be a far
//  pointer into conventional memory in Intel DWORD notation

typedef struct XMM_Move {
    dword	Length;			//  Number of bytes to move
    word	SourceHandle;		//  Source handle
    dword	SourceOffset;		//  Source offset into block memory
    word	DestHandle;		//  Destination handle
    dword	DestOffset;		//  Destination offset into block memory
} XMM_Move;

//---------------------------------------------------------------------------
//
//  External Global Variable Declaration
//
//---------------------------------------------------------------------------

extern const char XMMLIB_Version[];	//  String contains XMMLIB version
extern dword XMM_Control;		//  Array stores SEG:OFF of XMM handler
extern word XMM_Version;		//  16-bit BCD of XMM version
extern char XMM_VerString[];		//  String contains XMM version
extern word XMM_HMA;			//  Contains 1 if HMA is available
extern XMM_Move XMM_MoveStruct;		//  Contains move information

//---------------------------------------------------------------------------
//
//  Function Prototypes
//
//---------------------------------------------------------------------------

extern byte	XMM_Installed();
extern dword	XMM_GetControl();
extern word	XMM_GetVersion();
extern int	XMM_GetVerHigh();
extern int	XMM_GetVerLow();
extern char*	XMM_GetVerString();
extern dword	XMM_Initialize();
extern word	XMM_QueryTotalFree();
extern word	XMM_QueryLargestFree();
extern word	XMM_AllocateBlock(word size);
extern byte	XMM_FreeBlock(word handle);
extern word	XMM_MoveMemory(dword length,
				word srchnd, dword srcoff,
				word dsthnd, dword dstoff);
extern dword	XMM_LockBlock(word handle);
extern word	XMM_UnlockBlock(word handle);
extern int	XMM_LockCount(word handle);
extern int	XMM_NumHandles(word handle);
extern word	XMM_BlockSize(word handle);
extern word	XMM_ReallocateBlock(word handle, word length);
extern word	XMM_memcpy(word dsthnd, dword dstoff,
			    word srchnd, dword srcoff,
			    dword n);
extern word	XMM_memcpy(word dsthnd, dword dstoff,
			    byte far* source,
			    dword n);
extern word	XMM_memcpy(byte far* dest,
			    word srchnd, dword srcoff,
			    dword n);
extern word	XMM_memcpy(byte far* dest, byte far* source, dword n);

#endif _XMMLIB_H
