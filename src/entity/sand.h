#ifndef OPENGLFALLINGSAND_SAND_H
#define OPENGLFALLINGSAND_SAND_H

#include "entity.h"

class Sand : public Entity {
private:

    typedef Entity super;

    int m_gravity;
    int m_spreadFactor;
public:

    Sand(glm::vec2 offset);

    Sand(Entity *entity);

    ~Sand();

    void StepEntity(std::vector<std::vector<Entity *>> &entities, int i, int j) override;

    glm::vec3 GetColor() override;

    void InitColor();

};


#endif //OPENGLFALLINGSAND_SAND_H
