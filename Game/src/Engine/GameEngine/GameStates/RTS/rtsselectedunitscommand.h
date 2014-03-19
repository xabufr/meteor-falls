#ifndef RTSSELECTEDUNITSCOMMAND_H
#define RTSSELECTEDUNITSCOMMAND_H
#include <vector>
#include <set>

class WorldObject;
class TypeUnite;
class RTSState;
class RTSSelectedUnitsCommand
{
public:
    RTSSelectedUnitsCommand(RTSState *rtsState);
    void changeSelection(const std::vector<WorldObject *> &selection);
    void addBuild(const TypeUnite *type, int count);
    const std::set<const TypeUnite*> availableBuilds() const;

private:
    RTSState *m_rtsState;
    std::vector<WorldObject*> m_selection;
    std::set<const TypeUnite*> m_availableBuilds;
};

#endif // RTSSELECTEDUNITSCOMMAND_H
