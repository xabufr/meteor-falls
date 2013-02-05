#ifndef HERO_STATE_H
#define HERO_STATE_H
#include "Engine/GameEngine/Unites/Hero.h"
#include <OgreSceneManager.h>
enum AnimID
{
    /// Movement
    ANIM_WALK_FORWARD = 0,
    ANIM_WALK_BACK = 1,
    ANIM_WALK_RIGHT = 2,
    ANIM_WALK_LEFT = 3,
    ANIM_RUN_FORWARD = 4,
    ANIM_RUN_BACK = 5,
    ANIM_RUN_RIGHT = 6,
    ANIM_RUN_LEFT = 7,

    /// Various
    ANIM_WAIT = 8,
    ANIM_LAUGHT = 9,
    ANIM_SMACK = 10,
    ANIM_DANCE = 11,

    /// JUMP
    ANIM_JUMP_START = 12,
    ANIM_JUMP_LOOP = 13,
    ANIM_JUMP_END = 14,

    /// ATTACK
    ANIM_JATTACK1 = 15,
    ANIM_JATTACK2 = 16,
    ANIM_JATTACK3 = 17,
    ANIM_ATTACK_ULTIMATE = 18,
    ANIM_ATTACK_BASIC = 19,
    ANIM_PARRY = 20
};

struct attack_def_modif
{
    int percent_attack_more,percent_attack_less;
    int percent_defense_more,percent_defense_less;
};

class Hero_State : public Hero
{

    public:
        Hero_State(Ogre::SceneManager* mng, Equipe*, TypeUnite* type, int id);

    private:
        float m_Animation_Get_Duration();
        float m_attack_def_modification(AnimID monAnim);
        bool m_DoNothing();
        void m_StopAnimation();
        std::string m_animation_name;
        std::string m_animation_path;
        float m_animation_duration;
        bool m_isDoingNothing;
        attack_def_modif m_attack_def_modif;
};

#endif // HERO_STATE_H*/
