#pragma
#include "cocos2d.h"

USING_NS_CC;

class DrawTool
{

public:
	/// <summary>
	/// 绘制圆角矩形
	/// </summary>
	/// <param name="drawNode">绘制节点</param>
	/// <param name="origin">开始点（矩形左上角）</param>
	/// <param name="destination">结束点（矩形右下角）</param>
	/// <param name="radius">圆角半径</param>
	/// <param name="segments">圆角等份数，等份越多，圆角越平滑</param>
	/// <param name="bFill">是否填充</param>
	/// <param name="color">颜色</param>
	static void drawRoundRect(DrawNode* drawNode, Vec2 origin, Vec2 destination, float radius, unsigned int segments, bool bFill, Color4F color);

};