#ifndef _HOME_THOMAS_METEOR_FALLS_SRC_UTILS_CLOCK_H__
#define _HOME_THOMAS_METEOR_FALLS_SRC_UTILS_CLOCK_H__

#include <boost/date_time/posix_time/posix_time_types.hpp>

class Clock
{
	public:
		boost::posix_time::time_duration getDuration() const;
		long getTime() const;
		void setTime(long);
		Clock();
		~Clock();
		Clock(const Clock&);
		void reset();
	private:
		boost::posix_time::ptime *m_start;
};

#endif 
