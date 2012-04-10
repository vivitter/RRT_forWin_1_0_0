#include "RRT.h"


CRRT::CRRT(void)
{
}

CRRT::~CRRT(void)
{
}


/***********************************************************/
/** void CRRT::Init( double x, double y )
 ***********************************************************
 * Date		: 2012/03/27
 * Author	: Kohei Kojima
 * Note		: Initialize Tree's State
 ***********************************************************/
void CRRT::Init()
{
	// Input Start & GoalState
	StartNode.Conf.x = START_X;
	StartNode.Conf.y = START_Y;
	GoalNode.Conf.x = GOAL_X;
	GoalNode.Conf.y = GOAL_Y;
	printf("-----------------------------------\n");
	printf("[Condition]\n");
	printf("   [Start] x = %.3f, y = %.3f\n", StartNode.Conf.x, StartNode.Conf.y);
	printf("   [Goal]  x = %.3f, y = %.3f\n", GoalNode.Conf.x, GoalNode.Conf.y);
	printf("-----------------------------------\n");

	// Reset Map
	for(int i=0; i<MAX_X/MESH; i++){
		for(int j=0; j<MAX_Y/MESH; j++){
			Map[i][j] = 0;
		}
	}

	for(int i = MAX_X/MESH/3 ; i<2*MAX_X/MESH/3 ; i++){
		for(int j=MAX_X/MESH/3 ; j<2*MAX_X/MESH/3 ; j++){
			Map[i][j] = 1;
		}
	}
	
	srand((unsigned)time(NULL));
	
	// Initialize Graph Window
	Graph.InitGraphWindow( StartNode.Conf, GoalNode.Conf );
}

/***********************************************************/
/** CONF_2D CRRT::RandConf()
 ***********************************************************
 * Date		: 2012/03/27
 * Author	: Kohei Kojima
 * Note		: Return Random Configuration
 ***********************************************************/
CONF_2D CRRT::RandConf()
{
	CONF_2D RandConf;
	double Min = 0;
	double Max = RAND_RANGE;

	RandConf.x = Min + (double)(rand()*(Max-Min+1.0)/(1.0+(double)RAND_MAX));
	RandConf.y = Min + (double)(rand()*(Max-Min+1.0)/(1.0+(double)RAND_MAX));

	//Graph.Point( RandConf, 51, 51, 51 );

	return RandConf;
}


/***********************************************************/
/** NODE* CRRT::NearestNode( CONF_2D Conf )
 ***********************************************************
 * Date		: 2012/03/27
 * Author	: Kohei Kojima
 * Note		: Search & Select Nearest Node
 ***********************************************************/
NODE* CRRT::FindNearestNode( CONF_2D RandomConf )
{
	NODE* pNode;
	NODE* pNearestNode = NULL;
	queue<NODE*> Que;
	list<NODE*> NextNode;

	double Dist;		// Distance
	double MinDist;		// Minimum Distance

	// 1. Push Start Point to the Que
	Que.push( &StartNode );
	MinDist = CalcDist(RandomConf, StartNode.Conf);

	while(Que.size()){
		// 2. Get Front Adress
		pNode = Que.front();
		// 3. Delete Front Adress
		Que.pop();

		// 4. Calculate Distance
		Dist = CalcDist( RandomConf, pNode->Conf );
		if(Dist <= MinDist){
			pNearestNode = pNode;
			MinDist = Dist;
		}

		// 5. Get New State and Add to the Que
		if( pNode->m_NodeConnection.size() ){
			copy( pNode->m_NodeConnection.begin(), pNode->m_NodeConnection.end(), back_inserter( NextNode ) );
			while( NextNode.size() ){
				Que.push( NextNode.front() );
				NextNode.pop_front();
			}
		}
	}
	
	// Return Nearest Node's Adress
	return pNearestNode;
}


/***********************************************************/
/** NODE* CRRT::CreateNewNode(CONF_2D Conf)
 ***********************************************************
 * Date		: 2012/03/27
 * Author	: Kohei Kojima
 * Note		: Create New Configuration
 ***********************************************************/
CONF_2D CRRT::CreateNewConf(CONF_2D ParentConf, CONF_2D RandomConf)
{
	double Delta;
	double Movement = MOVEMENT;

	CONF_2D NewConf;

	Delta = (RandomConf.y - ParentConf.y)/(RandomConf.x - ParentConf.x);
	if(RandomConf.x > ParentConf.x){
		NewConf.x = ParentConf.x + Movement / sqrt( 1 + pow(Delta,2) );
	}else{
		NewConf.x = ParentConf.x - Movement / sqrt( 1 + pow(Delta,2) );
	}
	NewConf.y = ParentConf.y + (NewConf.x - ParentConf.x ) * Delta;

	// Return New Configuration
	return NewConf;
}


/***********************************************************/
/** bool CRRT::ObstacleDetection(CONF_2D NewConf)
 ***********************************************************
 * Date		: 2012/03/27
 * Author	: Kohei Kojima
 * Note		: Check New Configuration & Detect Obstacle
 ***********************************************************/
