#pragma once

#include "stdafx.h"

struct ipcMessageQueue
{
  unsigned int Initialized;
  unsigned int SendIndex;
  unsigned int ReadIndex;
  unsigned int MaxIndex;
  unsigned int WaitAfterSend;
  ipcMessage *pMessages;
  HANDLE SendEvent;
  HANDLE WaitEvent;
  HANDLE hMutex;
  HANDLE hQueueThread;
};

struct ipcMessage
{
    void (*pHandler)(void *);
    void *pParameter;
};
