#include "ChargeBinaryMap.h"
#include "../Exception/FileNotFound.h"
#include <fstream>
#include <iostream>
#include <math.h>

ChargeBinaryMap::ChargeBinaryMap()
{
    std::string nom[]={"X0Y0", "X0Y-1", "X0Y1", "X-1Y0", "X1Y0", "X-1Y-1", "X-1Y1", "X1Y-1", "X1Y1"};
    std::ifstream file;
    int taille;
    int pos=0;

    file.open("data/maps/default2/heightmap/Page"+nom[0]+".f32");
    if (!file)
        throw FileNotFound("data/maps/default2/heightmap/Page"+nom[0]+".f32");

    file.seekg(0, std::ios_base::end);
    taille = sqrt(file.tellg()/4);
    m_height_field_data = new float[int(taille*taille*9)];
    file.close();
    for (int i=0; i < taille; ++i)
    {
        for (int j=0; j<9; ++j)
        {
            file.open("data/maps/default2/heightmap/Page"+nom[j]+".f32");
            if (!file)
                throw FileNotFound("data/maps/default2/heightmap/Page"+nom[j]+".f32");

            file.seekg(i*sizeof(float),std::ios_base::beg);
            file.read((char *)(&m_height_field_data[pos]), sizeof(float));
            std::cout << m_height_field_data[pos] << std::endl;
            file.close();
            ++pos;
        }
    }
}

float *ChargeBinaryMap::getHeightFieldData()
{
    return m_height_field_data;
}
