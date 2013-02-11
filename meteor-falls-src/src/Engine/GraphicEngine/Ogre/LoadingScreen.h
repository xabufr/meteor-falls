#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H
#include <CEGUI.h>

class LoadingScreen
{
    public:
        LoadingScreen(int sum);
        virtual ~LoadingScreen();
        void show();
        void update(std::string);
        void setGroup(std::string);
    protected:
    private:
        int m_count, m_sum;
        CEGUI::Window *m_window;
        CEGUI::Window *m_loadingText, *m_loadingCurrent;
        CEGUI::ProgressBar *m_progress_bar;
};

#endif // LOADINGSCREEN_H
