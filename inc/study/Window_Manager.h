#ifndef _WINDOW_MANAGER_H
#define _WINDOW_MANAGER_H

#include "Screen.h"
class Window_Manager {

private:
    std::vector<Screen> screens {Screen(24, 80, ' ')}
};

#endif
