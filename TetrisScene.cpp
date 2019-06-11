#define DEBUG

#include "TetrisScene.h"
#include "AppMacros.h"
#include <ctime>
#include <algorithm>
#include <set>
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


inline CCSprite * Tetris::setSprite(enum Block::tag t)
{
	CCSprite* blockSprite;
	switch (t) {
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
			return NULL;
	}

	return blockSprite;
}


void Tetris::display(void)
{
	CCSprite *blockSprite;
	int i, j;

	snprintf(strBuf, 10, "%d", score);
	drawScoreText(std::string(strBuf));

	for(i = 0; i < 20; i++) {
		for(j = 0; j < 10; j++) {
			if ((blockSprite = setSprite(static_cast<enum Block::tag>(board[i][j]))) == nullptr)
				continue;
			blockSprite->setAnchorPoint(ccp(0,1));
			blockSprite->setPosition(ccp(107 + 42.7 + 42.7 * j, 854 - 42.7 * i));
			auto tempPair = std::make_pair(i, j);
			if (this->getChildByTag(10*i+j+1) == NULL)
				this->addChild(blockSprite, 10*i+j+1, 10*i+j+1);
//#ifdef DEBUG
//			CCLog("addChild (%d, %d)", i, j);
//#endif
		}
	}

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (nextBlock.matrix[i][j] != 0 && this->getChildByTag(666 + 10 * i + j + 1) == NULL) {
				if ((blockSprite = setSprite(static_cast<enum Block::tag>(nextBlock.tag))) == nullptr)
					exit(EXIT_FAILURE);
				blockSprite->setAnchorPoint(ccp(0,1));
				blockSprite->setScale(static_cast<float>(0.79626));
				blockSprite->setPosition(ccp(nextBlock.posOfNextBlock.first + 34 * j, nextBlock.posOfNextBlock.second - 34 * i));
				this->addChild(blockSprite, 666 + 10 * i + j + 1, 666 + 10 * i + j + 1);
			}
		}
	}
}

Tetris::Tetris() : u(1,28), e(time(0)), curBlock(Block::BLOCK_NONE), nextBlock(Block::BLOCK_NONE), gameOver(false)
{
	array<array<int, 10>, 20> temp = { 0 };
	board = temp;
	score = -10;

	//// test
	//for (int i = 0; i < 9; i++) {
	//	board[18][i] = 1;
	//	board[19][i] = 1;
	//}
	//for (int j = 17; j > 13; j--)
	//	board[j][5] = 10;

	nextTurn();

#ifdef DEBUG
	debugPrintMatrix(board);
#endif

	display();
	this->schedule(schedule_selector(Tetris::moveDown), 1.0f);
}


void Tetris::nextTurn(void)
{
	int i, j, ct;
	CCNode *tempNode;
	curBlockVertex = std::make_pair(0, 3);
	score += 10;

	for(i = 0, ct = 0; i < 4; i++)
		for(j = 3; j < 7; j++) {
			if (curBlock.matrix[i][j-3] != 0) {
				board[i][j] = curBlock.tag;
				pair<int, int>tempPair(i,j);
				curBlockPos[ct++] = tempPair;
				if ((tempNode = getChildByTag(666 + i * 10 + (j - 3) + 1)) != nullptr)
					removeChild(tempNode);
			}
		}
}


void Tetris::drawScoreText(std::string s)
{
	int i, offset;
	CCSprite *textSprite;
	CCNode *tempNode;

	for(i = 10; i >= 0; i--) {
		if ((tempNode = getChildByTag(1000 + i)) != nullptr)
			removeChild(tempNode);
	}
	
	for(i = s.size()-1; i >= 0; i--) {
		switch (s[i]) {
		case '0': textSprite = CCSprite::create("text0.png"); break;
		case '1': textSprite = CCSprite::create("text1.png"); break;
		case '2': textSprite = CCSprite::create("text2.png"); break;
		case '3': textSprite = CCSprite::create("text3.png"); break;
		case '4': textSprite = CCSprite::create("text4.png"); break;
		case '5': textSprite = CCSprite::create("text5.png"); break;
		case '6': textSprite = CCSprite::create("text6.png"); break;
		case '7': textSprite = CCSprite::create("text7.png"); break;
		case '8': textSprite = CCSprite::create("text8.png"); break;
		case '9': textSprite = CCSprite::create("text9.png"); break;
		default: OutputDebugString("Error: no matched case in Tetris::drawScoreText\n");
			exit(EXIT_FAILURE);
		}
		textSprite->setAnchorPoint(ccp(0,1));
		/*textSprite->setScale(static_cast<float>(0.813953));*/
		offset = s.size() - i - 1;
		textSprite->setPosition(ccp(858 - 44 * offset, 641));
		this->addChild(textSprite, 1000 + i, 1000 + i);
	}
}


