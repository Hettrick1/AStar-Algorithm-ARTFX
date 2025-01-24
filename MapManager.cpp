#include "MapManager.h"
#include "thread"
#include "chrono"

float totalCost;

MapManager::MapManager()
{
	mMap[IMAGE_SIZE][IMAGE_SIZE] = {Tile()};
	mMapImage = Image();
	mMapIndex = MAP_INDEX;
	mStartPosition = Vector2D( 38, 13 );
	mEndPosition = Vector2D( 40, 90 );
	mCanGoDiagonal = true;
}

MapManager::~MapManager()
{
}

void MapManager::Load()
{
	int index = 0;
	mMapImage = LoadImage(TextFormat("maps/Map%i.png", mMapIndex));
	Color* colors = LoadImageColors(mMapImage);
	int tileSizeX = GetScreenWidth() / IMAGE_SIZE;
	int TileSizeY = GetScreenWidth() / IMAGE_SIZE;
	for (int i = 0; i < mMapImage.width; i++) {
		for (int j = 0; j < mMapImage.width; j++) {
			mMap[i][j] = Tile(j * tileSizeX, i * TileSizeY, tileSizeX, TileSizeY);
			mMapOverlay[i][j] = Tile(j * tileSizeX, i * TileSizeY, tileSizeX, TileSizeY);
			mMapOverlay[i][j].ChangeType(TileType::Invisible);
			if (colors[index].g > 0 && colors[index].r == 0 && colors[index].b == 0) {
				mMap[i][j].ChangeType(TileType::Normal);
			}
			else if (colors[index].r > 0 && colors[index].g == 0 && colors[index].b == 0) {
				mMap[i][j].ChangeType(TileType::Difficult);
			}
			else if (colors[index].b > 0 && colors[index].r == 0 && colors[index].g == 0) {
				mMap[i][j].ChangeType(TileType::Challenging);
			}
			else if (colors[index].b == 255 && colors[index].r == 255 && colors[index].g == 255) {
				mMap[i][j].ChangeType(TileType::Void);
			}
			else if (colors[index].b == 0 && colors[index].r == 0 && colors[index].g == 0) {
				mMap[i][j].ChangeType(TileType::Obstacle);
			}
			index += 1;
		}
	}
	UnloadImageColors(colors);
	UnloadImage(mMapImage);
	mMapOverlay[static_cast<int>(mStartPosition.x)][static_cast<int>(mStartPosition.y)].ChangeType(TileType::Start);
	mMapOverlay[static_cast<int>(mEndPosition.x)][static_cast<int>(mEndPosition.y)].ChangeType(TileType::End);

}

void MapManager::Start()
{
}

void MapManager::Update()
{
	if (IsKeyDown(KEY_ENTER)) {
		CalculateAStar();
	}
}

void MapManager::Draw()
{
	for (int i = 0; i < IMAGE_SIZE; i++) {
		for (int j = 0; j < IMAGE_SIZE; j++) {
			mMap[i][j].Draw();
			mMapOverlay[i][j].Draw();
		}
	}
}

void MapManager::Unload()
{
}

void MapManager::SetMapIndex(int index)
{
	mMapIndex = index;
}

void MapManager::CalculateAStar()
{
	if (mStartPosition.x != -1 && mStartPosition.y != -1 && mEndPosition.x != -1 && mEndPosition.y != -1) {
		Node* startNode = &mMap[static_cast<int>(mStartPosition.x)][static_cast<int>(mStartPosition.y)].GetNode();
		Node* endNode = &mMap[static_cast<int>(mEndPosition.x)][static_cast<int>(mEndPosition.y)].GetNode();

		openList.clear();
		closedList.clear();

		startNode->g = 0;
		startNode->h = startNode->GetDistance(endNode);
		startNode->f = startNode->g + startNode->h;
		startNode->parent = nullptr;
		openList.push_back(startNode);
		while (!openList.empty()) {
			float tempF = Inf;
			int indexTemp = -1;
			for (int i = 0; i < openList.size(); i++) {
				if (openList[i]->f < tempF) {
					tempF = openList[i]->f;
					indexTemp = i;
				}
			}
			Node* currentNode = openList[indexTemp];
			openList.erase(openList.begin() + indexTemp);

			closedList.push_back(currentNode);

			DrawFinalPath(currentNode);
			BeginDrawing();
			Draw();
			EndDrawing();
			//std::this_thread::sleep_for(std::chrono::milliseconds(0));
			UnDrawCurrentPath(currentNode);
			if (currentNode == endNode) {
				DrawFinalPath(endNode);
				std::cout << "total rounded cost : " << endNode->g << std::endl;
				return;
			}
			for (Node* neighbor : GetNeighbors(currentNode)) {
				if (std::find(closedList.begin(), closedList.end(), neighbor) != closedList.end()) {
					continue;
				}
				int y = static_cast<int>(neighbor->position.x / (GetScreenWidth() / IMAGE_SIZE));
				int x = static_cast<int>(neighbor->position.y / (GetScreenWidth() / IMAGE_SIZE));
				mMapOverlay[x][y].ChangeType(TileType::PotentialPath);
				y = static_cast<int>(currentNode->position.x / (GetScreenWidth() / IMAGE_SIZE));
				x = static_cast<int>(currentNode->position.y / (GetScreenWidth() / IMAGE_SIZE));
				mMapOverlay[x][y].ChangeType(TileType::PotentialPathBlocked);

				int tentativeG = (currentNode->g * currentNode->weight) + (currentNode->GetDistance(neighbor) / (GetScreenWidth() / IMAGE_SIZE) * 10); // euclidian distance

				if (std::find(openList.begin(), openList.end(), neighbor) == openList.end() || tentativeG < (neighbor->g*neighbor->weight) ) {
					neighbor->g = tentativeG;
					neighbor->h = neighbor->GetDistance(endNode);
					neighbor->f = neighbor->g + neighbor->h;
					neighbor->parent = currentNode;

					if (std::find(openList.begin(), openList.end(), neighbor) == openList.end()) {
						openList.push_back(neighbor);
					}
				}
			}
		}
	}
}

