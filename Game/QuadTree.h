#ifndef _QUAD_TREE_H_
#define _QUAD_TREE_H_

#include <SFML/System.hpp>
#include "EntityManager.h"
#include <vector>

///  hope to increase collision decetion speed with this one!!

// need to figure out how im going to do this...
struct NodeRect
{
    int x,  y,  w,  h;

    NodeRect()
    {
        x = y = w = h = 0;
    }

    NodeRect(int setX, int setY, int setW, int setH)
    :
    x(setX),
    y(setY),
    w(setW),
    h(setH)
    {
    }
};
struct Node
{
    Node* child[4];
    NodeRect area;
    std::vector<cell::Entity*> entity;

    bool pushed;

    ~Node()
    {
        if(child[0]) delete child[0];
        if(child[1]) delete child[1];
        if(child[2]) delete child[2];
        if(child[3]) delete child[3]; // becomes a recursive deallocation
    }

    Node()
    {
        child[0] = child[1] = child[2] = child[3] = NULL;
    }

    Node(int x, int y, int w, int h):
    area(x, y, w, h),
    pushed(false)
    {
        child[0] = child[1] = child[2] = child[3] = NULL;
    }

    Node(const NodeRect &setArea):
    area(area),
    pushed(false)
    {
         child[0] = child[1] = child[2] = child[3] = NULL;
    }

    void AddEntity(cell::Entity* _entity)
    {
        entity.push_back(_entity);
    }

};


// in the entity class create an OnCollision method
class QuadTree
{
    public:
        QuadTree(int levels, int width=640, int height=480);
        ~QuadTree();

        void Setup(Node* node, int levels = 2); // zero = 1x1 one = 4x4 two = 16x16 exc...

        void Update(EntityManager*);
        void CheckCollisions();

        void FindCell(Node* node, cell::Entity& entity);

        Node* GetNode(){ return m_node; }

    private:
        int m_levels;
        Node* m_node;

    public:

/// just for now
        std::vector<Node*> leafNodes; // for collision checking and stuff
        std::vector<Node*> collisionNodes;

};

#endif
