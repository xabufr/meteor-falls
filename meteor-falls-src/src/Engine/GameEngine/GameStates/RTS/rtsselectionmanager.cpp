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
#include <OgreOverlay.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayElement.h>
#include <OgreOverlayContainer.h>

#include "../../ClientGameEngine.h"
#include "../../../EngineManager/EngineManager.h"
#include "../../../GraphicEngine/GraphicEngine.h"
#include "../../Map/selectionbillboardmanager.h"

RTSSelectionManager::RTSSelectionManager(RTSState *rtsState)
{
    m_mouseDown = false;
    m_mouseMoved = false;
    m_rtsState = rtsState;
    OgreContextManager::get()->getInputManager()->addMouseListener(this);
    Ogre::OverlayManager &overlayManager = Ogre::OverlayManager::getSingleton();
    m_overlaySelection = overlayManager.create("selection");
    m_containerSelection = static_cast<Ogre::OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelSelection"));
    m_containerSelection->setPosition(0,0);
    m_containerSelection->setDimensions(0.5,0.5);
    m_containerSelection->setMaterialName("Selection/Overlay");
    m_overlaySelection->add2D(m_containerSelection);
}

Vector2D<float> RTSSelectionManager::getMouseCoord()
{
    return CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getDisplayIndependantPosition();
}

bool RTSSelectionManager::mouseMoved(const OIS::MouseEvent &arg)
{
    if(m_mouseDown) {
        Vector2D<float> position = getMouseCoord();
        m_containerSelection->setPosition(std::min(position.x, m_startPosition.x), std::min(position.y, m_startPosition.y));
        m_containerSelection->setDimensions(std::abs(m_startPosition.x - position.x), std::abs(m_startPosition.y - position.y));
        m_overlaySelection->show();
    }

    m_mouseMoved = true;
    return true;
}

bool RTSSelectionManager::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    if(id == OIS::MouseButtonID::MB_Left) {
        m_mouseDown = true;
        m_mouseMoved = false;
        m_startPosition = getMouseCoord();
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
        m_rtsState->game()->selectionBillboardManager()->remove(view);
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
            m_rtsState->game()->selectionBillboardManager()->add(view, "Selection/Circle", Ogre::ColourValue::Green);
        }
    }
}

void RTSSelectionManager::selectArea()
{
    Vector2D<float> endPosition = getMouseCoord();
    Rectangle<float> selectedAera(m_startPosition, endPosition);
    std::vector<Unite *> unitesInRectangle = m_rtsState->getUnitesInRectangleUnderCamera(selectedAera);
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
        m_overlaySelection->hide();
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
