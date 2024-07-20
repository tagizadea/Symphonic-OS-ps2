#ifndef _OWN_PAD
#define _OWN_PAD
#include <tamtypes.h>
#include <kernel.h>
#include <sifrpc.h>
#include <loadfile.h>
#include <stdio.h>


#include <libpad.h>

void init_pad_port();
int waitPadReady(int port, int slot);
int initializePad(int port, int slot);
u32 read_pad(int port, int slot);

#endif