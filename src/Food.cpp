//ΟΜΑΔΑ ΕΡΓΑΣΙΑΣ C++:
// ΑΝΤΩΝΙΟΥ ΔΗΜΗΤΡΙΟΣ p3230011
// ΖΕΡΒΑΣ ΓΕΩΡΓΙΟΣ  p3230330

#include "Food.h"
#include "GlobalState.h"

Food::Food() {
    init();
}

void Food::init() {
    // Ζητάμε έναν τυχαίο κόμβο από τον Γράφο
    m_current_node = GlobalState::getInstance()->getRandomNode();
}

void Food::update() {}

void Food::draw() {
    if (m_current_node) {
        graphics::Brush br;
        br.fill_color[0] = 1.0f; br.fill_color[1] = 0.2f; br.fill_color[2] = 0.2f;
        br.outline_opacity = 0.0f;
        
        // Σχεδιάζουμε Κύκλο στη θέση του Κόμβου
        float cx = m_current_node->x + m_current_node->size/2;
        float cy = m_current_node->y + m_current_node->size/2;
        graphics::drawDisk(cx, cy, m_current_node->size/2, br);
    }
}