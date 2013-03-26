#ifndef H_REPEATKEY_H
#define H_REPEATKEY_H
#include <OIS/OIS.h>

class RepeatKey
{
public:
	RepeatKey(float repeatDelay = 0.035f, float initialDelay = 0.3f);

	void begin(const OIS::KeyEvent &evt);
	void end(const OIS::KeyEvent &evt);
	void update(float time);
protected:
	virtual void repeatKey(OIS::KeyCode code, unsigned int text)=0;
private:
	unsigned int m_text;
	OIS::KeyCode m_code;

	float m_elapsed, m_delay;

	float m_repeatDelay, m_repeatInitialDelay;
};

#endif 
