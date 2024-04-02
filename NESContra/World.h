#pragma once
#include "GameObject.h"
#include "Game.h"
extern CBill* bill;
class World
{
public:
	World();
	World(int l, int t, int r, int b);
	~World();
	void Build(World* w);
	void SetObjects(vector<LPGAMEOBJECT> objects) { this->objects = objects; }
	void GetObjectColliderWithWiewport(World * node, vector<LPGAMEOBJECT>& objects);
	void AddObjectToTree(LPGAMEOBJECT object, World* world);
private:
	World* leftNode;
	World* rightNode;
	int left;
	int right;
	int top;
	int bottom;
	vector<LPGAMEOBJECT> objects;
};

World::World()
{
	
}

World::World(int l, int t, int r, int b)
{
	this->leftNode = NULL;
	this->rightNode = NULL;
	this->left = l;
	this->top = t;
	this->right = r;
	this->bottom = b;
}

World::~World()
{
}


void World::Build(World* w)
{
	
	CGame* g = CGame::GetInstance();
	if (abs(w->right - w->left) >= g->GetBackBufferWidth() / 2 && w->objects.size() > 0)
	{
		w->leftNode = new World(w->left, w->top,w->left+ (w->right-w->left )/ 2, w->bottom);
		w->rightNode = new World(w->left + (w->right - w->left) / 2, w->top, w->right, w->bottom);
		for (int i = 0; i < w->objects.size(); i++)
		{
			float x = -1, y = -1;
			w->objects[i]->GetPosition(x, y);
			if (x >= w->left && x <= (float)(w->left + (w->right - w->left) / 2))
			{
				
				w->leftNode->objects.push_back(w->objects[i]);
			}
			else if (x > (float)(w->left + (w->right - w->left) / 2) && x <= w->right)
			{
				
				w->rightNode->objects.push_back(w->objects[i]);
			}
		}
		w->objects.clear();
		Build(w->leftNode);
		Build(w->rightNode);
	}
}
void World::GetObjectColliderWithWiewport(World* node, vector<LPGAMEOBJECT>& result)
{
	CGame* g = CGame::GetInstance();
	float camX, camY;
	g->GetCamera()->GetCamPos(camX, camY);
	if (node == nullptr)
		 return;

	if (node->right<=camX ||node->left>=g->GetBackBufferWidth() + camX)
		return;

	if (node->leftNode == nullptr && node->rightNode == nullptr && !node->objects.empty()) 
	{
		for (auto it = node->objects.begin(); it != node->objects.end(); ) 
		{
			LPGAMEOBJECT obj = *it;
			result.push_back(obj);
			if (obj->GetIsMovable())
				it = node->objects.erase(it);
			else
				++it;	
		}
	}
	else 
	{
		GetObjectColliderWithWiewport(node->leftNode, result);
		GetObjectColliderWithWiewport(node->rightNode, result);
	}
}

void World::AddObjectToTree(LPGAMEOBJECT object, World* world)
{
	float objX, objY;
	object->GetPosition(objX, objY);
	if (objX >= world->left && objX <= world->right ) 
	{
		if (world->leftNode != nullptr && world->rightNode != nullptr) 
		{
			if (objX <= (float)(world->left + world->right) / 2)
				AddObjectToTree(object, world->leftNode);
			else
				AddObjectToTree(object, world->rightNode);
		}
		world->objects.push_back(object);
	}
}




