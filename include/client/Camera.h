#ifndef TALLER_MICROMACHINES_CAMERA_H
#define TALLER_MICROMACHINES_CAMERA_H


#include "Renderizable.h"
#include "SDLWindow.h"
#include "CarLivesDrawer.h"
#include "SDLText.h"
#include "MudSplatter.h"
#include <string>

class Camera {
public:
    Camera();

    ~Camera();

    void prepare_frame();

    void render_object(Renderizable &object, float abs_x, float abs_y,
                       float angle = 0, int id = 0, float speed = 0);

    void show_frame();

    void set_center(float x, float y);

    void render_car_lives(int lives);


    void render_splatter();

    void render_name(std::string name);

    void render_podium(size_t position);

    void render_lapcount(int lapcount, int total_laps);

    SDLWindow window;
private:
    bool _is_in_frame(Renderizable &object, float abs_x, float abs_y);

    float center_x_cms;
    float center_y_cms;
    float center_x_px;
    float center_y_px;
    SDLText text_creator;
};


#endif //TALLER_MICROMACHINES_CAMERA_H
