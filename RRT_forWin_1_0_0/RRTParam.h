#pragma once
#include <list>
#include <vector>

using namespace std;

// 移動量
#define MOVEMENT 20
// 最終許容誤差
#define TOLERANCE 15

#define RAND_RANGE 800

// スタート座標
#define START_X 10
#define START_Y 10

// ゴール座標
#define GOAL_X 420
#define GOAL_Y 330

// 状態空間の範囲指定
#define MAX_X 600
#define MAX_Y 600
#define MIN_X 0
#define MIN_Y 0

// メッシュ粒度
#define MESH 10

// 最大探索回数
#define MAX_CYCLE 100000


/*==========================================*/
// Structure
/*==========================================*/
struct Node;
struct NodeConnection;

typedef struct Conf_2d{
	double x;
	double y;
} CONF_2D;

typedef struct Node{
	CONF_2D Conf;
	list<Node*> m_NodeConnection;	// Connection List
	Node* pParentNode;
}NODE;

