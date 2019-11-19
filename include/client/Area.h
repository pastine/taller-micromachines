//
// Created by casimiro on 17/10/19.
//

#ifndef TALLER_MICROMACHINES_AREA_H
#define TALLER_MICROMACHINES_AREA_H


class Area {
public:
    Area(int x, int y, int width, int height);

    int getX() const;

    int getY() const;

    int getWidth() const;

    int getHeight() const;

private:
    int x, y;
    int width, height;
};


#endif //TALLER_MICROMACHINES_AREA_H
