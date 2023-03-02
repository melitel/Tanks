#include "BrainAtk.h"
#include "Game.h"
#include <queue>

extern Game* g_Game;

bool BrainAtk::tile_walkable(int tile_x, int tile_y)
{
    bool get_tile_walkable = g_Game->m_map->get_tile_walkable_by_indices(tile_x, tile_y);

    return get_tile_walkable;
}

int BrainAtk::heuristic(Node *current, int goal_x, int goal_y)
{
    return abs(current->x - goal_x) + abs(current->y - goal_y);
}

std::vector<BrainAtk::Node*> BrainAtk::get_neighbors(Node *n)
{
    std::vector<Node*> neighbors;
    int x = n->x;
    int y = n->y;
    int rows = g_Game->m_map->get_rows();
    int cols = g_Game->m_map->get_columns();

    if (x > 0 && tile_walkable(x - 1, y)) {
        neighbors.push_back(create_node(x -1, y, n, 3));
    }
    if (x < rows - 1 && tile_walkable(x + 1, y)) {
        neighbors.push_back(create_node(x + 1, y, n, 2));
    }
    if (y > 0 && tile_walkable(x, y - 1)) {
        neighbors.push_back(create_node(x, y -1, n, 0));
    }
    if (y < cols - 1 && tile_walkable(x, y + 1)) {
        neighbors.push_back(create_node(x, y+1, n, 1));
    }
    return neighbors;
}

std::vector<BrainAtk::Node> BrainAtk::a_star(int start_x, int start_y, int goal_x, int goal_y) {
    
    // Using lambda to compare elements.
    auto cmp = [](Node* left, Node* right) { return left->f > right->f; };
    std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> frontier(cmp);


    Node *start = create_node(start_x, start_y, nullptr, 1);
    Node *goal = create_node(goal_x, goal_y, nullptr, 1);
    frontier.push(start);

    
    const int rows = g_Game->m_map->get_rows();
    const int cols = g_Game->m_map->get_columns();
    
    std::vector<std::vector<int>> visited(rows, std::vector<int>(cols, 0));
    visited[start->x][start->y] = 1;

    while (!frontier.empty()) {
        Node *current = frontier.top();
        //std::cout << current.x << " - " << current.y << std::endl;
        frontier.pop();

        // Check if the current node is the goal
        if (current->x == goal->x && current->y == goal->y) {
            // Construct the path by following the parent pointers
            std::vector<Node> path;
            while (current->parent != nullptr) {
                path.push_back(*current);
                current = current->parent;
            }
            path.push_back(*start);
            reverse(path.begin(), path.end());

            for (int i = 0; i < path.size(); ++i) {

                std::cout << path[i].x << " - " << path[i].y << std::endl;
            }
            m_next_free_node = 0;

            return path;
        }
        auto neighbors = get_neighbors(current);
        for (Node *neighbor : neighbors) {

            int new_g = current->g + 1;

            if (!visited[neighbor->x][neighbor->y] || new_g < neighbor->g) {
                neighbor->g = new_g;
                neighbor->h = heuristic(neighbor, goal_x, goal_y);
                neighbor->f = neighbor->g + neighbor->h;
              
                neighbor->parent = current;

                frontier.push(neighbor);
                visited[neighbor->x][neighbor->y] = 1;
            }
        }
    }

    return std::vector<Node>();
}
