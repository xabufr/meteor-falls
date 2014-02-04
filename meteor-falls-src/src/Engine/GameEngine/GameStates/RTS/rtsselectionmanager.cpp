#include "rtsselectionmanager.h"
#include "../RTSState.h"
#include <Utils/rectangle.h>
#include "../../Map/WorldObjectView.h"
#include "../../Map/WorldObject.h"

#include <Engine/GraphicEngine/Ogre/ogrecontextmanager.h>
#include <Engine/GraphicEngine/Ogre/OgreWindowInputManager.h>

#include <OgreRay.h>

RTSSelectionManager::RTSSelectionManager(RTSState *rtsState)
{
    m_mouseDown = false;
    m_mouseMoved = false;
    m_rtsState = rtsState;
    OgreContextManager::get()->getInputManager()->addMouseListener(this);
}

bool RTSSelectionManager::mouseMoved(const OIS::MouseEvent &arg)
{
    m_mouseMoved = true;
    return true;
}

bool RTSSelectionManager::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    if(id == OIS::MouseButtonID::MB_Left) {
        m_mouseDown = true;
        m_mouseMoved = false;
        m_startPosition = getMouseCoordOnMap();
    }
    return true;
}

Vector2D<float> RTSSelectionManager::getMouseCoordOnMap()
{
    Vector3D mouseProjectedPosition = m_rtsState->getMouseProjectedPosition();
    Vector2D<float> mousePosition(mouseProjectedPosition.x, mouseProjectedPosition.z);

    return mousePosition;
}

void RTSSelectionManager::clearSelection()
{
    for(WorldObjectView *view : m_selectionViews) {
        view->setSelected(false);
    }
    m_selection.clear();
    m_selectionViews.clear();
}

void RTSSelectionManager::extractViews()
{
    for(WorldObject *object : m_selection) {
        WorldObjectView *view = object->view();
        if(view) {
            m_selectionViews.push_back(view);
            view->setSelected(true);
        }
    }
}

void RTSSelectionManager::selectArea()
{
    Vector2D<float> endPosition = getMouseCoordOnMap();
    Rectangle<float> selectedAera(m_startPosition, endPosition);
    std::vector<Unite *> unitesInRectangle = m_rtsState->getUnitesInRectangle(selectedAera);
    for(Unite* unite : unitesInRectangle) {
        m_selection.push_back((WorldObject*)unite);
    }
}

void RTSSelectionManager::selectSingleUnit()
{
    Ogre::Ray ray = m_rtsState->getMouseRay();
    WorldObject *object = m_rtsState->getObjectUnderRay(ray);
    if(object) {
        m_selection.push_back(object);
    }
}

bool RTSSelectionManager::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    if(id == OIS::MouseButtonID::MB_Left) {
        clearSelection();
        m_mouseDown = false;
        if(m_mouseMoved) {
            selectArea();
        } else {
            selectSingleUnit();
        }
        extractViews();
    }
    return true;
}

RTSSelectionManager::~RTSSelectionManager()
{
    OgreContextManager::get()->getInputManager()->delMouseListener(this);
}
