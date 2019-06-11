#ifndef __Tetris_SCENE_H__
#define __Tetris_SCENE_H__

#include <array>
#include "cocos2d.h"
#include "Block.h"
#include <random>
#include <utility>

using std::array;
using std::pair;
using std::string;

class Tetris : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(Tetris);

	Tetris();

	array<array<int, 10>, 20> board;

	array<pair<int, int>, 4> curBlockPos;

	pair<int,int> curBlockVertex;

	void display(void);

	void moveDown(float dt);

	void moveLeft(void);

	void moveRight(void);

	void rotate(void);

	void onWin32KeyEvent( UINT message,WPARAM wParam, LPARAM lParam );
private:
	std::default_random_engine e;
	std::uniform_int_distribution<unsigned> u;
	Block curBlock;
	Block nextBlock;
	void nextTurn(void);
	cocos2d::CCSprite * setSprite(enum Block::tag t);
	void drawScoreText(string s);
	void drawText(string s, int x, int y);
	int score;
	char strBuf[32];
	bool gameOver;
};

#endif // __Tetris_SCENE_H__
