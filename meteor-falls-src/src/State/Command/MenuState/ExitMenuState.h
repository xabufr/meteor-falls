#ifndef EXITMENUSTATE_H_INCLUDED
#define EXITMENUSTATE_H_INCLUDED

#include "../../Menu/MenuState.h"
#include "../Command.h"

class ExitMenuState : public Command
{
    public:
        ExitMenuState();
        ~ExitMenuState();
        virtual void use();
};

#endif // EXITMENUSTATE_H_INCLUDED
