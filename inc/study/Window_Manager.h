#ifndef _WINDOW_MANAGER_H
#define _WINDOW_MANAGER_H

#include <vector>

#include "Screen.h"

class Window_Manager {

public:
    using ScreenIndex = std::vector<Screen>::size_type;
    void clear(ScreenIndex);

    ScreenIndex addScreen(const Screen&);
    
private:
    std::vector<Screen> screens {Screen(24, 80, ' ')};
};

#endif
