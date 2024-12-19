#include "NPCSystems.h"

float NPCMovementSystem::calculateHeuristic(int x1, int y1, int x2, int y2)
{

    return std::abs(x1 - x2) + std::abs(y1 - y2);
    
}

bool NPCMovementSystem::isValid(int x, int y)
{
    return x >= 0 && x < width && y >= 0 && y < height;
}

bool NPCMovementSystem::isWalkable(int x, int y)
{
    return !(grid[y * width + x] & WALL);
}

void NPCMovementSystem::setVisited(int x, int y)
{
    grid[y * width + x] |= VISITED;
}

bool NPCMovementSystem::isVisited(int x, int y)
{
    return grid[y * width + x] & VISITED;
}

void NPCMovementSystem::setWall(int x, int y)
{
    if (isValid(x, y))
    {
        grid[y * width + x] |= WALL;
    }
}

void NPCMovementSystem::clearCell(int x, int y)
{
    if (isValid(x, y))
    {
        grid[y * width + x] = EMPTY;
    }
}

std::vector<std::pair<int, int>> NPCMovementSystem::findPath(int startX, int startY, int endX, int endY)
{
      // Reset visited states
        for (int i = 0; i < width * height; ++i)
        {
            grid[i] &= ~VISITED;
        }
        
        std::priority_queue<Node*, std::vector<Node*>, std::greater<Node*>> openSet;
        std::unordered_map<int, Node*> nodeMap;  // For memory management
        
        // Create start node
        Node* startNode = new Node{startX, startY, 0.0f, 
            calculateHeuristic(startX, startY, endX, endY), nullptr};
        openSet.push(startNode);
        nodeMap[startY * width + startX] = startNode;
        
        // Direction arrays for 8-directional movement
        const int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
        const int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        
        while (!openSet.empty())
        {
            Node* current = openSet.top();
            openSet.pop();
            
            // Check if we reached the end
            if (current->x == endX && current->y == endY)
            {
                // Reconstruct path
                std::vector<std::pair<int, int>> path;
                while (current != nullptr)
                {
                    path.emplace_back(current->x, current->y);
                    current = current->parent;
                }
                
                // Cleanup
                for (auto& pair : nodeMap)
                {
                    delete pair.second;
                }
                
                std::reverse(path.begin(), path.end());
                return path;
            }
            
            setVisited(current->x, current->y);
            
            // Check all neighbors
            for (int i = 0; i < 8; ++i)
            {
                int newX = current->x + dx[i];
                int newY = current->y + dy[i];
                
                if (!isValid(newX, newY) || !isWalkable(newX, newY) || isVisited(newX, newY))
                {
                    continue;
                }
                
                // Calculate new costs
                float moveCost = (i < 4) ? 1.0f : 1.414f;  // Diagonal movement costs more
                float newG = current->g_cost + moveCost;
                float newH = calculateHeuristic(newX, newY, endX, endY);
                
                int nodeKey = newY * width + newX;
                Node* neighbor = nodeMap[nodeKey];
                
                if (neighbor == nullptr)
                {
                    neighbor = new Node{newX, newY, newG, newH, current};
                    nodeMap[nodeKey] = neighbor;
                    openSet.push(neighbor);
                }
                else if (newG < neighbor->g_cost)
                {
                    neighbor->g_cost = newG;
                    neighbor->parent = current;
                }
            }
        }
        
        // No path found
        for (auto& pair : nodeMap)
        {
            delete pair.second;
        }
        return std::vector<std::pair<int, int>>();
}
