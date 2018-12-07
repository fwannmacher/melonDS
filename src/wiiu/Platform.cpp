/*
    Copyright 2018 Hydr8gon

    This file is part of melonDS.

    melonDS is free software: you can redistribute it and/or modify it under
    the terms of the GNU General Public License as published by the Free
    Software Foundation, either version 3 of the License, or (at your option)
    any later version.

    melonDS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with melonDS. If not, see http://www.gnu.org/licenses/.
*/

#include <malloc.h>
#include <stdio.h>
#include <dynamic_libs/os_functions.h>

#include "../Platform.h"
#include "../Config.h"

#define THREAD_STACK_SIZE 0x80000

namespace Platform
{

void* stack = NULL;

void StopEmu()
{
}

void* Thread_Create(s32 (*func)(s32, void*))
{
    stack = OSAllocFromSystem(THREAD_STACK_SIZE, 0x10);
    OSThread* thread = OSAllocFromSystem(sizeof(OSThread), 8);
    bool created = OSCreateThread(thread, func, 0, NULL, ((u32)stack) + THREAD_STACK_SIZE, THREAD_STACK_SIZE, 0, 1);

    if(!created) OSFatal("Failed to create thread");

    return (void*)thread;
}

void Thread_Free(void* thread)
{
    OSFreeToSystem(stack);
    OSFreeToSystem(thread);
}

void Thread_Wait(void* thread)
{
    OSResumeThread((OSThread*)thread);
}

void* Semaphore_Create()
{
    void* mutex = OSAllocFromSystem(OS_MUTEX_SIZE, 8);
    bool initiated = OSInitMutex(mutex);

    if(!initiated) OSFatal("Failed to initiate mutex");

    return mutex;
}

void Semaphore_Free(void* mutex)
{
    OSFreeToSystem(mutex);
}

void Semaphore_Reset(void* mutex)
{
    OSUnlockMutex(mutex);
}

void Semaphore_Wait(void* mutex)
{
    OSLockMutex(mutex);
}

void Semaphore_Post(void* mutex)
{
    OSUnlockMutex(mutex);
}

bool MP_Init()
{
    return false;
}

void MP_DeInit()
{
}

int MP_SendPacket(u8* data, int len)
{
    return 0;
}

int MP_RecvPacket(u8* data, bool block)
{
    return 0;
}

bool TryLoadPCap(void* lib)
{
    return true;
}

bool LAN_Init()
{
    return false;
}

void LAN_DeInit()
{
}

int LAN_SendPacket(u8* data, int len)
{
    return 0;
}

void LAN_RXCallback(u8* blarg, const struct pcap_pkthdr* header, const u8* data)
{
}

int LAN_RecvPacket(u8* data)
{
    return 0;
}

}
