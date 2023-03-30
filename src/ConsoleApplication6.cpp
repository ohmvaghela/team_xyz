#include <iostream>
#include <string>
// #include <Windows.h>
// #include <conio.h>
#include<chrono>
#include<vector>
using namespace std;
using namespace std::chrono;
#include "./olcConsoleGameEngine.h"

class OneLoneCoder_Platformer : public olcConsoleGameEngine
{
public:
	OneLoneCoder_Platformer()
	{
		m_sAppName = L"Tile Based Platform Game";
	}

private:
	// Level storage

	int nLevelWidth;
	int nLevelHeight;
	wstring sLevel;
	float fPlayerPosX = 12.0f;
	float fPlayerPosY = 87.0f;
	float fPlayerVelX = 0.0f;
	float fPlayerVelY = 0.0f;
	bool bPlayerOnGround = false;
	int nDirModX = 0;
	int nDirModY = 0;
protected:
	virtual bool OnUserCreate()
	{
		nLevelWidth = 32;
		nLevelHeight = 90;

		sLevel += L"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB";
		sLevel += L"B..............................B";
		sLevel += L"BBBBBB..................BBBBB..B";
		sLevel += L"B..............BBBBBB..........B";
		sLevel += L"B..............................B";
		sLevel += L"B......######..................B";
		sLevel += L"B..............................B";
		sLevel += L"BBBBB.........#######..........B";
		sLevel += L"B..............................B";
		sLevel += L"B..............................B";
		sLevel += L"B.......GGGGGGGGGG.............B";
		sLevel += L"B..............................B";
		sLevel += L"BBBBB................GGGG......B";
		sLevel += L"B..............................B";
		sLevel += L"B.......................BBBBB..B";
		sLevel += L"B....####......................B";
		sLevel += L"B...............GGGGGG.........B";
		sLevel += L"B..............................B";
		sLevel += L"B..............................B";
		sLevel += L"B..BBBBBBBBBB.............BBBBBB";
		sLevel += L"B..............................B";
		sLevel += L"B..............######..........B";
		sLevel += L"B..............................B";
		sLevel += L"B.......................GGGGGGGB";
		sLevel += L"B..............................B";
		sLevel += L"B..............................B";
		sLevel += L"B.................BBBB.........B";
		sLevel += L"B..............................B";
		sLevel += L"B.......#######................B";
		sLevel += L"B..............................B";
		
		sLevel += L"B..............................B";
		sLevel += L"B..............................B";
		sLevel += L"B..............GGGGGGG.........B";
		sLevel += L"B..............................B";
		sLevel += L"B..............................B";
		sLevel += L"B..BBBBBBBBBB.............BBBBBB";
		sLevel += L"B..............................B";
		sLevel += L"B..............#######.........B";
		sLevel += L"B..............................B";
		sLevel += L"BBBBBBB........................B";
		sLevel += L"B.....................#######..B";
		sLevel += L"B.........BBBBBB...............B";
		sLevel += L"B..............................B";
		sLevel += L"B..............................B";
		sLevel += L"BBBB..............GGGG.........B";
		sLevel += L"B..............................B";
		sLevel += L"B...BBBBBBBBB...........#######B";
		sLevel += L"B..............................B";
		sLevel += L"B...............GGGGGG.........B";
		sLevel += L"B..............................B";
		sLevel += L"B..............................B";
		sLevel += L"B..BBBBBBBBBBBB...........BBBBBB";
		sLevel += L"B..............................B";
		sLevel += L"B..............#######.........B";
		sLevel += L"B..............................B";
		sLevel += L"BBBBBBB........................B";
		sLevel += L"B.....................#######..B";
		sLevel += L"B......BBBBB...................B";
		sLevel += L"B..............................B";
		sLevel += L"B.............GGGGGGG..........B";


		sLevel += L"B..............................B";
		sLevel += L"B..............................B";
		sLevel += L"B.....BBBBBBB..................B";
		sLevel += L"B..............................B";
		sLevel += L"B.........................BBBBBB";
		sLevel += L"B###...........................B";
		sLevel += L"B..............#######.........B";
		sLevel += L"B..............................B";
		sLevel += L"BBBBBBB........................B";
		sLevel += L"B.........####..............###B";
		sLevel += L"B..............................B";
		sLevel += L"B..............BBBBBBBB........B";
		sLevel += L"B..............................B";
		sLevel += L"B.......BBBB...................B";
		sLevel += L"B........................GGGGGGB";
		sLevel += L"B...............#####..........B";
		sLevel += L"B..............................B";
		sLevel += L"B......................########B";
		sLevel += L"B....BBBBBBBBBBBB..............B";
		sLevel += L"B..............................B";
		sLevel += L"B..............................B";
		sLevel += L"B..........GGGGGGGGGG..........B";
		sLevel += L"B....................GGG.......B";
		sLevel += L"B..............................B";
		sLevel += L"BBBBBBB........................B";
		sLevel += L"B......GGG..............#######B";
		sLevel += L"B...............GGGGGGG........B";
		sLevel += L"B..............................B";
		sLevel += L"BGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGB";
		sLevel += L"B..............................B";
		auto start = high_resolution_clock::now();

		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime)
	{
		// Utility Lambdas
		auto GetTile = [&](int x, int y)
		{
			if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
				return sLevel[y * nLevelWidth + x];
			else
				return L' ';
		};

		auto SetTile = [&](int x, int y, wchar_t c)
		{
			if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
				sLevel[y * nLevelWidth + x] = c;
		};

		if (IsFocused())
		{
			if (GetKey(VK_UP).bPressed && bPlayerOnGround==true)
			{
				fPlayerVelY = -60.0f;
			}

			if (GetKey(VK_DOWN).bHeld)
			{
				fPlayerVelY = 6.0f;
			}

			if (GetKey(VK_LEFT).bHeld)
			{
				fPlayerVelX += ( -200.0f) * fElapsedTime;
				nDirModY = 1;
			}

			if (GetKey(VK_RIGHT).bHeld)
			{
				fPlayerVelX += ( 200.0f) * fElapsedTime;
				nDirModY = 0;
			}

			if (GetKey(VK_SPACE).bPressed)
			{
				if (fPlayerVelY == 0)
				{
					fPlayerVelY = -12.0f;
					nDirModX = 1;
				}
			}
		}

		// Gravity
		fPlayerVelY += 10.0f * pow(fElapsedTime,0.5);

		// Drag
		if (bPlayerOnGround)
		{
			fPlayerVelX += -20.0f * fPlayerVelX * fElapsedTime;
			if (fabs(fPlayerVelX) < 0.01f)
				fPlayerVelX = 0.0f;
		}

		// Clamp velocities
		if (fPlayerVelX > 500.0f)
			fPlayerVelX = 500.0f;

		if (fPlayerVelX < -500.0f)
			fPlayerVelX = -500.0f;

		if (fPlayerVelY > 100.0f)
			fPlayerVelY = 100.0f;

		if (fPlayerVelY < -100.0f)
			fPlayerVelY = -100.0f;

		// Calculate potential new position
		float fNewPlayerPosX = fPlayerPosX + (fPlayerVelX * fElapsedTime);
		float fNewPlayerPosY = fPlayerPosY + (fPlayerVelY * fElapsedTime);

		
		// Check for Collision
		if (fPlayerVelX < 0) // Moving Left
		{
			if (GetTile(fNewPlayerPosX + 0.0f, fPlayerPosY + 0.0f) != L'.' || GetTile(fNewPlayerPosX + 0.0f, fPlayerPosY + 0.9f) != L'.')
			{
				fNewPlayerPosX = (int)fNewPlayerPosX +1;
				fPlayerVelX = 0;
			}
		}
		else // Moving Right
		{
			if (GetTile(fNewPlayerPosX + 1.0f, fPlayerPosY + 0.0f) != L'.' || GetTile(fNewPlayerPosX + 1.0f, fPlayerPosY + 0.9f) != L'.')
			{
				fNewPlayerPosX = (int)fNewPlayerPosX;
				fPlayerVelX = 0;

			}
		}

		bPlayerOnGround = false;
		if (fPlayerVelY < 0) // Moving Up
		{
			if (GetTile(fNewPlayerPosX + 0.0f, fNewPlayerPosY) != L'.' || GetTile(fNewPlayerPosX + 0.9f, fNewPlayerPosY) != L'.')
			{
				fNewPlayerPosY = (int)fNewPlayerPosY +1;
				fPlayerVelY = 0;
			}
		}
		else // Moving Down
		{
			if (GetTile(fNewPlayerPosX + 0.0f, fNewPlayerPosY + 1.0f) != L'.' || GetTile(fNewPlayerPosX + 0.9f, fNewPlayerPosY + 1.0f) != L'.')
			{
				fNewPlayerPosY = (int)fNewPlayerPosY;
				fPlayerVelY = 0;
				bPlayerOnGround = true; 
				nDirModX = 0;
			}
		}

		// Apply new position
		fPlayerPosX = fNewPlayerPosX;
		fPlayerPosY = fNewPlayerPosY;
		// Draw Level
		
		
		int nTileWidth = 1;
		int nTileHeight = 1;
		int nVisibleTilesX = 32;
		int nVisibleTilesY = 32;
		//time calculation 
		/*if (fPlayerPosY == 1)
		{
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<milliseconds>(stop - start);
			cout << duration.count() << endl;
		}*/
		// Draw visible tile map
		if (fPlayerPosY < 30)
		{
			for (int x = 0; x < nVisibleTilesX + 1; x++)
			{
				for (int y = 0; y < 30; y++)
				{
					wchar_t sTileID = GetTile(x, y);
					switch (sTileID)
					{
					case L'.': // Sky
						Fill(x * nTileWidth, (y)*nTileHeight, (x + 1) * nTileWidth, ((y)+1) * nTileHeight, PIXEL_SOLID, FG_CYAN);
						break;
					case L'#': // Solid Block
						Fill(x * nTileWidth, (y)*nTileHeight, (x + 1) * nTileWidth, ((y)+1) * nTileHeight, PIXEL_SOLID, FG_WHITE);
						break;
					case L'G': // Ground Block
						Fill(x * nTileWidth, (y)*nTileHeight, (x + 1) * nTileWidth, ((y)+1) * nTileHeight, PIXEL_SOLID, FG_WHITE);
						break;
					case L'B': // Brick Block
						Fill(x * nTileWidth, (y)*nTileHeight, (x + 1) * nTileWidth, ((y)+1) * nTileHeight, PIXEL_SOLID, FG_RED);
						break;
					default:
						Fill(x * nTileWidth, (y)*nTileHeight, (x + 1) * nTileWidth, ((y)+1) * nTileHeight, PIXEL_SOLID, FG_BLACK);
						break;
					}
				}
			}
			Fill((fPlayerPosX), (fPlayerPosY), (fPlayerPosX + 1.0f), (fPlayerPosY +1.0f), PIXEL_SOLID, FG_GREEN);
			return true;
		}
		else if(fPlayerPosY < 60 && fPlayerPosY > 30)
		{
			for (int x = 0; x < nVisibleTilesX + 1; x++)
			{
				for (int y = 0; y < 30; y++)
				{
					wchar_t sTileID = GetTile(x, y+30);
					switch (sTileID)
					{
					case L'.': // Sky
						Fill(x * nTileWidth, (y)*nTileHeight, (x + 1) * nTileWidth, ((y)+1) * nTileHeight, PIXEL_SOLID, FG_CYAN);
						break;
					case L'#': // Solid Block
						Fill(x * nTileWidth, (y)*nTileHeight, (x + 1) * nTileWidth, ((y)+1) * nTileHeight, PIXEL_SOLID, FG_WHITE);
						
						break;
					case L'G': // Ground Block
						Fill(x * nTileWidth, (y)*nTileHeight, (x + 1) * nTileWidth, ((y)+1) * nTileHeight, PIXEL_SOLID, FG_WHITE);
						break;
					case L'B': // Brick Block
						Fill(x * nTileWidth, (y)*nTileHeight, (x + 1) * nTileWidth, ((y)+1) * nTileHeight, PIXEL_SOLID, FG_RED);
						break;
					default:
						Fill(x * nTileWidth, (y)*nTileHeight, (x + 1) * nTileWidth, ((y)+1) * nTileHeight, PIXEL_SOLID, FG_BLACK);
						break;
					}
				}
			}
			Fill((fPlayerPosX), (fPlayerPosY-30.0f), (fPlayerPosX + 1.0f), (fPlayerPosY -29.0f), PIXEL_SOLID, FG_GREEN);
			return true;
		}

		else if (fPlayerPosY < 90 && fPlayerPosY > 60)
		{
			for (int x = 0; x < nVisibleTilesX + 1; x++)
			{
				for (int y = 0; y < 30; y++)
				{
					wchar_t sTileID = GetTile(x, y + 60);
					switch (sTileID)
					{
					case L'.': // Sky
						Fill(x * nTileWidth, (y)*nTileHeight, (x + 1) * nTileWidth, ((y)+1) * nTileHeight, PIXEL_SOLID, FG_CYAN);
						break;
					case L'#': // Solid Block
						Fill(x * nTileWidth, (y)*nTileHeight, (x + 1) * nTileWidth, ((y)+1) * nTileHeight, PIXEL_SOLID, FG_WHITE);
						break;
					case L'G': // Ground Block
						Fill(x * nTileWidth, (y)*nTileHeight, (x + 1) * nTileWidth, ((y)+1) * nTileHeight, PIXEL_SOLID, FG_WHITE);
						break;
					case L'B': // Brick Block
						Fill(x * nTileWidth, (y)*nTileHeight, (x + 1) * nTileWidth, ((y)+1) * nTileHeight, PIXEL_SOLID, FG_RED);
						break;
					default:
						Fill(x * nTileWidth, (y)*nTileHeight, (x + 1) * nTileWidth, ((y)+1) * nTileHeight, PIXEL_SOLID, FG_BLACK);
						break;
					}
				}
			}
			Fill((fPlayerPosX), (fPlayerPosY - 60.0f), (fPlayerPosX + 1.0f), (fPlayerPosY - 59.0f), PIXEL_SOLID, FG_GREEN);
			return true;
		}
		
	}
};

int main()
{
	OneLoneCoder_Platformer game;
	if (game.ConstructConsole(32,30,1,1))
		game.Start();
	return 0;
}

