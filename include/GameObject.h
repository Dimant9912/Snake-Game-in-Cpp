//ΟΜΑΔΑ ΕΡΓΑΣΙΑΣ C++:
// ΑΝΤΩΝΙΟΥ ΔΗΜΗΤΡΙΟΣ p3230011
// ΖΕΡΒΑΣ ΓΕΩΡΓΙΟΣ  p3230330

#pragma once
#include "graphics.h"

// Ορισμός Κόμβου Γράφου
struct Node {
    float x, y;      // Θέση για τη ζωγραφική
    float size;      // Μέγεθος κελιού
    
    // Κάθε κόμβος ξέρει ποιοι είναι οι γείτονές του
    Node* up = nullptr;
    Node* down = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;

    
    bool isWall = false; 
};

class GameObject {
public:
    virtual void update() = 0; 
    virtual void draw() = 0;   
    virtual void init() = 0;   
    virtual ~GameObject() {}   
};