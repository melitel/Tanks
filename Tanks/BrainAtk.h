#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <stack>
#include <set>
#include <array>

class BrainAtk
{
public:

    struct Node {
        int x, y;  // Coordinates of the node
        int f, g, h;  // Cost values of the node
        Node* parent;
        Node() {}
        Node(int x_, int y_, int f_, int g_, int h_, Node* parent_) :
            x(x_), y(y_), f(f_), g(g_), h(h_), parent(parent_) {}

        bool operator<(const Node& other) const {
            return f > other.f;
        }
    };

    std::vector<Node> a_star(int start_x, int start_y, int goal_x, int goal_y);

private:        

    bool tile_walkable(int tile_x, int tile_y);
    int heuristic(Node *current, int goal_x, int goal_y);

    std::vector<Node*> get_neighbors(Node *current);

    Node* create_node(uint32_t x, uint32_t y, Node* parent) {
        Node& node = m_node_pool[m_next_free_node++];
        node.f = 0;
        node.g = 0;
        node.h = 0;
        node.x = x;
        node.y = y;
        node.parent = parent;

        return &node;
    }

    std::array<Node, 2048> m_node_pool;
    uint32_t m_next_free_node{0};
};

