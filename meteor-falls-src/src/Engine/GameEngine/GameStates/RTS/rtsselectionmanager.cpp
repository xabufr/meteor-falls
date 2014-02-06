#include "rtsselectionmanager.h"
#include "../RTSState.h"
#include <Utils/rectangle.h>
#include "../../Map/WorldObjectView.h"
#include "../../Map/WorldObject.h"

#include <Engine/GraphicEngine/Ogre/ogrecontextmanager.h>
#include <Engine/GraphicEngine/Ogre/OgreWindowInputManager.h>
#include <Engine/GraphicEngine/Ogre/OgreApplication.h>

#include <OgreRay.h>
#include <OgreBillboardSet.h>
#include <OgreBillboard.h>

#include "../../ClientGameEngine.h"
#include "../../../EngineManager/EngineManager.h"
#include "../../../GraphicEngine/GraphicEngine.h"

RTSSelectionManager::RTSSelectionManager(RTSState *rtsState)
{
    m_mouseDown = false;
    m_mouseMoved = false;
    m_rtsState = rtsState;
    OgreContextManager::get()->getInputManager()->addMouseListener(this);
    m_selectionProjection = m_rtsState->game()->getProjectiveDecalsManager()->addSimple(ProjectiveDecalsManager::DecalProperties("selection.png", Ogre::ColourValue(255,255,255), 0.f));
}

bool RTSSelectionManager::mouseMoved(const OIS::MouseEvent &arg)
{
    if(m_mouseDown) {
        m_selectionProjection->setVisible(true);
        ProjectiveDecalsManager::DecalProperties &properties = m_selectionProjection->getProperties();
        Vector2D<float> mouse = getMouseCoordOnMap();
        properties.size = m_startPosition - mouse;
        properties.position = m_startPosition - properties.size / 2.f;
        m_selectionProjection->update();
    }

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
        m_rtsState->game()->getProjectiveDecalsManager()->remove(view);
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
            m_rtsState->game()->getProjectiveDecalsManager()->add(view);
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
        m_selectionProjection->setVisible(false);
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
    m_rtsState->game()->getProjectiveDecalsManager()->remove(m_selectionProjection);
}
