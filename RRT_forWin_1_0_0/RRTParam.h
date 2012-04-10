#pragma once
#include <list>
#include <vector>

using namespace std;

// �ړ���
#define MOVEMENT 20
// �ŏI���e�덷
#define TOLERANCE 15

#define RAND_RANGE 800

// �X�^�[�g���W
#define START_X 10
#define START_Y 10

// �S�[�����W
#define GOAL_X 420
#define GOAL_Y 330

// ��ԋ�Ԃ͈͎̔w��
#define MAX_X 600
#define MAX_Y 600
#define MIN_X 0
#define MIN_Y 0

// ���b�V�����x
#define MESH 10

// �ő�T����
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

