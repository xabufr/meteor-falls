#include "Hero_State.h"

Hero_State::Hero_State(Ogre::SceneManager* mng, Equipe* e, TypeUnite* type, int id)
: Hero(mng, e, type, id)
{

}


float Hero_State::m_attack_def_modification(AnimID monAnim)
{

    switch(monAnim)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            m_attack_def_modif.percent_attack_more = 15;
            m_attack_def_modif.percent_attack_less = 0;
            m_attack_def_modif.percent_defense_more = 0;
            m_attack_def_modif.percent_defense_less = 15;
            break;
    }

}
