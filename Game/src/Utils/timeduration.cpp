#include "timeduration.h"
#include <SFML/System/Time.hpp>

TimeDuration::TimeDuration(): totalMilliseconds(0), totalSeconds(0.f)
{
}

TimeDuration::TimeDuration(const sf::Time &time): totalMilliseconds(time.asMilliseconds()), totalSeconds(time.asSeconds())
{
}

float TimeDuration::seconds() const
{
    return totalSeconds;
}

int TimeDuration::milliseconds() const
{
    return totalMilliseconds;
}

TimeDuration TimeDuration::fromMilliseconds(int millisec)
{
    TimeDuration duration;
    duration.totalMilliseconds = millisec;
    duration.totalSeconds = millisec * 0.001;
    return duration;
}

TimeDuration TimeDuration::fromSeconds(float seconds)
{
    TimeDuration duration;
    duration.totalMilliseconds = seconds * 1000;
    duration.totalSeconds = seconds;
    return duration;
}
