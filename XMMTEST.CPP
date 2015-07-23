//===========================================================================
//
//  XMMTEST.CPP -- Sample program that illustrates some XMMLIB functions
//
//===========================================================================

#ifndef XMMTEST_CPP
#define XMMTEST_CPP

#include <iostream.h>
#include "xmmlib.h"

int main()
{
    word handle;
    word freeEMB;
    char buffer[1024] = "These are the contents of buffer";
    char buffer2[1024] = "";

    cout << XMMLIB_Version << endl;

    if (XMM_Installed() == FALSE) {
	cout << "No Extended Memory Manager found" << endl;
	return(1);
    }

    if (XMM_Initialize() == 0) {
	cout << "Could not initialize XMM" << endl;
	return(2);
    }

    cout << "Extended Memory Manager version " << XMM_GetVerString()
	 << " found" << endl;

    cout << XMM_QueryTotalFree() << " KB total XMS free" << endl;
    freeEMB = XMM_QueryLargestFree();
    cout << freeEMB << " KB free in largest EMB" << endl;

    if (freeEMB < 16) {
	cout << "Sorry, not enough memory (16K) found in largest EMB." << endl;
	return(3);
    }

    cout << "Allocating 1K block" << endl;
    handle = XMM_AllocateBlock(1);
    cout << "EMB handle is " << handle << endl;

    cout << XMM_QueryTotalFree() << " KB total XMS free" << endl;
    cout << XMM_QueryLargestFree() << " KB free in largest EMB" << endl;

    cout << "Contents of buffer:  \"" << buffer << "\"" << endl;
    cout << "Contents of buffer2:  \"" << buffer2 << "\"" << endl;

    cout << "Copying from buffer to EMB:0" << endl;
    XMM_memcpy(handle, 0L, (byte far*) buffer, 512L);
    cout << "Copying from EMB:0 to EMB:512" << endl;
    XMM_memcpy(handle, 512L, handle, 0L, 512L);
    cout << "Copying from EMB:512 to buffer2" << endl;
    XMM_memcpy((byte far*) buffer2, handle, 512L, 512L);

    cout << "Contents of buffer:  \"" << buffer << "\"" << endl;
    cout << "Contents of buffer2:  \"" << buffer2 << "\"" << endl;

    cout << "Reallocating block to 2K" << endl;
    XMM_ReallocateBlock(handle, 2);
    cout << "Block size is now " << XMM_BlockSize(handle) << endl;

    cout << XMM_QueryTotalFree() << " KB total XMS free" << endl;
    cout << XMM_QueryLargestFree() << " KB free in largest EMB" << endl;

    cout << XMM_NumHandles(handle) << " handles available for EMBs" << endl;
    cout << XMM_LockCount(handle) << " locks on this particular EMB" << endl;

    cout << "Locking this EMB" << endl;
    XMM_LockBlock(handle);
    cout << XMM_LockCount(handle) << " locks on this particular EMB" << endl;

    cout << "Unlocking this EMB" << endl;
    XMM_UnlockBlock(handle);
    cout << XMM_LockCount(handle) << " locks on this particular EMB" << endl;

    cout << "Deallocating 2K block" << endl;
    XMM_FreeBlock(handle);

    cout << XMM_QueryTotalFree() << " KB total XMS free" << endl;
    cout << XMM_QueryLargestFree() << " KB free in largest EMB" << endl;

    return(0);
}

#endif XMMTEST_CPP

