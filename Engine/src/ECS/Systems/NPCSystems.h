#pragma once
#include "Systems.h"
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>

struct NPCSystems
{
public:
    
};

// Grid cell states using bitwise flags
enum CellFlags {
    EMPTY = 0,
    WALL = 1 << 0,
    VISITED = 1 << 1,
    PATH = 1 << 2
};

struct Node {
    int x, y;
    float g_cost;  // Cost from start to current node
    float h_cost;  // Estimated cost from current node to end
    Node* parent;
    
    float f_cost() const { return g_cost + h_cost; }
    
    bool operator>(const Node& other) const {
        return f_cost() > other.f_cost();
    }
};

class NPCMovementSystem : public ISystem
{
private:
    int width, height;
    std::vector<unsigned char> grid;  // Using bitwise flags for cell states
    
    // Helper function to calculate heuristic (Manhattan distance)
    float calculateHeuristic(int x1, int y1, int x2, int y2);
    
    bool isValid(int x, int y);
    
    bool isWalkable(int x, int y);
    
    void setVisited(int x, int y);
    
    bool isVisited(int x, int y);

public:
    NPCMovementSystem(int w, int h) : width(w), height(h) {
        grid.resize(width * height, EMPTY);
    }
    
    void setWall(int x, int y);
    
    void clearCell(int x, int y);
    
    std::vector<std::pair<int, int>> findPath(int startX, int startY, int endX, int endY);

    void Update(float deltaTime) override;
};
