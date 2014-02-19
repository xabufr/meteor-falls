#ifndef TIMEDURATION_H
#define TIMEDURATION_H

namespace sf {
    class Time;
}
class TimeDuration
{
public:
    TimeDuration();
    TimeDuration(const sf::Time &time);
    float seconds() const;
    int milliseconds() const;

    static TimeDuration fromMilliseconds(int millisec);
    static TimeDuration fromSeconds(float seconds);

private:
    int totalMilliseconds;
    float totalSeconds;
};

#endif // TIMEDURATION_H
