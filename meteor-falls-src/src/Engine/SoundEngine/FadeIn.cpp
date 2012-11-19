#include "FadeIn.h"
#include <cmath>

float Fade::operator()(float temps)// calcule le temps ici
{
    if (m_fadeType == in)
    {
        temps = 1 - temps;
    }

    switch(m_fadeFunction)
    {
        cubique :
            break;
    }

}

float Fade::Cubique(float temps)// ici, calcul de fonction cubique
{

    return (1 + pow(2 * temps + 1,1.f/3.f)) / 2;

}

float Fade::Carre(float temps)// ici, calcul de fonction carre
{
    return 1 - (temps-1)*(temps-1);
}

float Fade::Constant(float temps)// ici, calcul de fonction carre
{
    return temps;
}


int Fade::work(int temps_actuel, int temps_total, int duree_fade, int volume_base) // millisecondes
{
    float temps;

    if (m_fadeType == in)
        temps = (float (temps_actuel) / float (duree_fade));
    else
        temps = float (temps_total - temps_actuel) / duree_fade;


    switch(m_fadeFunction)
    {

        case cubique:
            return (volume_base * Cubique(temps));

        case carre:
            return (volume_base * Carre(temps));

        case constant:
            return (volume_base * Constant(temps));

    }

}





