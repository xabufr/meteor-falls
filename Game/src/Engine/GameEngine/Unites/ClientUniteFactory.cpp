#include "ClientUniteFactory.h"
#include "Builder/UniteBuilder.h"
#include "BatimentView.h"
#include "TerrestreView.h"
#include "TypeUnite.h"
#include "../Heros/HeroView.h"
#include "../Heros/Hero.h"
#include "Unite.h"
#include "Batiment.h"
#include "Terrestre.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"

Unite *ClientUniteFactory::create_impl(UniteBuilder *builder, Joueur *j, Avatar *a, TypeUnite *t, UnitId id)
{
    Unite *u = builder->create(j, a, t, id);
    switch (t->type())
    {
        case TypeUnite::BATIMENT:
        {
            BatimentView *batView = new BatimentView(static_cast<Batiment *>(u), m_sceneManager->getRootSceneNode()
                    ->createChildSceneNode());
        }
        break;
        case TypeUnite::TERRESTE:
        {
            TerrestreView *terrestreView = new TerrestreView(static_cast<Terrestre *>(u), m_sceneManager->getRootSceneNode()->createChildSceneNode());
        }
        break;
        case TypeUnite::HERO:
        {
            HeroView *heroView = new HeroView(static_cast<Hero *>(u), m_sceneManager->getRootSceneNode()->createChildSceneNode());
        }
        break;
    }
    return u;
}
