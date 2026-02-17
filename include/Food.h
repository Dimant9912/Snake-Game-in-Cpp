//ΟΜΑΔΑ ΕΡΓΑΣΙΑΣ C++:
// ΑΝΤΩΝΙΟΥ ΔΗΜΗΤΡΙΟΣ p3230011
// ΖΕΡΒΑΣ ΓΕΩΡΓΙΟΣ  p3230330

#pragma once
#include "GameObject.h"

class Food : public GameObject {
    Node* m_current_node = nullptr; // Δείκτης στον κόμβο που βρίσκεται το φαι
public:
    Food();
    void update() override;
    void draw() override;
    void init() override;
    
    Node* getNode() { return m_current_node; }
};