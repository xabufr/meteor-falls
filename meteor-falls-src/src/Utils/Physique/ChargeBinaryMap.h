#ifndef CHARGEBINARYMAP_H_INCLUDED
#define CHARGEBINARYMAP_H_INCLUDED

class ChargeBinaryMap
{
public:
    ChargeBinaryMap();
    float *getHeightFieldData();
private:
    float *m_height_field_data;
};
#endif // CHARGEBINARYMAP_H_INCLUDED
