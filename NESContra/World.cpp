#include "World.h"
#include "Bill.h"
extern CBill* bill;
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


void World::Build()
{
	CGame* g = CGame::GetInstance();
	if (right - left >= g->GetBackBufferWidth() / 2 && objects.size() > 0)
	{
		leftNode = new World(left, top, left + (right - left) / 2, bottom);
		rightNode = new World(left + (right - left) / 2, top, right, bottom);
		for (int i = 0; i < objects.size(); i++)
		{
			float x = -1, y = -1;
			objects[i]->GetPosition(x, y);
			RECT rect = objects[i]->GetRect();
			// working on it
			if (x + rect.right >= left && x <= (float)(left + (right - left) / 2))
			{
				leftNode->objects.push_back(objects[i]);
			}

			if (x + rect.right > (float)(left + (right - left) / 2) && x <= right)
			{
				rightNode->objects.push_back(objects[i]);
			}
		}
		objects.clear();
		leftNode->Build();
		rightNode->Build();
	}
}
void World::GetObjectColliderWithWiewport(vector<LPGAMEOBJECT>& result)
{
	CGame* g = CGame::GetInstance();
	float camX, camY;
	g->GetCamera()->GetCamPos(camX, camY);
	if (camX > 100)
	{
		int as = 12;
	}
	if (this == nullptr)
		return;
	if (right <= camX || left >= g->GetBackBufferWidth() + camX)
		return;

	if (leftNode == nullptr && rightNode == nullptr && !objects.empty())
	{
		for (auto it = objects.begin(); it != objects.end(); )
		{
			LPGAMEOBJECT obj = *it;
			bool existsInResult = false;
			for (auto& resultObj : result)
			{
				if (obj == resultObj)
				{
					existsInResult = true;
					break;
				}
			}

			if (!existsInResult)
			{
				result.push_back(obj);
			}

			if (obj->GetIsMovable())
				it = objects.erase(it);
			else
				++it;
		}
	}
	else
	{
		this->leftNode->GetObjectColliderWithWiewport(result);
		this->rightNode->GetObjectColliderWithWiewport(result);
	}
}

void World::AddObjectToTree(LPGAMEOBJECT object)
{
	CGame* g = CGame::GetInstance();
	float objX, objY;
	object->GetPosition(objX, objY);
	RECT rect = object->GetRect();
	if (objX + rect.right >= left && objX <= right)
	{
		if (leftNode != nullptr && rightNode != nullptr)
		{
			if (objX <= (float)(left + right) / 2 )
				leftNode->AddObjectToTree(object);
			
			if( objX + rect.right >= (float)(left + right) / 2)
				rightNode->AddObjectToTree(object);
		}
		else if (right - left > g->GetBackBufferWidth() / 2)
		{
			leftNode = new World(left, top, left + (right -left) / 2, bottom);
			rightNode = new World(left + (right - left) / 2, top, right, bottom);
			if (objX + rect.right >= left && objX <= (float)(left + (right - left) / 2))
			{
				leftNode->AddObjectToTree(object);
			}

			if (objX + rect.right >= (float)(left + (right - left) / 2) && objX <= right)
			{
				rightNode->AddObjectToTree(object);
			}
		}
		
		objects.push_back(object);
		
	}
}