void Tetris::drawText(string s, int x, int y)
{
	unsigned i;
	CCSprite *textSprite;

	for (i = 0; i < s.size(); i++) {
		switch(s[i]) {
		case 'A': textSprite = CCSprite::create("textA.png"); break;
		case 'E': textSprite = CCSprite::create("textE.png"); break;
		case 'G': textSprite = CCSprite::create("textG.png"); break;
		case 'M': textSprite = CCSprite::create("textM.png"); break;
		case 'O': textSprite = CCSprite::create("textO.png"); break;
		case 'R': textSprite = CCSprite::create("textR.png"); break;
		case 'V': textSprite = CCSprite::create("textV.png"); break;
		case ' ': continue;
		default: OutputDebugString("Error: no matched case in Tetris::drawText\n");
			exit(EXIT_FAILURE);
		}
		textSprite->setAnchorPoint(ccp(0,1));
		/*textSprite->setScale(static_cast<float>(0.813953));*/
		textSprite->setPosition(ccp(x + 44 * i, y));
		this->addChild(textSprite, 1500 + i, 1500 + i);
	}
}


void Tetris::moveDown(float dt)
{
	int i, j, k, ct, m, n, numRemovedLine = 0;
	CCNode *tempNode;
	std::set<int> lines;

	for (auto it = curBlockPos.cbegin(); it != curBlockPos.cend(); it++) {
		i = (*it).first;
		j = (*it).second;
		if (i + 1 > 19 || // 检测到碰撞，进入下一轮
			(board[i+1][j] != 0 && std::find(curBlockPos.cbegin(), curBlockPos.cend(), std::make_pair(i+1, j)) == curBlockPos.cend())) {
			if (i <= 2) {
				gameOver = true;
				for (m = 0; m < 20; m++)
					for (n = 0; n < 10; n++) {
						board[m][n] = 0;
						if ((tempNode = getChildByTag(10*m+n+1)) != nullptr)
							removeChild(tempNode);
					}
				for (m = 0; m < 4; m++)
					for (n = 0; n < 4; n++)
						if ((tempNode = getChildByTag(666+10*m+n+1)) != nullptr)
							removeChild(tempNode);
				this->unschedule(schedule_selector(Tetris::moveDown));
				drawText(string("GAME OVER"), 167, 406);
				return;
			}

			for (k = 0; k < 4; k++)
				lines.insert(curBlockPos[k].first);
			for (auto it = lines.begin(); it != lines.end(); it++) {
				for (i = *it, ct = 0, j = 0; j < 10; j++) { // 检测当前行是否需要消行
					if (board[i][j] == 0)
						break;
					else ct++;
				}
				if (ct == 10) { // 需要消行
					numRemovedLine++;
					for (m = *it; m > 0; m--)
						for (k = 0; k < 10; k++)
							if (board[m][k] != 0) {
#ifdef DEBUG
								CCLog("remove (%d, %d)", m, k);
#endif
								removeChildByTag(10*m+k+1);
							}
					for (m = *it; m > 0; m--)
						for (k = 0; k < 10; k++)
							board[m][k] = board[m-1][k];

					switch (numRemovedLine) { // 更新分数
					case 0 : break;
					case 1 : score += 100; break;
					case 2 : score += 200; break;
					case 3 : score += 400; break;
					case 4 : score += 800; break;
					default: exit(EXIT_FAILURE);
					}
				}
			}

			curBlock = nextBlock;
			nextBlock = Block(Block::BLOCK_NONE);
			nextTurn();
			display();
			return;
		}
	}

	curBlockVertex.first++;

	for (k = 0; k < 4; k++) { // 消除当前方块
		i = curBlockPos[k].first++;
		j = curBlockPos[k].second;
		board[i][j] = 0;
		removeChildByTag(10*i+j+1);
	}
	
	for (k = 0; k < 4; k++) // 放置方块在下一格
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
	if (gameOver) {
		if (message == 256 && wParam == 13) {// Press "Enter"
			gameOver = false;
			for (int i = 0; i < 9; i++)
				removeChildByTag(1500 + i);
			score = -10;
			curBlock = Block(Block::BLOCK_NONE);
			nextBlock = Block(Block::BLOCK_NONE);
			nextTurn();
			this->schedule(schedule_selector(Tetris::moveDown), 1.0f);
		}
		else return;
	}

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
