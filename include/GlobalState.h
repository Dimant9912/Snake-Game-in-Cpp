//ΟΜΑΔΑ ΕΡΓΑΣΙΑΣ C++:
// ΑΝΤΩΝΙΟΥ ΔΗΜΗΤΡΙΟΣ p3230011
// ΖΕΡΒΑΣ ΓΕΩΡΓΙΟΣ  p3230330

#pragma once
#include "graphics.h"
#include "GameObject.h"
#include <vector>
#include <string>

enum GameStatus {
    STATUS_START,
    STATUS_PLAYING,
    STATUS_PAUSED,
    STATUS_GAMEOVER
};

class GlobalState {
    static GlobalState* m_instance;
    std::vector<GameObject*> m_objects; 
    
    // GRAPH logic 
    std::vector<Node*> m_graph_nodes; // Όλοι οι κόμβοι του γράφου
    float m_block_size = 20.0f;
    int m_cols = 0;
    int m_rows = 0;

    GameStatus m_status = STATUS_START; 
    int m_score = 0; 

    std::string m_player_name = "";

    float m_input_timer = 0.0f;
    
    GlobalState() {} 

public:
    ~GlobalState();
    static GlobalState* getInstance();

    void init();
    void update(float ms);
    void draw();
    
    // Συνάρτηση για να χτίσουμε τον Γράφο
    void buildGraph();

    // Βοηθητικές
    // Βοηθητικές συναρτήσεις
    void setGameOver(bool go);
    float getCanvasWidth() { return 800.0f; }
    float getCanvasHeight() { return 600.0f; }
    
    // Πρόσβαση στον Γράφο 
    Node* getNodeAt(int col, int row);
    Node* getRandomNode(); // Για το φαγητό
};