#ifndef OPENGLFALLINGSAND_FIRE_H
#define OPENGLFALLINGSAND_FIRE_H

#include "entity.h"

class Fire : public Entity {
private:
    typedef Entity super;

    int m_spreadFactor;
public:
    Fire(glm::vec2 offset);

    Fire(Entity *entity);

    ~Fire();

    void StepEntity(std::vector<std::vector<Entity *>> &entities, int i, int j) override;
};


#endif //OPENGLFALLINGSAND_FIRE_H