bool CRRT::ObstacleDetection(CONF_2D NewConf)
{
	bool Flg;
	int x,y;

	if( NewConf.x >= MIN_X && NewConf.x <= MAX_X && NewConf.y >= MIN_Y && NewConf.y <= MAX_Y ){
		x = (int)NewConf.x / MESH;
		y = (int)NewConf.y / MESH;

		if( Map[x][y] == 0 ){
			Flg = 1;
			Map[x][y] = 1;
		}else{
			Flg = 0;
		}
	}else{
		Flg = 0;
	}

	return Flg;
}


/***********************************************************/
/** NODE* CRRT::CreateNewNode( CONF_2D NewConf )
 ***********************************************************
 * Date		: 2012/03/27
 * Author	: Kohei Kojima
 * Note		: Create New Node
 ***********************************************************/
NODE* CRRT::CreateNewNode( CONF_2D NewConf )
{
	NODE* pNode = new NODE;
		
	pNode->Conf.x = NewConf.x;
	pNode->Conf.y = NewConf.y;

	// Return New Node's Adress
	return pNode;
}


/***********************************************************/
/** bool CRRT::EvaluateState(NODE *NewNode)
 ***********************************************************
 * Date		: 2012/03/27
 * Author	: Kohei Kojima
 * Note		: Evaluate State
 ***********************************************************/
bool CRRT::EvaluateState(NODE *NewNode)
{
	bool EndFlg;

	if( CalcDist( NewNode->Conf, GoalNode.Conf ) < TOLERANCE ){
		EndFlg = 1;
		printf("[Success]\n");
		printf("   x = %.3f, y = %.3f\n", NewNode->Conf.x, NewNode->Conf.y);
		printf("-----------------------------------\n");

	}else{
		EndFlg = 0;
	}


	// If the position is in the are of Goal Point, it returns 1.
	return EndFlg;
}


/***********************************************************/
/** void CRRT::ShowConf( NODE* Node )
 ***********************************************************
 * Date		: 2012/03/27
 * Author	: Kohei Kojima
 * Note		: Show Configuration Value
 ***********************************************************/
void CRRT::ShowConf( NODE* Node )
{
	printf("     [%p] x = %f\n", Node, Node->Conf.x);
	printf("     [%p] y = %f\n", Node, Node->Conf.y);
}


/***********************************************************/
/** int CRRT::RunRRT()
 ***********************************************************
 * Date		: 2012/03/27
 * Author	: Kohei Kojima
 * Note		: Run RRT Algorithm (Main Function)
 ***********************************************************/
bool CRRT::RunRRT()
{
	// Random Configuration
	CONF_2D RandomConf;
	
	// Nearest Node's Information
	NODE*	pNearestNode;

	// New Configuration
	CONF_2D NewConf;

	// New Configuration
	NODE*	pNewNode;

	// Count
	int NodeCount = 0;
	int CycleCount = 0;


	// 1. Initialize Tree's State
	Init();
	
	do{
		// 2. Choose Random Point
		RandomConf = RandConf();

		// 3. Select Nearest Node
		pNearestNode = FindNearestNode( RandomConf );

		// 4. Create New Configuration
		NewConf = CreateNewConf( GetNodeConf(pNearestNode), RandomConf );

		
		if( ObstacleDetection( NewConf ) ){
			// 5. Create New Node
			pNewNode = CreateNewNode( NewConf );
			// 6. Add New Node to Tree
			AddNode( pNearestNode, pNewNode );

			//printf("[%d]\n", NodeCount);
			//ShowConf( pNewNode );
			NodeCount++;
		}

		CycleCount++;
		if( CycleCount == MAX_CYCLE)	break;

	} while( !EvaluateState(pNewNode) );
	




	if( CycleCount < MAX_CYCLE ){
		AddNode( pNewNode, &GoalNode );
	}else{
		printf("Search Failed!\n");
	}

	return 1;
}


/***********************************************************/
/** bool CRRT::PathPlanning()
 ***********************************************************
 * Date		: 2012/03/27
 * Author	: Kohei Kojima
 * Note		: Path Planning
 ***********************************************************/
bool CRRT::PathPlanning()
{
	bool Flg = 1;
	list< NODE* > List;
	NODE* pNode;

	Graph.DrawNewNode( GoalNode.pParentNode->Conf, GoalNode.Conf, 255, 0, 0 );

	List.push_back( &GoalNode );
	pNode = GoalNode.pParentNode;

	while(1){
		Graph.DrawNewNode( pNode->pParentNode->Conf, pNode->Conf, 255, 0, 0 );
		pNode = pNode->pParentNode;
		List.push_front( pNode );

		if( pNode->Conf.x == StartNode.Conf.x && pNode->Conf.y == StartNode.Conf.y ){
			break;
		}
	}

	char Key;
	gets(&Key);
	Graph.DestroyWindow();

	return Flg;

}

