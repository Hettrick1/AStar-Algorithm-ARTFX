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
		mNode.weight = 1;
	}
	else if (mType == TileType::Challenging) {
		mColor = ORANGE;
		mNode.weight = 1.2;
	}
	else if (mType == TileType::Difficult) {
		mColor = RED;
		mNode.weight = 1.5;
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
		mColor = Color{51, 245, 255, 128};
	}
	else if (mType == TileType::PotentialPathBlocked) {
		mColor = Color{ 51, 170, 255, 128 };
	}
	else if (mType == TileType::Invisible) {
		mColor = BLANK;
	}
}

TileType Tile::GetTileType()
{
	return mType;
}

