#ifndef FADEIN_H
#define FADEIN_H

class Fade{

    public:

        enum fadeType
        {
            in,
            out,
        } m_fadeType;

        enum fadeFunction
        {
            cubique,
            carre,
            constant
        } m_fadeFunction;

        void setFunction(fadeFunction Function)
        {
            m_fadeFunction = Function;
        }


        void setType(fadeType Type_fading)
        {
            m_fadeType = Type_fading;
        }

        int work(int temps_actuel, int temps_total, int duree_fade, int volume_base); // millisecondes
        static float Cubique(float);// ici, calcul de fonction cubique
        static float Carre(float);// ici, calcul de fonction carre
        static float Constant(float); // ici, calcul de fonction constant

};

#endif
