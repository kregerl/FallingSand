#ifndef OPENGLFALLINGSAND_WOOD_H
#define OPENGLFALLINGSAND_WOOD_H

#include "entity.h"


class Wood : public Entity {
private:
    typedef Entity super;

    int m_gravity;
public:
    Wood(glm::vec2 offset);

    Wood(Entity *entity);

    ~Wood();

    void StepEntity(std::vector<std::vector<Entity *>> &entities, int i, int j) override;
};


#endif //OPENGLFALLINGSAND_WOOD_H
