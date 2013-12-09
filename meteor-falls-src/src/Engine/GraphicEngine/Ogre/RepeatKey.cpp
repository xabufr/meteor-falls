#include "RepeatKey.h"

RepeatKey::RepeatKey(float delay, float initial) : 
	m_code(OIS::KeyCode::KC_UNASSIGNED),
	m_repeatDelay(delay), 
	m_repeatInitialDelay(initial)
{
}
void RepeatKey::begin(const OIS::KeyEvent &evt)
{
	m_code    = evt.key;
	m_text    = evt.text;

	m_elapsed = 0.f;
	m_delay   = m_repeatInitialDelay;
}
void RepeatKey::end(const OIS::KeyEvent &evt)
{
	if(evt.key==m_code)
		m_code = OIS::KeyCode::KC_UNASSIGNED;
}
void RepeatKey::update(float time)
{
	if(m_code==OIS::KeyCode::KC_UNASSIGNED)
		return;
	m_elapsed += time;
	if(m_elapsed<m_delay) return;
	m_elapsed -= m_delay;
	m_delay    = m_repeatDelay;

	do
	{
		repeatKey(m_code, m_text);
		m_elapsed -= m_repeatDelay;
	}while(m_elapsed>=m_repeatDelay);
}
