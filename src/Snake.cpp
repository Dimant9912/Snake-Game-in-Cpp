//ΟΜΑΔΑ ΕΡΓΑΣΙΑΣ C++:
// ΑΝΤΩΝΙΟΥ ΔΗΜΗΤΡΙΟΣ p3230011
// ΖΕΡΒΑΣ ΓΕΩΡΓΙΟΣ  p3230330

#include "Snake.h"
#include "GlobalState.h" 

Snake::Snake() {
    init();
}

void Snake::init() {
    m_move_timer = 0.0f;
    m_move_delay = 100.0f;
    m_current_dir = DIR_RIGHT;
    m_next_dir = DIR_RIGHT;
    m_tail_nodes.clear(); 

    // Ξεκινάμε από έναν κόμβο στη μέση του γράφου
    
    Node* startNode = GlobalState::getInstance()->getNodeAt(10, 10);
    if (startNode) {
        m_head_node = startNode;
        
        // Φτιάχνουμε  ουρά προς τα αριστερά
        Node* t1 = startNode->left;
        if (t1) { m_tail_nodes.push_back(t1); if (t1->left) m_tail_nodes.push_back(t1->left); }
    }
}

void Snake::update() {
    // Αποθήκευση επόμενης κατεύθυνσης
    if (graphics::getKeyState(graphics::SCANCODE_UP) && m_current_dir != DIR_DOWN) m_next_dir = DIR_UP;
    if (graphics::getKeyState(graphics::SCANCODE_DOWN) && m_current_dir != DIR_UP) m_next_dir = DIR_DOWN;
    if (graphics::getKeyState(graphics::SCANCODE_LEFT) && m_current_dir != DIR_RIGHT) m_next_dir = DIR_LEFT;
    if (graphics::getKeyState(graphics::SCANCODE_RIGHT) && m_current_dir != DIR_LEFT) m_next_dir = DIR_RIGHT;

    // Timer
    m_move_timer += graphics::getDeltaTime();
    if (m_move_timer >= m_move_delay) {
        m_move_timer = 0.0f;
        m_current_dir = m_next_dir;

        // Βρίσκουμε τον ΕΠΟΜΕΝΟ ΚΟΜΒΟ μέσω των δεικτών 
        Node* nextNode = nullptr;
        
        if (m_head_node) {
            switch (m_current_dir) {
                case DIR_UP:    nextNode = m_head_node->up; break;
                case DIR_DOWN:  nextNode = m_head_node->down; break;
                case DIR_LEFT:  nextNode = m_head_node->left; break;
                case DIR_RIGHT: nextNode = m_head_node->right; break;
            }
        }

        // Έλεγχος: Υπάρχει κόμβος, Αν όχι, είναι τοίχος  nullptr
        if (nextNode == nullptr) {
            GlobalState::getInstance()->setGameOver(true);
            return;
        }

        // Έλεγχος: Χτυπήσαμε ουρά;
        for (auto* tailNode : m_tail_nodes) {
            if (nextNode == tailNode) {
                GlobalState::getInstance()->setGameOver(true);
                return;
            }
        }

        // Κίνηση Ουράς
        if (!m_tail_nodes.empty()) {
            // Μετακινούμε όλα τα κομμάτια μια θέση μπροστά
            for (size_t i = m_tail_nodes.size() - 1; i > 0; i--) {
                m_tail_nodes[i] = m_tail_nodes[i - 1];
            }
            m_tail_nodes[0] = m_head_node; // Το πρώτο κομμάτι πάει εκεί που ήταν το κεφάλι
        }

        // Κίνηση Κεφαλιού
        m_head_node = nextNode;
    }
}

void Snake::draw() {
    graphics::Brush br;
    br.outline_opacity = 0.0f;

    // ΣΧΕΔΙΑΣΗ ΟΥΡΑΣ 
    br.fill_color[0] = 0.0f; br.fill_color[1] = 1.0f; br.fill_color[2] = 0.0f; //Πράσινο

    for (auto* node : m_tail_nodes) {
        graphics::drawRect(node->x + node->size/2, node->y + node->size/2, node->size, node->size, br);
    }

    // ΣΧΕΔΙΑΣΗ ΚΕΦΑΛΙΟΥ ME ΜΑΤΙΑ
    if (m_head_node) {
        float cx = m_head_node->x + m_head_node->size/2;
        float cy = m_head_node->y + m_head_node->size/2;

        
        float rotation = 0.0f;
        if (m_current_dir == DIR_UP) rotation = -90.0f;
        else if (m_current_dir == DIR_DOWN) rotation = 90.0f;
        else if (m_current_dir == DIR_LEFT) rotation = 180.0f;
        else if (m_current_dir == DIR_RIGHT) rotation = 0.0f;

        // Περιστρέφουμε το κεφάλι
        graphics::setOrientation(rotation);

        // Ζωγραφίζουμε το πράσινο κουτί του κεφαλιού
        br.fill_color[0] = 0.0f; br.fill_color[1] = 1.0f; br.fill_color[2] = 0.0f;
        graphics::drawRect(cx, cy, m_head_node->size, m_head_node->size, br);

        // ΜΑΤΙΑ φυδιου
        graphics::Brush eye_brush;
        eye_brush.fill_color[0] = 1.0f; eye_brush.fill_color[1] = 1.0f; eye_brush.fill_color[2] = 1.0f; // Λευκό
        eye_brush.outline_opacity = 0.0f;
        
        
        
        graphics::drawDisk(cx + 4, cy - 4, 3, eye_brush);
     
        graphics::drawDisk(cx + 4, cy + 4, 3, eye_brush);

        // Μαύρες κουκκίδες ματιων
        graphics::Brush pupil_brush;
        pupil_brush.fill_color[0] = 0.0f; pupil_brush.fill_color[1] = 0.0f; pupil_brush.fill_color[2] = 0.0f; //black color
        pupil_brush.outline_opacity = 0.0f;

        
        graphics::drawDisk(cx + 6, cy - 4, 1.5f, pupil_brush);
        graphics::drawDisk(cx + 6, cy + 4, 1.5f, pupil_brush);

        
        graphics::resetPose();
    }
}

void Snake::grow() {
    // Προσθέτουμε έναν κόμβο
    if (!m_tail_nodes.empty())
        m_tail_nodes.push_back(m_tail_nodes.back());
    else
        m_tail_nodes.push_back(m_head_node);
}