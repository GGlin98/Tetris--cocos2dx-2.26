#define DEBUG

#include "TetrisScene.h"
#include "AppMacros.h"
#include <ctime>
#include <algorithm>
#include <deque>
USING_NS_CC;

void debugPrintMatrix(std::array<std::array<int, 10>, 20> m)
{
	char buf[512] = { 0 };
	char* p = buf;
	for(int i = 0; i < 20; i++) {
		p += snprintf(p, sizeof(buf-4), "%02d  ", i);
		for(int j = 0; j < 10; j++)
			p += snprintf(p, sizeof(buf-1), "%d", m[i][j]);
		p += snprintf(p, sizeof(buf-1), "%c", '\n');
	}
	OutputDebugString(buf);
}


CCScene* Tetris::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Tetris *layer = Tetris::create();

    // add layer as a child to scene
    scene->addChild(layer);

	extern void Win32SetKeyLayer(Tetris *layer);  
    Win32SetKeyLayer(layer);  

    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool Tetris::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
 //   CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
 //                                       "CloseNormal.png",
 //                                       "CloseSelected.png",
 //                                       this,
 //                                       menu_selector(Tetris::menuCloseCallback));
 //   
	//pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
 //                               origin.y + pCloseItem->getContentSize().height/2));

 //   // create menu, it's an autorelease object
 //   CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
 //   pMenu->setPosition(CCPointZero);
 //   this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    //CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", TITLE_FONT_SIZE);
    //
    //// position the label on the center of the screen
    //pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
    //                        origin.y + visibleSize.height - pLabel->getContentSize().height));

    //// add the label as a child to this layer
    //this->addChild(pLabel, 1);

    // add "Tetris" splash screen"
    CCSprite* pSprite = CCSprite::create("bg.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);

    return true;
}


void Tetris::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}


void Tetris::display(void)
{
	CCSprite *blockSprite;
	for(int i = 0; i < 20; i++)
		for(int j = 0; j < 10; j++) {
			switch (board[i][j])
			{
			case Block::BLOCK_I1:
			case Block::BLOCK_I2:
			case Block::BLOCK_I3:
			case Block::BLOCK_I4: blockSprite = CCSprite::create("blockI.png"); break;
			case Block::BLOCK_J1:
			case Block::BLOCK_J2:
			case Block::BLOCK_J3:
			case Block::BLOCK_J4: blockSprite = CCSprite::create("blockJ.png"); break;
			case Block::BLOCK_L1:
			case Block::BLOCK_L2:
			case Block::BLOCK_L3:
			case Block::BLOCK_L4: blockSprite = CCSprite::create("blockL.png"); break;
			case Block::BLOCK_O1:
			case Block::BLOCK_O2:
			case Block::BLOCK_O3:
			case Block::BLOCK_O4: blockSprite = CCSprite::create("blockO.png"); break;
			case Block::BLOCK_S1:
			case Block::BLOCK_S2:
			case Block::BLOCK_S3:
			case Block::BLOCK_S4: blockSprite = CCSprite::create("blockS.png"); break;
			case Block::BLOCK_T1:
			case Block::BLOCK_T2:
			case Block::BLOCK_T3:
			case Block::BLOCK_T4: blockSprite = CCSprite::create("blockT.png"); break;
			case Block::BLOCK_Z1:
			case Block::BLOCK_Z2:
			case Block::BLOCK_Z3:
			case Block::BLOCK_Z4: blockSprite = CCSprite::create("blockZ.png"); break;
			default:
				continue;
			}
			blockSprite->setAnchorPoint(ccp(0,1));
			blockSprite->setPosition(ccp(107 + 42.7 + 42.7 * j, 854 - 42.7 * i));
			this->addChild(blockSprite, 10*i+j+1, 10*i+j+1);
		}
}

Tetris::Tetris() : u(1,28), e(time(0)), curBlock(Block::BLOCK_NONE), nextBlock(Block::BLOCK_NONE)
{
	array<array<int, 10>, 20> temp = { 0 };
	board = temp;

	nextTurn();

#ifdef DEBUG
	debugPrintMatrix(board);
#endif

	display();
	this->schedule(schedule_selector(Tetris::moveDown), 1.0f);
}


void Tetris::nextTurn(void)
{
	pair<int, int> temp = std::make_pair(0, 3);
	curBlockVertex = temp;

	for(int i = 0, ct = 0; i < 4; i++)
		for(int j = 3; j < 7; j++) {
			if (curBlock.matrix[i][j-3] != 0) {
				board[i][j] = curBlock.tag;
				pair<int, int>tempPair(i,j);
				curBlockPos[ct++] = tempPair;
			}
		}
}


