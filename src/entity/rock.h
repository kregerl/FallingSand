#ifndef OPENGLFALLINGSAND_ROCK_H
#define OPENGLFALLINGSAND_ROCK_H


#include "entity.h"

class Rock : public Entity {
private:
    typedef Entity super;

    int m_gravity;
public:
    Rock(glm::vec2 offset);

    Rock(Entity *entity);

    ~Rock();

    void StepEntity(std::vector<std::vector<Entity *>> &entities, int i, int j) override;
};


#endif //OPENGLFALLINGSAND_ROCK_H
