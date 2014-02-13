#include "Faction.h"
#include "../Unites/UniteFactory.h"
#include "../Unites/typedefs.h"
#include "../Unites/TypeUnite.h"
#include "../Degats/DegatManager.h"
#include "../../../precompiled/lexical_cast.h"
#include "../Recherches/Recherche.h"
#include "../../../Utils/Exception/FileNotFound.h"
#include "../Heros/ClasseHero.h"
#include "../Heros/Avatar.h"

Faction::Faction(bool jouable, FactionId id, const std::string& nom):
m_nom(nom), m_id(id), m_jouable(jouable)
{
}
Faction::~Faction()
{
    for(auto it : m_typesUnites)
    {
        delete it.second;
    }
    for(auto it : m_recherches)
        delete it.second;
    for(Avatar* av : m_avatarDefault)
        delete av;
}
void Faction::addConfigFile(std::string path)
{
    m_paths.push_back(path);
}
void Faction::load()
{
    //Première passe de chargement
    for(std::string path : m_paths)
    {
        XmlDocumentManager::Document& document = XmlDocumentManager::get()->getDocument(path);
        //Chargement des recherches
        std::pair<XmlDocumentManager::Document::const_assoc_iterator,
            XmlDocumentManager::Document::const_assoc_iterator>bounds(document.get_child("root").equal_range("recherche"));
        for(auto it(bounds.first); it!=bounds.second;++it)
        {
            const XmlDocumentManager::Document &drech = it->second;
            Recherche *recherche;
            RechercheId id = drech.get<RechercheId>("id");
            recherche = new Recherche(id);
            m_recherches[id]=recherche;

            recherche->m_temps = drech.get<int>("temps");
            recherche->m_niveau_recquis = drech.get("level", 1);

            recherche->m_cout.gold = drech.get<int>("coute.or");
            recherche->m_cout.wood = drech.get<int>("coute.bois");
            recherche->m_cout.metal = drech.get<int>("coute.metal");
            recherche->m_cout.population = drech.get<int>("coute.pop");

            recherche->m_icone = drech.get<std::string>("icone");
            recherche->m_script = drech.get<std::string>("script");
            recherche->m_nom = drech.get<std::string>("nom");
        }
        //Chargement des unités
        bounds = document.get_child("root").equal_range("unite");
        for(auto it(bounds.first);it!=bounds.second;++it)
        {
            processUnit(it->second);
        }
    }
    //Seconde passe, pour édition de liens
    for(std::string path : m_paths)
    {
        XmlDocumentManager::Document& document = XmlDocumentManager::get()->getDocument(path);
        //Chargement des recherches
        auto bounds = document.get_child("root").equal_range("recherche");
        for(auto it(bounds.first);it!=bounds.second;++it)
        {
            const XmlDocumentManager::Document& drech = it->second;
            Recherche *recherche;
            RechercheId id = drech.get<int>("id");

            recherche = m_recherches[id];
            try {
                auto boundsNecessite = drech.get_child("necessite").equal_range("recherche");
                for(auto rech(boundsNecessite.first);rech!=boundsNecessite.second;++rech)
                {
                    id = rech->second.get_value<RechercheId>();
                    recherche->m_recherchesNecessaires.push_back(m_recherches[id]);
                }
                boundsNecessite = drech.get_child("necessite").equal_range("unite");
                for(auto unit(boundsNecessite.first);unit!=boundsNecessite.second;++unit)
                {
                    id = unit->second.get_value<UnitId>();
                    recherche->m_unitesNecessaires.push_back(m_typesUnites[id]);
                }
            } catch (...) {
            }
        }
        //Chargement des unités
        bounds = document.get_child("root").equal_range("unite");
        for(auto it=bounds.first;it!=bounds.second;++it)
        {
            TypeUnite *unite;
            const XmlDocumentManager::Document& nodeUnit = it->second;
            UnitId id = nodeUnit.get<int>("id");
            unite = m_typesUnites[id];

            int idAmelioration = nodeUnit.get("amelioration", -1);
            if(idAmelioration>0)
                unite->m_amelioration = m_typesUnites[idAmelioration];

            boost::optional<const XmlDocumentManager::Document &> construit = nodeUnit.get_child_optional("construit");
            if(construit)
            {
                auto boundsLiens = construit->equal_range("unite");
                for(auto itUn=boundsLiens.first;itUn!=boundsLiens.second;++itUn)
                    unite->m_construit.push_back(m_typesUnites[itUn->second.get_value<int>()]);
                boundsLiens = construit->equal_range("recherche");
                for(auto itUn=boundsLiens.first;itUn!=boundsLiens.second;++itUn)
                    unite->m_recherches.push_back(m_recherches[itUn->second.get_value<int>()]);
            }
            boost::optional<const XmlDocumentManager::Document&> necessite = nodeUnit.get_child_optional("necessite");
            if(necessite)
            {
                auto boundsLiens = necessite->equal_range("unite");
                for(auto itUn=boundsLiens.first;itUn!=boundsLiens.second;++itUn)
                    unite->m_necessiteUnite.push_back(m_typesUnites[itUn->second.get_value<int>()]);
                boundsLiens = necessite->equal_range("recherche");
                for(auto itUn=boundsLiens.first;itUn!=boundsLiens.second;++itUn)
                    unite->m_necessiteRecherche.push_back(m_recherches[itUn->second.get_value<int>()]);
            }
        }
        bounds = document.get_child("root").equal_range("avatar");
        for(auto it=bounds.first;it!=bounds.second;++it)
        {
            const XmlDocumentManager::Document& nodeAvatars = it->second;
            int id = nodeAvatars.get<int>("id");
            bool existe = false;
            for(Avatar *av : m_avatarDefault)
            {
                if(av->id() == id)
                    existe = true;
            }
            if(existe)
                continue;
            ClasseHero *classe = nullptr;
            int idClasse       = nodeAvatars.get<int>("classe");
            classe             = m_classeHeroManager.classe(idClasse);
            if(classe == nullptr)
                continue;
            Avatar* av = new Avatar(id, classe);
            av->m_nom  = nodeAvatars.get<std::string>("nom");
            av->m_isDefault = true;
            m_avatarDefault.push_back(av);
        }
    }
}
FactionId Faction::id() const
{
    return m_id;
}
TypeUnite* Faction::getType(UnitId id)
{
    auto it = m_typesUnites.find(id);
    if(it!=m_typesUnites.end())
        return it->second;
    return 0;
}
const ClasseHeroManager& Faction::getClassesManager() const
{
    return m_classeHeroManager;
}
const std::vector<Avatar*> Faction::defaultAvatars() const
{
    return m_avatarDefault;
}
const std::string& Faction::nom() const
{
    return m_nom;
}
void Faction::processUnit(const XmlDocumentManager::Document& nodeUnit)
{
    TypeUnite *unite;
    TypeUnite::Type type = TypeUnite::typeFromString(nodeUnit.get<std::string>("type"));
    UnitId id = nodeUnit.get<int>("id");

    if(type==TypeUnite::HERO)
        unite = new ClasseHero(id, this, nodeUnit);
    else
        unite = new TypeUnite(id,type,this, nodeUnit);

    unite->m_spawn = nodeUnit.get("<xmlattr>.spawn", false);
    unite->m_niveau_recquis = nodeUnit.get("level", 1);

    unite->m_nom = nodeUnit.get<std::string>("nom");
    unite->m_attaque = nodeUnit.get<int>("attaque");
    unite->m_vision = nodeUnit.get<float>("vision");
    unite->m_portee = nodeUnit.get<float>("portee");
    unite->m_temps_construction = nodeUnit.get<int>("temps");
    unite->m_vie = nodeUnit.get<int>("vie");

    unite->m_typeDegats = DegatManager::get()->getDegat(nodeUnit.get<DegatId>("type-degat"));
    unite->m_armure = DegatManager::get()->getArmure(nodeUnit.get<ArmureId>("armure"));

    unite->m_cout.gold          = nodeUnit.get("coute.or", 0);
    unite->m_cout.wood          = nodeUnit.get("coute.bois", 0);
    unite->m_cout.metal         = nodeUnit.get("coute.metal", 0);
    unite->m_cout.population    = nodeUnit.get("coute.pop", 0);

    unite->m_apports.gold       = nodeUnit.get("produit.or", 0);
    unite->m_apports.wood       = nodeUnit.get("produit.bois", 0);
    unite->m_apports.metal      = nodeUnit.get("produit.metal", 0);
    unite->m_apports.population = nodeUnit.get("produit.pop", 0);

    auto boundMeshes            = nodeUnit.get_child("meshes").equal_range("mesh");
    for(auto itMesh=boundMeshes.first;itMesh!=boundMeshes.second;++itMesh)
    {
        if(type == TypeUnite::HERO)
        {
            int from, to;
            from = itMesh->second.get<int>("<xmlattr>.from");
            to   = itMesh->second.get<int>("<xmlattr>.to");
            ClasseHero::HeroMesh data;
            data.mesh = itMesh->second.get<std::string>("<xmlattr>.mesh");
            data.walk = itMesh->second.get<std::string>("walk");
            data.jump = itMesh->second.get<std::string>("jump");
            data.fall = itMesh->second.get<std::string>("fall");
            static_cast<ClasseHero*>(unite)->addMesh(from, to,data);
        }
        else
        {
            std::string name, mesh;
            name                          = itMesh->second.get<std::string>("<xmlattr>.name");
            mesh                          = itMesh->second.get<std::string>("<xmlattr>.mesh");
            unite->m_meshParameters[name] = mesh;
        }
    }
    if(type == TypeUnite::HERO)
    {
        ClasseHero* hero = static_cast<ClasseHero*>(unite);
        if(!m_classeHeroManager.addClasse(hero))
        {
            delete hero;
            return;
        }
        hero->m_icone = nodeUnit.get<std::string>("icone");
        /*
         * Chargement des meshes
         * */
    }
    else
        m_typesUnites[id]=unite;
}
