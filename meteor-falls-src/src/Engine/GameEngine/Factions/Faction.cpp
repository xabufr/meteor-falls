#include "Faction.h"
#include "../Unites/UniteFactory.h"
#include "../../ScriptEngine/XmlDocumentManager.h"
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
    rapidxml::xml_document<>* document;
    for(std::string path : m_paths)
    {
        try{
        document = XmlDocumentManager::get()->getDocument(path);
        }
        catch(FileNotFound &e){
            std::cerr << "File not found: " << e.what() << std::endl;
            continue;
        }
        rapidxml::xml_node<> *root = document->first_node("root");
        //Chargement des recherches
        rapidxml::xml_node<>* nodeRech, *nodeUnit;
        for(nodeRech=root->first_node("recherche");nodeRech;nodeRech=nodeRech->next_sibling("recherche"))
        {
            Recherche *recherche;
            RechercheId id = boost::lexical_cast<RechercheId>(nodeRech->first_node("id")->value());
            recherche = new Recherche(id);
            m_recherches[id]=recherche;

            recherche->m_temps = boost::lexical_cast<int>(nodeRech->first_node("temps")->value());
            if(nodeRech->first_node("level"))
                recherche->m_niveau_recquis = boost::lexical_cast<int>(nodeRech->first_node("level")->value());
            else
                recherche->m_niveau_recquis = 1;

            rapidxml::xml_node<>* nodeCouts = nodeRech->first_node("coute");
            recherche->m_cout.gold = boost::lexical_cast<int>(nodeCouts->first_node("or")->value());
            recherche->m_cout.wood = boost::lexical_cast<int>(nodeCouts->first_node("bois")->value());
            recherche->m_cout.metal = boost::lexical_cast<int>(nodeCouts->first_node("metal")->value());
            recherche->m_cout.population = boost::lexical_cast<int>(nodeCouts->first_node("pop")->value());

            recherche->m_icone = nodeRech->first_node("icone")->value();
            recherche->m_script = nodeRech->first_node("script")->value();
            recherche->m_nom = nodeRech->first_node("nom")->value();
        }
        //Chargement des unités
        for(nodeUnit=root->first_node("unite");nodeUnit;nodeUnit=nodeUnit->next_sibling("unite"))
        {
            TypeUnite *unite;
            TypeUnite::Type type = TypeUnite::typeFromString(nodeUnit->first_node("type")->value());
            UnitId id = boost::lexical_cast<UnitId>(nodeUnit->first_node("id")->value());
            unite = new TypeUnite(id,type,this);
            m_typesUnites[id]=unite;
			if(nodeUnit->first_attribute("spawn"))
			{
				unite->m_spawn = boost::lexical_cast<bool>(nodeUnit->first_attribute("spawn")->value());
			}

            if(nodeUnit->first_node("level"))
                unite->m_niveau_recquis = boost::lexical_cast<int>(nodeUnit->first_node("level")->value());
            else
                unite->m_niveau_recquis = 1;

            unite->m_nom = nodeUnit->first_node("nom")->value();
            unite->m_attaque = boost::lexical_cast<int>(nodeUnit->first_node("attaque")->value());
            unite->m_vision = boost::lexical_cast<float>(nodeUnit->first_node("vision")->value());
            unite->m_portee = boost::lexical_cast<float>(nodeUnit->first_node("portee")->value());
            unite->m_temps_construction = boost::lexical_cast<int>(nodeUnit->first_node("temps")->value());

            unite->m_typeDegats = DegatManager::get()->getDegat(boost::lexical_cast<DegatId>(nodeUnit->first_node("type-degat")->value()));
            unite->m_armure = DegatManager::get()->getArmure(boost::lexical_cast<ArmureId>(nodeUnit->first_node("armure")->value()));

            rapidxml::xml_node<>* nodeCouts = nodeUnit->first_node("coute");
			if(nodeCouts)
			{
				unite->m_cout.gold = boost::lexical_cast<int>(nodeCouts->first_node("or")->value());
				unite->m_cout.wood = boost::lexical_cast<int>(nodeCouts->first_node("bois")->value());
				unite->m_cout.metal = boost::lexical_cast<int>(nodeCouts->first_node("metal")->value());
				unite->m_cout.population = boost::lexical_cast<int>(nodeCouts->first_node("pop")->value());
			}

            rapidxml::xml_node<>* nodeProduction = nodeUnit->first_node("produit");
            if(nodeProduction)
            {
                if(nodeCouts->first_node("or"))
                    unite->m_cout.gold = boost::lexical_cast<int>(nodeCouts->first_node("or")->value());
                if(nodeCouts->first_node("bois"))
                    unite->m_cout.wood = boost::lexical_cast<int>(nodeCouts->first_node("bois")->value());
                if(nodeCouts->first_node("metal"))
                    unite->m_cout.metal = boost::lexical_cast<int>(nodeCouts->first_node("metal")->value());
                if(nodeCouts->first_node("pop"))
                    unite->m_cout.population = boost::lexical_cast<int>(nodeCouts->first_node("pop")->value());
            }
			rapidxml::xml_node<>* nodeMeshes = nodeUnit->first_node("meshes");
			if(nodeMeshes)
			{
				rapidxml::xml_node<>* nodeMesh;
				for(nodeMesh = nodeMeshes->first_node("mesh");nodeMesh!=0;nodeMesh=nodeMeshes->next_sibling("mesh"))
				{
					std::string name, mesh;
					name                          = nodeMesh->first_attribute("name")->value();
					mesh                          = nodeMesh->first_attribute("mesh")->value();
					unite->m_meshParameters[name] = mesh;
				}
			}
            switch(type)
            {
                case TypeUnite::Type::BATIMENT:
                    m_batiments.push_back(m_nom);
                break;

                case TypeUnite::Type::AERIEN:
                    m_aerien.push_back(m_nom);
                break;

                case TypeUnite::Type::TERRESTE:
                    m_terrestre.push_back(m_nom);
                break;
            }
        }
		rapidxml::xml_node<>* nodeHero;
		for(nodeHero=root->first_node("classe");nodeHero;nodeHero=nodeHero->next_sibling("classe"))
		{
			int id             = boost::lexical_cast<int>(nodeHero->first_node("id")->value());
			ClasseHero *classe = new ClasseHero(id, this);
			if(!m_classeHeroManager.addClasse(classe))
			{
				delete classe;
				continue;
			}
			classe->m_nom   = nodeHero->first_node("nom")->value();
			classe->m_icone = nodeHero->first_node("icone")->value();
			/*
			 * Chargement des meshes
			 * */
			rapidxml::xml_node<> *meshes;
			for(meshes=nodeHero->first_node("meshes")->first_node("mesh");meshes;meshes=meshes->next_sibling("mesh"))
			{
				int from, to;
				from = boost::lexical_cast<int>(meshes->first_attribute("from")->value());
				to   = boost::lexical_cast<int>(meshes->first_attribute("to")->value());
				classe->addMesh(from, to, meshes->value());
			}
		}
    }
    //Seconde passe, pour édition de liens
    for(std::string path : m_paths)
    {
        try{
        document = XmlDocumentManager::get()->getDocument(path);
        }
        catch(FileNotFound &e){
            continue;
        }
        rapidxml::xml_node<> *root = document->first_node("root");
        //Chargement des recherches
        rapidxml::xml_node<>* nodeRech, *nodeUnit;
        for(nodeRech=root->first_node("recherche");nodeRech;nodeRech=nodeRech->next_sibling("recherche"))
        {
            Recherche *recherche;
            RechercheId id = boost::lexical_cast<RechercheId>(nodeRech->first_node("id")->value());
            recherche = m_recherches[id];
            if(nodeRech->first_node("necessite"))
            {
                rapidxml::xml_node<>* nodeNecessite = nodeUnit->first_node("necessite"),
                                        *tempNode;
                //Recherches
                for(tempNode=nodeNecessite->first_node("recherche");tempNode;tempNode=tempNode->next_sibling("recherche"))
                {
                    id = boost::lexical_cast<RechercheId>(tempNode->value());
                    recherche->m_recherchesNecessaires.push_back(m_recherches[id]);
                }
                //Unités
                for(tempNode=nodeNecessite->first_node("unite");tempNode;tempNode=tempNode->next_sibling("unite"))
                {
                    id = boost::lexical_cast<UnitId>(tempNode->value());
                    recherche->m_unitesNecessaires.push_back(m_typesUnites[id]);
                }
            }
        }
        //Chargement des unités
        for(nodeUnit=root->first_node("unite");nodeUnit;nodeUnit=nodeUnit->next_sibling("unite"))
        {
            TypeUnite *unite;
            UnitId id = boost::lexical_cast<UnitId>(nodeUnit->first_node("id")->value());
            unite = m_typesUnites[id];

            if(nodeUnit->first_node("amerlioration"))
                unite->m_amelioration = m_typesUnites[boost::lexical_cast<UnitId>(nodeUnit->first_node("amelioration")->value())];

            if(nodeUnit->first_node("constuit"))
            {
                rapidxml::xml_node<>* nodeConstruit = nodeUnit->first_node("constuit"),
                                        *tempNode;
                //Unités
                for(tempNode=nodeConstruit->first_node("unite");tempNode;tempNode=tempNode->next_sibling("unite"))
                {
                    id = boost::lexical_cast<UnitId>(tempNode->value());
                    unite->m_construit.push_back(m_typesUnites[id]);
                }
                //Recherches
                for(tempNode=nodeConstruit->first_node("recherche");tempNode;tempNode=tempNode->next_sibling("recherche"))
                {
                    id = boost::lexical_cast<RechercheId>(tempNode->value());
                    unite->m_recherches.push_back(m_recherches[id]);
                }
            }
            if(nodeUnit->first_node("necessite"))
            {
                rapidxml::xml_node<>* nodeConstruit = nodeUnit->first_node("necessite"),
                                        *tempNode;
                //Unités
                for(tempNode=nodeConstruit->first_node("unite");tempNode;tempNode=tempNode->next_sibling("unite"))
                {
                    id = boost::lexical_cast<UnitId>(tempNode->value());
                    unite->m_necessiteUnite.push_back(m_typesUnites[id]);
                }
                //Recherches
                for(tempNode=nodeConstruit->first_node("recherche");tempNode;tempNode=tempNode->next_sibling("recherche"))
                {
                    id = boost::lexical_cast<RechercheId>(tempNode->value());
                    unite->m_necessiteRecherche.push_back(m_recherches[id]);
                }
            }
        }
		rapidxml::xml_node<>* nodeAvatars;
		for(nodeAvatars=root->first_node("avatar");nodeAvatars;nodeAvatars=nodeAvatars->next_sibling("avatar"))
		{
			int id = boost::lexical_cast<int>(nodeAvatars->first_node("id")->value());
			bool existe = false;
			for(Avatar *av : m_avatarDefault)
			{
				if(av->id() == id)
					existe = true;
			}
			if(existe)
				continue;
			ClasseHero *classe = nullptr;
			int idClasse       = boost::lexical_cast<int>(nodeAvatars->first_node("classe")->value());
			classe             = m_classeHeroManager.classe(idClasse);
			if(classe == nullptr)
					continue;
			Avatar* av = new Avatar(id, classe);
			av->m_nom  = nodeAvatars->first_node("nom")->value();
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
