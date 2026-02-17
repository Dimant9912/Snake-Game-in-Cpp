//ΟΜΑΔΑ ΕΡΓΑΣΙΑΣ C++:
// ΑΝΤΩΝΙΟΥ ΔΗΜΗΤΡΙΟΣ p3230011
// ΖΕΡΒΑΣ ΓΕΩΡΓΙΟΣ  p3230330

#include "graphics.h"
#include "GlobalState.h"

void update(float ms) {
    GlobalState::getInstance()->update(ms);
}

void draw() {
    GlobalState::getInstance()->draw();
}

int main() {
    graphics::createWindow(800, 600, "SGG Snake");

    GlobalState::getInstance()->init(); // Αρχικοποίηση παιχνιδιού

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(GlobalState::getInstance()->getCanvasWidth(), GlobalState::getInstance()->getCanvasHeight());
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    graphics::startMessageLoop();
    return 0;
}