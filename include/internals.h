#pragma once
#include "sys/ioctl.h"
#include "termios.h"
#include "stdio.h"
#include "time.h"

namespace internal{

    int keyEvent();
    void frameSleep(const int&);

}