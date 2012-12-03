#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H
#include <CEGUI.h>

class LoadingScreen
{
    public:
        LoadingScreen();
        virtual ~LoadingScreen();
        void show();
        void update(std::string);
    protected:
    private:
        CEGUI::Window *m_window;
        CEGUI::Window *m_loadingText, *m_loadingCurrent;
};

#endif // LOADINGSCREEN_H