Tile& MapManager::GetTile(int i, int j)
{
	return mMap[j][i];
}

std::vector<Node*> MapManager::GetNeighbors(Node* current)
{
	std::vector<Node*> neighbors;
	int y = static_cast<int>(current->position.x/ (GetScreenWidth() / IMAGE_SIZE));
	int x = static_cast<int>(current->position.y/ (GetScreenWidth() / IMAGE_SIZE));

	if (x > 0 && mMap[x - 1][y].GetTileType() != TileType::Obstacle) { // up neighbor
		neighbors.push_back(&mMap[x - 1][y].GetNode());
	}
	if (x < IMAGE_SIZE - 1 && mMap[x + 1][y].GetTileType() != TileType::Obstacle) { // down neighbor
		neighbors.push_back(&mMap[x + 1][y].GetNode());
	}
	if (y > 0 && mMap[x][y - 1].GetTileType() != TileType::Obstacle) { // left neighbor
		neighbors.push_back(&mMap[x][y - 1].GetNode()); 
	}
	if (y < IMAGE_SIZE - 1 && mMap[x][y + 1].GetTileType() != TileType::Obstacle) { // right neighbor
		neighbors.push_back(&mMap[x][y + 1].GetNode()); 
	}
	if (mCanGoDiagonal) {
		if (x > 0 && y > 0 && mMap[x - 1][y - 1].GetTileType() != TileType::Obstacle) { 
			neighbors.push_back(&mMap[x - 1][y - 1].GetNode());
		}
		if (x < IMAGE_SIZE - 1 && y < IMAGE_SIZE - 1 && mMap[x + 1][y + 1].GetTileType() != TileType::Obstacle) {
			neighbors.push_back(&mMap[x + 1][y + 1].GetNode());
		}
		if (y > 0 && x < IMAGE_SIZE && mMap[x + 1][y - 1].GetTileType() != TileType::Obstacle) {
			neighbors.push_back(&mMap[x + 1][y - 1].GetNode());
		}
		if (y < IMAGE_SIZE - 1 && x > 0 && mMap[x - 1][y + 1].GetTileType() != TileType::Obstacle) {
			neighbors.push_back(&mMap[x -1][y + 1].GetNode());
		}
	}

	return neighbors;
}

void MapManager::DrawFinalPath(Node* endNode)
{
	Node* currentNode = endNode;
	//int nodeAmount = 0;
	while (currentNode != nullptr) {
		int y = static_cast<int>(currentNode->position.x/ (GetScreenWidth() / IMAGE_SIZE));
		int x = static_cast<int>(currentNode->position.y/ (GetScreenWidth() / IMAGE_SIZE));
		mMapOverlay[x][y].ChangeType(TileType::Path);
		currentNode = currentNode->parent;
		//nodeAmount++;
	}
	//std::cout << nodeAmount << std::endl;
}

void MapManager::UnDrawCurrentPath(Node* endNode)
{
	Node* currentNode = endNode;
	while (currentNode != nullptr) {
		int y = static_cast<int>(currentNode->position.x / (GetScreenWidth() / IMAGE_SIZE));
		int x = static_cast<int>(currentNode->position.y / (GetScreenWidth() / IMAGE_SIZE));
		mMapOverlay[x][y].ChangeType(TileType::PotentialPathBlocked);
		currentNode = currentNode->parent;
	}
}

