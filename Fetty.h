#ifndef WATCHY_FETTY_H
#define WATCHY_FETTY_H

#include <Watchy.h>

class WatchyFetty : public Watchy{
    public:
        WatchyFetty();
        void init(String datetime = "");
        void handleButtonPress();
        virtual void showMenu(byte menuIndex, bool partialRefresh);
        virtual void showFastMenu(byte menuIndex);
        void drawWatchFace();
};

#endif
