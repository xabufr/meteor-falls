#ifndef RTSINPUTMANAGER_H
#define RTSINPUTMANAGER_H

#include <OIS/OISMouse.h>
#include <Utils/vector2d.h>
#include "../../Map/projectivedecalsmanager.h"

class RTSState;
class WorldObjectView;
class WorldObject;
class RTSSelectionManager: public OIS::MouseListener
{
public:
    RTSSelectionManager(RTSState *rtsState);
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

    ~RTSSelectionManager();

private:
    Vector2D<float> getMouseCoordOnMap();
    void clearSelection();
    void extractViews();
    void selectArea();
    void selectSingleUnit();

private:
    bool m_mouseDown, m_mouseMoved;
    Vector2D<float> m_startPosition;
    RTSState *m_rtsState;
    std::vector<WorldObject*> m_selection;
    std::vector<WorldObjectView*> m_selectionViews;
    ProjectiveDecalsManager::BasicDecalDefinition *m_selectionProjection;
};

#endif // RTSINPUTMANAGER_H
