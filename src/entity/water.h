#ifndef OPENGLFALLINGSAND_WATER_H
#define OPENGLFALLINGSAND_WATER_H


#include "entity.h"
#include "../world.h"

class Water : public Entity {
private:
    typedef Entity super;

    int m_gravity;
public:
    Water(glm::vec2 offset);

    Water(Entity *entity);

    ~Water();

    void StepEntity(std::vector<std::vector<Entity *>> &entities, int i, int j) override;

    glm::vec3 GetColor() override;

    void InitColor();

};


#endif //OPENGLFALLINGSAND_WATER_H
