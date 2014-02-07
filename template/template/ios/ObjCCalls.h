//PrintMessage.h
#ifndef __PRINTMESSAGE_H__
#define __PRINTMESSAGE_H__

#include <stddef.h>

class ObjCCalls
{
public:
    static bool OpenURL(const char *url);
    void hideBanner();
    void showBanner();
};

#endif//__PRINTMESSAGE_H__