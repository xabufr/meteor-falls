#include "rtsselectionmanager.h"
#include "../RTSState.h"
#include <Utils/rectangle.h>
#include "../../Map/WorldObjectView.h"
#include "../../Unites/Unite.h"

#include <Engine/GraphicEngine/Ogre/ogrecontextmanager.h>
#include <Engine/GraphicEngine/Ogre/OgreWindowInputManager.h>

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
    for(Unite *unite : m_selection) {
        WorldObjectView *view = unite->view();
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
    clearSelection();
    m_selection = m_rtsState->getUnitesInRectangle(selectedAera);
    extractViews();
}

void RTSSelectionManager::selectSingleUnit()
{
    //TODO
}

bool RTSSelectionManager::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    if(id == OIS::MouseButtonID::MB_Left) {
        m_mouseDown = false;
        if(m_mouseMoved) {
            selectArea();
        } else {

        }
    }
    return true;
}

RTSSelectionManager::~RTSSelectionManager()
{
    OgreContextManager::get()->getInputManager()->delMouseListener(this);
}
