#ifndef WORLDOBJECTIDENTIFIERPROVIDER_H
#define WORLDOBJECTIDENTIFIERPROVIDER_H

class WorldObjectIdentifierProvider
{
public:
    WorldObjectIdentifierProvider();
    unsigned int createId();
    unsigned int getLastCreatedId() const;
private:
    unsigned int m_last_id_created;
};

#endif // WORLDOBJECTIDENTIFIERPROVIDER_H
