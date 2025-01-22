#pragma once
#include "raylib.h"
#include "Tile.h"
#include "Vector2D.h"
#include <vector>

#define IMAGE_SIZE 100
#define Inf std::numeric_limits<int>::max()

class MapManager
{
private:
	Tile mMap[IMAGE_SIZE][IMAGE_SIZE];
	Image mMapImage;
	int mMapIndex;
	Vector2D mStartPosition;
	Vector2D mEndPosition;
	std::vector<Node*> openList;
	std::vector<Node*> closedList;
	bool mCanGoDiagonal;

public:
	MapManager();
	~MapManager();
	void Load();
	void Start();
	void Update();
	void Draw();
	void Unload();
	void SetMapIndex(int index);
	void CalculateAStar();
	Tile& GetTile(int i, int j);
	std::vector<Node*> GetNeighbors(Node* current);
	void DrawFinalPath(Node* endNode);
	void UnDrawCurrentPath(Node* endNode);
};