void Tetris::moveDown(float dt)
{
	int i, j, k;

	for (auto it = curBlockPos.cbegin(); it != curBlockPos.cend(); it++) {
		i = (*it).first;
		j = (*it).second;
		if (i + 1 > 19 || // 检测到碰撞，进入下一轮
			(board[i+1][j] != 0 && std::find(curBlockPos.cbegin(), curBlockPos.cend(), std::make_pair(i+1, j)) == curBlockPos.cend())) {
			curBlock = nextBlock;
			nextBlock = Block(Block::BLOCK_NONE);
			nextTurn();
			return;
		}
	}

	curBlockVertex.first++;

	for (k = 0; k < 4; k++) {
		i = curBlockPos[k].first++;
		j = curBlockPos[k].second;
		board[i][j] = 0;
		removeChildByTag(10*i+j+1);
	}

	for (k = 0; k < 4; k++)
		board[curBlockPos[k].first][curBlockPos[k].second] = curBlock.tag;

	display();
}


void Tetris::moveLeft(void)
{
	int i, j, k;

	for (k = 0; k < 4; k++) {
		i = curBlockPos[k].first;
		j = curBlockPos[k].second - 1;
		if (j < 0 || (board[i][j] != 0 && std::find(curBlockPos.cbegin(), curBlockPos.cend(), std::make_pair(i, j)) == curBlockPos.cend() ))
			return; // 左移遇到墙或者其他方块，其他方块不是自己的方块
	}

	curBlockVertex.second--;

	for (k = 0; k < 4; k++) {
		i = curBlockPos[k].first;
		j = curBlockPos[k].second--;
		board[i][j] = 0;
		removeChildByTag(10*i+j+1);
	}

	for (k = 0; k < 4; k++)
		board[curBlockPos[k].first][curBlockPos[k].second] = curBlock.tag;

	display();
}


void Tetris::moveRight(void)
{
	int i, j, k;

	for (k = 0; k < 4; k++) {
		i = curBlockPos[k].first;
		j = curBlockPos[k].second + 1;
		if (j > 9 || (board[i][j] != 0 && std::find(curBlockPos.cbegin(), curBlockPos.cend(), std::make_pair(i, j)) == curBlockPos.cend() ))
			return;
	}

	curBlockVertex.second++;

	for (k = 0; k < 4; k++) {
		i = curBlockPos[k].first;
		j = curBlockPos[k].second++;
		board[i][j] = 0;
		removeChildByTag(10*i+j+1);
	}

	for (k = 0; k < 4; k++)
		board[curBlockPos[k].first][curBlockPos[k].second] = curBlock.tag;

	display();
}


void Tetris::rotate(void)
{
	int k, x, i, j, ct;
	x = static_cast<int>(curBlock.tag);
	curBlock = Block(static_cast<enum Block::tag>(x % 4 + 1 + ( (x - 1) / 4 ) * 4));

	for (i = 0; i < 4; i++) // 碰撞检测
		for (j = 0; j < 4; j++)
			if (curBlock.matrix[i][j] != 0) {
				int m = curBlockVertex.first, n = curBlockVertex.second;
			   if ((m + i > 19 || n + j < 0 || n + j > 9) || // 遇到边界
			   (board[m + i][n + j] != 0 && // 遇到其他方块且不是自身的方块
			   std::find(curBlockPos.cbegin(), curBlockPos.cend(), std::make_pair(m + i, n + j)) == curBlockPos.cend() ))
				return;
			}

	for (k = 0; k < 4; k++) {
		i = curBlockPos[k].first;
		j = curBlockPos[k].second;
		board[i][j] = 0;
		removeChildByTag(10*i+j+1);
	}

	for (i = 0, ct = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			if (curBlock.matrix[i][j] != 0) {
				pair<int, int> tempPair(curBlockVertex.first + i, curBlockVertex.second + j);
				curBlockPos[ct++] = tempPair;
				board[curBlockVertex.first + i][curBlockVertex.second + j] = curBlock.tag;
			}

	display();
}


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
void Tetris::onWin32KeyEvent( UINT message,WPARAM wParam, LPARAM lParam )
{
#ifdef DEBUG
	 CCLog("onWin32KeyEvent message %d wParam %d lParam %d", message, wParam, lParam);
#endif

	 if (message == 256) { // Key Down
        switch (wParam) {
        case 38: // Up
			rotate();
            break;
        case 40: // Down
			moveDown(0);
            break;
        case 37: // Left
			moveLeft();
            break;
        case 39: // Right
			moveRight();
            break;
        }
    }
}
#endif
