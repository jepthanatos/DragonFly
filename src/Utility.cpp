#include "Utility.h"

namespace df
{

    bool valueInRange(float value, float min, float max)
    {
        return (value >= min) && (value <= max);
    }

    // bool boxIntersectsBox(Box box1, Box box2)
    //{
    //     return !((box1.getHorizontal() > box2.getRight()) ||
    //              (box1.getRight() < box2.getHorizontal()) ||
    //              (box1.getVertical() > box2.getBottom()) ||
    //              (box1.getBottom() < box2.getVertical()));
    // }
    //
    // Box getWorldBox(const std::shared_ptr<Object>p_o)
    //{
    //    Vector pos = p_o->getPosition();
    //    Box box = p_o->getBox();
    //    return Box(pos.getX() + box.getHorizontal(),
    //               pos.getY() + box.getVertical(),
    //               pos.getX() + box.getRight(),
    //               pos.getY() + box.getBottom());
    //}
    //
    // Box getWorldBox(const std::shared_ptr<Object>p_o, Vector where)
    //{
    //    Box box = p_o->getBox();
    //    return Box(where.getX() + box.getHorizontal(),
    //               where.getY() + box.getVertical(),
    //               where.getX() + box.getRight(),
    //               where.getY() + box.getBottom());
    //}

    Vector worldToView(Vector world_pos)
    {
        return world_pos;
    }

    bool positionsIntersect(Vector p1, Vector p2)
    {
        if (abs(p1.getX() - p2.getX()) <= 1 && abs(p1.getY() - p2.getY()) <= 1)
            return true;
        else
            return false;
    }
}