#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(int posX, int posY, int sizeX, int sizeY)
{
	mPosX = posX;
	mPosY = posY;
	mSizeX = sizeX;
	mSizeY = sizeY;
	mType = TileType::Normal;
	mColor = GREEN;
}

Tile::~Tile()
{
}

void Tile::Draw()
{
	DrawRectangle(mPosX, mPosY, mSizeX, mSizeY, mColor);
}

void Tile::ChangeType(TileType type)
{
	mType = type;
	if (mType == TileType::Normal) {
		mColor = GREEN;
	}
	else if (mType == TileType::Challenging) {
		mColor = ORANGE;
	}
	else if (mType == TileType::Difficult) {
		mColor = RED;
	}
	else if (mType == TileType::Obstacle) {
		mColor = BLACK;
	}
	else if (mType == TileType::Void) {
		mColor = GRAY;
	}
}

TileType Tile::GetTileType()
{
	return mType;
}

