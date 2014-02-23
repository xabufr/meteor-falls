#ifndef H_CLIENT_GAME_ENGINE_H
#define H_CLIENT_GAME_ENGINE_H
#include "Layout/layoutRTS.h"
#include "GameEngine.h"
#include "StateFactory.h"

class MapView;
class WorldObjectView;
class SelectionBillboardManager;
class ClientGameEngine : public GameEngine
{
public:
    ClientGameEngine(EngineManager*, Joueur*);
    virtual ~ClientGameEngine();
    virtual void handleMessage(EngineMessage&);
    virtual void work(const TimeDuration &elapsed);

    Chat* getChat(){return m_chat;}
    CameraManager *cameraManager() const;
    Joueur* getCurrentJoueur();
    void setSousStateType(TypeState);
    virtual void addTeam(Equipe*);

    virtual Type getTypeServerClient() const;
    const MapView* getMapView() const;

    SelectionBillboardManager *selectionBillboardManager();
    void setSelectedUnits(const std::vector<std::uint32_t> &ids);

private:
    void changeSousStateIfNecessary();

private:
    MapView *m_map_view;
    Joueur *m_current_joueur;
    State *m_sous_state;

    CameraManager* m_camManager;
    Chat* m_chat;
    TypeState m_type_sous_state;
    bool m_change_sous_state;
    SelectionBillboardManager *m_selectionBillboardManager;
};

#endif
