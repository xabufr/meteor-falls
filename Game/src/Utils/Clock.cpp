#include "Clock.h"
#include <boost/date_time/posix_time/posix_time.hpp>

long Clock::getTime() const
{
	return getDuration().total_milliseconds();
}
boost::posix_time::time_duration Clock::getDuration() const
{
	boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
	boost::posix_time::time_duration time = now - *m_start;
	return time;
}
void Clock::setTime(long time)
{
	*m_start = boost::posix_time::second_clock::local_time() - boost::posix_time::milliseconds(time);
}
Clock::Clock() : m_start(new boost::posix_time::ptime())
{
	reset();
}
Clock::~Clock()
{
	delete m_start;
}
Clock::Clock(const Clock& o) : m_start(new boost::posix_time::ptime(*o.m_start))
{
}
void Clock::reset()
{
	*m_start = boost::posix_time::microsec_clock::local_time();
}
Clock& Clock::operator=(const Clock& o)
{
	delete m_start;
	m_start = new boost::posix_time::ptime(*o.m_start);
	return *this;
}
