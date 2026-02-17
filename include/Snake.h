//ΟΜΑΔΑ ΕΡΓΑΣΙΑΣ C++:
// ΑΝΤΩΝΙΟΥ ΔΗΜΗΤΡΙΟΣ p3230011
// ΖΕΡΒΑΣ ΓΕΩΡΓΙΟΣ  p3230330

#pragma once
#include "GameObject.h"
#include <vector>

// Κατευθύνσεις ως Enum για τον Γράφο
enum Direction { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT, DIR_NONE };

class Snake : public GameObject {
    

    Node* m_head_node = nullptr;      // Πού είναι το κεφάλι (δείκτης σε κόμβο)
    std::vector<Node*> m_tail_nodes;  // Η ουρά είναι λίστα από δείκτες
    
    Direction m_current_dir = DIR_NONE;
    Direction m_next_dir = DIR_NONE;  // Buffer για να μην γυρνάει απότομα

    float m_move_timer = 0.0f; 
    float m_move_delay = 0.2f; 

public:
    Snake(); 
    void update() override;
    void draw() override;
    void init() override;

    void grow();
    
    // Getter για να βλέπει το GlobalState πού είμαστε
    Node* getHeadNode() { return m_head_node; }
};