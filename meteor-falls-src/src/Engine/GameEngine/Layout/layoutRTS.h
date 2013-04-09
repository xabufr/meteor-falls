#ifndef LAYOUTRTS_H
#define LAYOUTRTS_H
#include <CEGUI.h>
#include "Engine/GameEngine/Factions/Faction.h"
#include "State/StateManager.h"
#include "State/State.h"
#include "Engine/GameEngine/Joueur/Joueur.h"
#include "Engine/GameEngine/Factions/Equipe.h"
#include "Engine/GameEngine/Unites/TypeUnite.h"
#include <iostream>
#include <vector>

class LayoutRTS
{
    public:
        LayoutRTS(Joueur*);
        ~LayoutRTS();
        virtual bool isVisible();
        virtual void enter();
        virtual void exit();
        void update();
        void UpdateBatimentsPossiblesALaConstruction();
        void SetConstruction(int batiment_construit);
        virtual ret_code work(unsigned int);

    private:
        void SetIdBatimentFromButton();
        void AfficherPremiereListeConstruction();
        void AfficherSecondeListeConstruction();
        bool m_visible;
        bool m_choix_grille(const CEGUI::EventArgs&);
        bool m_choix_grilleBase(const CEGUI::EventArgs&);
        void hide_grille_constructionsShowGrilleGen();
        void hide_grille_constructions();
        Faction* m_faction;
        Joueur* m_joueur;
        std::vector<int> m_batiments_possible_pour_construire;
        std::vector<int> m_batiments_construits;
        CEGUI::Window *m_info_ressources,* m_position_map, *m_infos_unite,*m_grille_batiments;
        CEGUI::PushButton *m_grille_batimentsA,*m_grille_batimentsZ,*m_grille_batimentsE,*m_grille_batimentsQ,*m_grille_batimentsS,*m_grille_batimentsD,*m_grille_batimentsW,*m_grille_batimentsX,*m_grille_batimentsC,*m_grille_batimentsPartieA,*m_grille_batimentsPartieB;
        CEGUI::PushButton *m_grille_batiments2A,*m_grille_batiments2Z,*m_grille_batiments2E,*m_grille_batiments2Q;
};

#endif
