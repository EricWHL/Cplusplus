#include <string>

#include "Window_Manager.h"

using namespace std;

void Window_Manager::clear(ScreenIndex i)
{
    Screen& s = screens[i];
    s.contents = string(s.height * s.width, ' ');
}

Window_Manager::ScreenIndex Window_Manager::addScreen(const Screen& s)
{
    screens.push_back(s);
    return screens.size() - 1;
}
