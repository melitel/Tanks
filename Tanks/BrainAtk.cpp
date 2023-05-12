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
    if (x < (cols - 1) && tile_walkable(x + 1, y)) {
        neighbors.push_back(create_node(x + 1, y, n, 2));
    }
    if (y > 0 && tile_walkable(x, y - 1)) {
        neighbors.push_back(create_node(x, y -1, n, 1));
    }
    if (y < (rows - 1) && tile_walkable(x, y + 1)) {
        neighbors.push_back(create_node(x, y+1, n, 0));
    }
    return neighbors;
}

std::vector<BrainAtk::Node*> BrainAtk::get_goal_node(Node* n)
{
    std::vector<Node*> goal_nodes;
    int x = n->x;
    int y = n->y;
    int rows = g_Game->m_map->get_rows();
    int cols = g_Game->m_map->get_columns();

    if (x > 1 && tile_walkable(x - 2, y)) {
        goal_nodes.push_back(create_node(x - 2, y, nullptr, 3));
    }
    if (x < (cols - 2) && tile_walkable(x + 2, y)) {
        goal_nodes.push_back(create_node(x + 2, y, nullptr, 2));
    }
    if (y > 1 && tile_walkable(x, y - 2)) {
        goal_nodes.push_back(create_node(x, y - 2, nullptr, 1));
    }
    if (y < (rows - 2) && tile_walkable(x, y + 2)) {
        goal_nodes.push_back(create_node(x, y + 2, nullptr, 0));
    }
    return goal_nodes;
}

std::vector<BrainAtk::Node> BrainAtk::a_star(int start_x, int start_y, int target_x, int target_y, int tank_i) {
    m_next_free_node = 0;
    sf::Angle ai_tank_angle = g_Game->m_ai_tanks[tank_i].getRotation();
    int direction = 1;
    if (ai_tank_angle == sf::degrees(0.f)) {
        direction = 0;    
    }
    if (ai_tank_angle == sf::degrees(-90.f)) {
        direction = 2;
    }
    if (ai_tank_angle == sf::degrees(90.f)) {
        direction = 3;
    }
    if (ai_tank_angle == sf::degrees(-180.f)) {
        direction = 1;
    }
    Node *start = create_node(start_x, start_y, nullptr, direction);
    Node *target = create_node(target_x, target_y, nullptr, 0);
    auto goal_nodes = get_goal_node(target);
    std::vector<Node> path;
    
    for (Node* goal : goal_nodes) {
        
        // Using lambda to compare elements.
        auto cmp = [](Node* left, Node* right) { return left->f > right->f; };
        std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> frontier(cmp);

        frontier.push(start);

        const int rows = g_Game->m_map->get_rows();
        const int cols = g_Game->m_map->get_columns();

        std::vector<std::vector<int>> visited(cols, std::vector<int>(rows, 0));
        visited[start->x][start->y] = 1;

        while (!frontier.empty()) {

            Node* current = frontier.top();
            frontier.pop();

            // Check if the current node is the goal
            if (current->x == goal->x && current->y == goal->y) {
                // Construct the path by following the parent pointers
                std::vector<Node> path_temp;
                while (current->parent != nullptr) {
                    path_temp.push_back(*current);
                    current = current->parent;
                }
                path_temp.push_back(*start);
                reverse(path_temp.begin(), path_temp.end());              

                if (path_temp.size() < path.size() || path.size() == 0) {
                    path = path_temp;
                }
            }

            auto neighbors = get_neighbors(current);
            for (Node* neighbor : neighbors) {

                int new_g = current->g + 1;

                if (!visited[neighbor->x][neighbor->y] || new_g < neighbor->g) {
                    neighbor->g = new_g;
                    neighbor->h = heuristic(neighbor, goal->x, goal->y);
                    neighbor->f = neighbor->g + neighbor->h;

                    neighbor->parent = current;

                    frontier.push(neighbor);
                    visited[neighbor->x][neighbor->y] = 1;
                }
            }
        }    
    }

    return path;
}
