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
	mNode = Node({ static_cast<float>(mPosX), static_cast<float>(mPosY) });
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
	else if (mType == TileType::Start) {
		mColor = BLUE;
	}
	else if (mType == TileType::End) {
		mColor = DARKBLUE;
	}
	else if (mType == TileType::Path) {
		mColor = PINK;
	}
	else if (mType == TileType::PotentialPath) {
		mColor = Color{128, 0, 128, 128};
	}
	else if (mType == TileType::PotentialPathBlocked) {
		mColor = BROWN;
	}
}

TileType Tile::GetTileType()
{
	return mType;
}

