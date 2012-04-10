#include "GraphRendering.h"

CGraphRendering::CGraphRendering(void)
{
}

CGraphRendering::~CGraphRendering(void)
{
}


/***********************************************************/
/** void InitGraphWindow( CONF_2D StartConf, CONF_2D GoalConf );
 ***********************************************************
 * Date		: 2012/03/29
 * Author	: Kohei Kojima
 * Note		: Initialize Graph Window
 ***********************************************************/	
void CGraphRendering::InitGraphWindow(CONF_2D StartConf, CONF_2D GoalConf)
{
    //描画用IplImageバッファの確保
    img = cvCreateImage(cvSize(WIDTH, HEIGHT), IPL_DEPTH_8U, 3);
    
    //画像表示ウィンドウの準備
    cvNamedWindow( WINDOW_NAME, CV_WINDOW_AUTOSIZE );

    //画像表示ウィンドウの出現位置指定
    cvMoveWindow( WINDOW_NAME, 50, 50 );

	cvSetZero(img);

	cvCircle(img, cvPoint((int)StartConf.x, (int)StartConf.y), 3, cvScalar(0, 0, 255), 2, 8, 0);
	cvCircle(img, cvPoint((int)GoalConf.x, (int)GoalConf.y), TOLERANCE, cvScalar(0, 0, 255), 2, 8, 0);

	cvLine(img, cvPoint(MAX_X/3, MAX_Y/3), cvPoint(2*MAX_X/3, MAX_Y/3), cvScalar(0, 255, 0), 3, 8, 0);
	cvLine(img, cvPoint(MAX_X/3, MAX_Y/3), cvPoint(MAX_X/3, 2*MAX_Y/3), cvScalar(0, 255, 0), 3, 8, 0);
	cvLine(img, cvPoint(MAX_X/3, 2*MAX_Y/3), cvPoint(2*MAX_X/3, 2*MAX_Y/3), cvScalar(0, 255, 0), 3, 8, 0);
	cvLine(img, cvPoint(2*MAX_X/3, MAX_Y/3), cvPoint(2*MAX_X/3, 2*MAX_Y/3), cvScalar(0, 255, 0), 3, 8, 0);

	cvShowImage( WINDOW_NAME, img );
	cvWaitKey(10);
}


/***********************************************************/
/** void RefreshGraphWindow( CONF_2D ParentConf, CONF_2D NewConf, int R, int G, int B );
 ***********************************************************
 * Date		: 2012/03/29
 * Author	: Kohei Kojima
 * Note		: Refresh Graph Window
 ***********************************************************/	
void CGraphRendering::DrawNewNode(CONF_2D ParentConf, CONF_2D NewConf, int R, int G, int B)
{
	cvCircle(img, cvPoint((int)NewConf.x, (int)NewConf.y), 1, cvScalar(B, G, R), 2, 8, 0);
	cvLine(img, cvPoint((int)ParentConf.x, (int)ParentConf.y), cvPoint((int)NewConf.x, (int)NewConf.y), cvScalar(B, G, R), 1, 8, 0);
	cvShowImage( WINDOW_NAME, img );
	cvWaitKey(10);
}


/***********************************************************/
/** void Point( CONF_2D Conf, int R, int G, int B );
 ***********************************************************
 * Date		: 2012/03/29
 * Author	: Kohei Kojima
 * Note		: Draw point
 ***********************************************************/	
void CGraphRendering::Point( CONF_2D Conf, int R, int G, int B )
{
	cvCircle(img, cvPoint((int)Conf.x, (int)Conf.y), 1, cvScalar(B, G, R), 2, 8, 0);
	cvShowImage( WINDOW_NAME, img );
	cvWaitKey(10);
}


/***********************************************************/
/** void DestroyWindow();
 ***********************************************************
 * Date		: 2012/03/29
 * Author	: Kohei Kojima
 * Note		: Destroy Window
 ***********************************************************/	
void CGraphRendering::DestroyWindow()
{
	cvDestroyWindow( WINDOW_NAME );
}