#ifndef MAP_H
#define MAP_H

#include <string>
#include <iostream>

class Map
{
    public:
        Map();
        virtual ~Map();
        void load(std::string p_name);
        std::string getName();
        void update();

    protected:

    private:
        std::string m_name;
        int m_size_x;
        int m_size_y;
        int m_size_z;
        bool m_cycle_enable;
        int m_cycle_duration;
        int m_cycle_hour;


};

#endif // MAP_H
