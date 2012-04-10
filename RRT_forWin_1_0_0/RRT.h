#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <queue>
#include <time.h>
#include "RRTParam.h"
#include "GraphRendering.h"

using namespace std;

/*==========================================*/
// Class
/*==========================================*/
class CRRT
{
public:
	CRRT(void);
	~CRRT(void);

	bool RunRRT();
	bool PathPlanning();

private:
	CGraphRendering Graph;

	NODE StartNode;
	NODE GoalNode;

	bool Map[MAX_X/MESH][MAX_Y/MESH];

	/***********************************************************/
	/** void CRRT::Init( double x, double y )
	 ***********************************************************
	 * Date		: 2012/03/27
	 * Author	: Kohei Kojima
	 * Note		: Initialize Tree's State
	 ***********************************************************/
	void Init();	// Initialize Tree's State

	/***********************************************************/
	/** CONF_2D CRRT::RandConf()
	 ***********************************************************
	 * Date		: 2012/03/27
	 * Author	: Kohei Kojima
	 * Note		: Return Random Configuration
	 ***********************************************************/
	CONF_2D RandConf();					// Return Random Configuration

	/***********************************************************/
	/** NODE* CRRT::NearestNode( CONF_2D Conf )
	 ***********************************************************
	 * Date		: 2012/03/27
	 * Author	: Kohei Kojima
	 * Note		: Search & Select Nearest Node
	 ***********************************************************/
	NODE* FindNearestNode( CONF_2D RandomConf );	// Search & Select Nearest Node

	/***********************************************************/
	/** NODE* CreateNewNode( CONF_2D Conf );
	 ***********************************************************
	 * Date		: 2012/03/27
	 * Author	: Kohei Kojima
	 * Note		: Create New Configuration
	 ***********************************************************/	
	CONF_2D CreateNewConf( CONF_2D ParentConf, CONF_2D RandomConf );	// Create New Configuration

	/***********************************************************/
	/** bool EvaluateNewConf( CONF_2D NewConf );
	 ***********************************************************
	 * Date		: 2012/03/27
	 * Author	: Kohei Kojima
	 * Note		: Evaluate New Configuration
	 ***********************************************************/	
	bool ObstacleDetection( CONF_2D NewConf );

	/***********************************************************/
	/** NODE* CreateNewNode( CONF_2D NewConf );
	 ***********************************************************
	 * Date		: 2012/03/27
	 * Author	: Kohei Kojima
	 * Note		: Create New Node
	 ***********************************************************/	
	NODE* CreateNewNode( CONF_2D NewConf );
	
	/***********************************************************/
	/** void CRRT::ShowConf( NODE* Node )
	 ***********************************************************
	 * Date		: 2012/03/27
	 * Author	: Kohei Kojima
	 * Note		: Show Configuration Value
	 ***********************************************************/
	void AddNode( NODE* ParentNode, NODE* NewNode ){
		ParentNode->m_NodeConnection.push_back( NewNode );
		NewNode->pParentNode = ParentNode;
		Graph.DrawNewNode( ParentNode->Conf, NewNode->Conf, 255, 255, 255 );
	};

	/***********************************************************/
	/** bool EvaluateState( NODE* NewNode );
	 ***********************************************************
	 * Date		: 2012/03/27
	 * Author	: Kohei Kojima
	 * Note		: Evaluate State & Return End Flg
	 ***********************************************************/
	bool EvaluateState( NODE* NewNode );

	/***********************************************************/
	/** CONF_2D GetNodeConfiguration(NODE* Node){
	 ***********************************************************
	 * Date		: 2012/03/27
	 * Author	: Kohei Kojima
	 * Note		: Get Configuration Value
	 ***********************************************************/
	CONF_2D GetNodeConf(NODE* Node){
		return Node->Conf;
	};

	/***********************************************************/
	/** double CalcDist(CONF_2D A, CONF_2D B)
	 ***********************************************************
	 * Date		: 2012/03/27
	 * Author	: Kohei Kojima
	 * Note		: Calculate Distance between 2 points
	 ***********************************************************/
	double CalcDist(CONF_2D A, CONF_2D B){
		return sqrt( pow( (A.x - B.x), 2 ) + pow( (A.y - B.y), 2 ) );
	};

	/***********************************************************/
	/** void CRRT::ShowConf( NODE* Node )
	 ***********************************************************
	 * Date		: 2012/03/27
	 * Author	: Kohei Kojima
	 * Note		: Show Configuration Value
	 ***********************************************************/
	void ShowConf( NODE* Node );		// Show Configuration State

};
