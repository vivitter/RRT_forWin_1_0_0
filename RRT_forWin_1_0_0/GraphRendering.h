#pragma once
#include "RRTParam.h"
#include <cv.h>
#include <highgui.h>
#include <iostream>

#pragma comment (lib, "cv210.lib")
#pragma comment (lib, "cxcore210.lib")
#pragma comment (lib, "cvaux210.lib")
#pragma comment (lib, "highgui210.lib")

#define WINDOW_NAME "Rapidly-Exploring Random Tree"


// Size of the Window
const int WIDTH = MAX_X;
const int HEIGHT = MAX_Y;

class CGraphRendering
{
public:
	CGraphRendering(void);
	~CGraphRendering(void);

	/***********************************************************/
	/** void InitGraphWindow( CONF_2D StartConf, CONF_2D GoalConf );
	 ***********************************************************
	 * Date		: 2012/03/29
	 * Author	: Kohei Kojima
	 * Note		: Initialize Graph Window
	 ***********************************************************/	
	void InitGraphWindow( CONF_2D StartConf, CONF_2D GoalConf );

	/***********************************************************/
	/** void RefreshGraphWindow( CONF_2D ParentConf, CONF_2D NewConf, int R, int G, int B );
	 ***********************************************************
	 * Date		: 2012/03/29
	 * Author	: Kohei Kojima
	 * Note		: Refresh Graph Window
	 ***********************************************************/	
	void DrawNewNode( CONF_2D ParentConf, CONF_2D NewConf, int R, int G, int B );

	/***********************************************************/
	/** void Point( CONF_2D Conf, int R, int G, int B );
	 ***********************************************************
	 * Date		: 2012/03/29
	 * Author	: Kohei Kojima
	 * Note		: Draw point
	 ***********************************************************/	
	void Point( CONF_2D Conf, int R, int G, int B );

	/***********************************************************/
	/** void DestroyWindow();
	 ***********************************************************
	 * Date		: 2012/03/29
	 * Author	: Kohei Kojima
	 * Note		: Destroy Window
	 ***********************************************************/	
	void DestroyWindow();

private:
	IplImage* img;
};
