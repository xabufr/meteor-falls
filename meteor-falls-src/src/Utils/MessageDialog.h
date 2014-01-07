#ifndef MESSAGEDIALOG_H_INCLUDED
#define MESSAGEDIALOG_H_INCLUDED

#include "singleton.h"
#include <CEGUI/CEGUI.h>

class MessageDialog:public Singleton<MessageDialog>
{
public:
    MessageDialog();
    ~MessageDialog();
    bool isVisible(){return m_visible;}
    void setText(std::string s){m_text->setText((CEGUI::utf8*)s.c_str());}
    void show();
    void hide();
private:
    bool m_button_pushed(const CEGUI::EventArgs&);
    bool m_visible;
    CEGUI::Window *m_window;
    CEGUI::Window *m_text;
    CEGUI::PushButton *m_accept;
};
#endif // MESSAGEDIALOG_H_INCLUDED
