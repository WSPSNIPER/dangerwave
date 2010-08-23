#include "QuadTree.h"
#include <fstream>
#include <iostream>
#include "bulletmanager.hpp"
#include "Player.h"

QuadTree::QuadTree(int levels, int width, int height)
:
m_levels(levels)
{
    m_node = new Node(0, 0, width, height);
    Setup(m_node, levels);
}

QuadTree::~QuadTree()
{
    if(m_node != NULL)
    {
        delete m_node;
    }
}

void QuadTree::Setup(Node* node, int levels)
{
    levels -= 1;
    if(levels >= 0)
    {
        node->child[0] = new Node(node->area.x, node->area.y, node->area.w/2, node->area.h/2);
        node->child[1] = new Node(node->area.x + node->area.w/2, node->area.y, node->area.w/2, node->area.h/2);
        node->child[2] = new Node(node->area.x, node->area.y + node->area.h/2, node->area.w/2, node->area.h/2);
        node->child[3] = new Node(node->area.x + node->area.w/2, node->area.y + node->area.h/2, node->area.w/2, node->area.h/2);

        for(int i = 0; i < 4; i++)
        {
            Setup(node->child[i], levels);  // recursive method lol
        }
    }
    else
    {
        this->leafNodes.push_back(node); // its a leaf node !!
    }
}

void QuadTree::CheckCollisions()
{
    for(unsigned int i = 0; i < collisionNodes.size(); i++)
    {
        for(unsigned int n = 0; n < collisionNodes[i]->entity.size(); n++)
        {
            if(!collisionNodes[i]->entity[n]->Dead())
            {
                for(unsigned int z = 0; z < collisionNodes[i]->entity.size(); z++)
                {
                    if(z != n && !collisionNodes[i]->entity[z]->Dead())
                    {
                        if(collisionNodes[i]->entity[n]->Collision(collisionNodes[i]->entity[z]->GetRect()))
                        {
                            collisionNodes[i]->entity[n]->OnCollision(collisionNodes[i]->entity[z]);
                        }
                    }
                }
            }
        }
    }
}

void QuadTree::Update(EntityManager* mgr)
{

    for(unsigned int i = 0; i < leafNodes.size(); i++)
    {
        leafNodes[i]->entity.clear();
        leafNodes[i]->pushed = false;
    }

    collisionNodes.clear();
    for(unsigned int i = 0; i< mgr->GetVector().size(); i++)
    {
        FindCell(m_node, *mgr->GetEntity(i));
    }

}

void QuadTree::FindCell(Node* node, cell::Entity& entity)
{
    if(node->child[0])
    {
        // cant use if else because the rect could be in multiple nodes
        if(node->child[0]->area.contains(entity.GetRect().x, entity.GetRect().y));
        {
            FindCell(node->child[0], entity);
        }
        if(node->child[1]->area.contains(entity.GetRect().right(), entity.GetRect().y));
        {
            FindCell(node->child[1], entity);
        }
        if(node->child[2]->area.contains(entity.GetRect().x, entity.GetRect().bottom()));
        {
            FindCell(node->child[2], entity);
        }
        if(node->child[3]->area.contains(entity.GetRect().right(), entity.GetRect().bottom()));
        {
            FindCell(node->child[3], entity);
        }
    }
    else
    {
        node->AddEntity(&entity);
        if(!node->pushed)
        {
            collisionNodes.push_back(node); // if it has an entity check it for collision
            node->pushed = true;
        }
    }



}
