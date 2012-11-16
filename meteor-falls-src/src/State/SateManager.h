#ifndef SATEMANAGER_H
#define SATEMANAGER_H

#include <vector>


class SateManager
{
    public:
        void addState(State *p_state);
        void startLoop();
        void exit();
        void removeState(State *p_state);

    protected:

    private:
        std::vector<States*> m_states;
};

#endif // SATEMANAGER_H
