#ifndef RTSINPUTMANAGER_H
#define RTSINPUTMANAGER_H

#include <OIS/OISMouse.h>
#include <Utils/vector2d.h>

class RTSState;
class WorldObjectView;
class WorldObject;
namespace Ogre {
    class Overlay;
    class OverlayContainer;
}
class RTSSelectionManager: public OIS::MouseListener
{
public:
    RTSSelectionManager(RTSState *rtsState);
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

    ~RTSSelectionManager();

    Vector2D<float> getMouseCoord();
private:
    Vector2D<float> getMouseCoordOnMap();
    void clearSelection();
    void extractViews();
    void selectArea();
    void selectSingleUnit();
    void notifyPlayers();

private:
    bool m_mouseDown, m_mouseMoved;
    Vector2D<float> m_startPosition;
    RTSState *m_rtsState;
    std::vector<WorldObject*> m_selection;
    std::vector<WorldObjectView*> m_selectionViews;

    Ogre::Overlay *m_overlaySelection;
    Ogre::OverlayContainer *m_containerSelection;
};

#endif // RTSINPUTMANAGER_H
