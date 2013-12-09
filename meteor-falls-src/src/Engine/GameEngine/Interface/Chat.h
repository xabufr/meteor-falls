#ifndef CHAT_H_INCLUDED
#define CHAT_H_INCLUDED

#include <OIS/OIS.h>

namespace CEGUI{
    class Listbox;
    class Editbox;
    class String;
};

class Joueur;
class GameEngine;
class Chat: public OIS::KeyListener, public OIS::MouseListener
{
public:
    Chat(GameEngine*);
    ~Chat();
    void show();
    void hide();
    void addMessage(std::string, Joueur*);
    bool isVisible() const;
    bool isListen() {return m_listen;}

    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

    virtual bool keyPressed(const OIS::KeyEvent &arg);
    virtual bool keyReleased(const OIS::KeyEvent &arg);
private:
    bool m_visible;
    bool m_listen;
    void m_send_message(const CEGUI::String&);
    OIS::Keyboard *m_keyboard;
    CEGUI::Listbox *m_show_message;
    CEGUI::Editbox *m_message;
    GameEngine *m_game_engine;

};
#endif // CHAT_H_INCLUDED
