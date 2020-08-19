#ifndef _SCREEN_H
#define _SCREEN_H

#include <string>

class Screen {

public:
    void some_member() const;
    
    typedef std::string::size_type pos;

    Screen() = default;

    Screen(pos ht, pos wd, char c): height(ht), width(wd),
        contents(ht*wd,c){ }
    char get() const
    {return contents[cursor];}

    inline char get (pos ht, pos wd) const;

    Screen& move(pos r, pos c);

    Screen& set(char);
    Screen& set(pos, pos, char);
    
private:
    pos cursor = 0;
    pos height = 0;
    pos width = 0;
    std::string contents;

    mutable size_t access_ctr;
};
#endif
