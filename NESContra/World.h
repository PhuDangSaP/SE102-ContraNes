#pragma once
#include "GameObject.h"
#include "Game.h"

class World
{
public:
	World();
	World(int l, int t, int r, int b);
	~World();
	void Build();
	void SetObjects(vector<LPGAMEOBJECT> objects) { this->objects = objects; }
	void GetObjectColliderWithWiewport(vector<LPGAMEOBJECT>& objects);
	void AddObjectToTree(LPGAMEOBJECT object);
private:
	World* leftNode;
	World* rightNode;
	int left;
	int right;
	int top;
	int bottom;
	vector<LPGAMEOBJECT> objects;
};
