#pragma
#include "cocos2d.h"

USING_NS_CC;

class DrawTool
{

public:
	/// <summary>
	/// ����Բ�Ǿ���
	/// </summary>
	/// <param name="drawNode">���ƽڵ�</param>
	/// <param name="origin">��ʼ�㣨�������Ͻǣ�</param>
	/// <param name="destination">�����㣨�������½ǣ�</param>
	/// <param name="radius">Բ�ǰ뾶</param>
	/// <param name="segments">Բ�ǵȷ������ȷ�Խ�࣬Բ��Խƽ��</param>
	/// <param name="bFill">�Ƿ����</param>
	/// <param name="color">��ɫ</param>
	static void drawRoundRect(DrawNode* drawNode, Vec2 origin, Vec2 destination, float radius, unsigned int segments, bool bFill, Color4F color);

};