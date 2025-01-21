#pragma once
#include "TileType.h"
#include "raylib.h"

#include <iostream>

class Tile
{
private:
	int mPosX;
	int mPosY;
	int mSizeX;
	int mSizeY;
	TileType mType;
	Color mColor;
public:
	Tile();
	Tile(int posX, int posY, int sizeX, int sizeY);
	~Tile();
	void Draw();
	void ChangeType(TileType type);
	TileType GetTileType();
	int GetPosX() const { return mPosX; }
	int GetPosY() const { return mPosY; }
	int GetSizeX() const { return mSizeX; }
	int GetSizeY() const { return mSizeY; }
};



