#include "DrawTool.h"

void DrawTool::drawRoundRect(DrawNode* drawNode, Vec2 origin, Vec2 destination, float radius, unsigned int segments, bool bFill, Color4F color)
{

    const float coef = 0.5f * (float)M_PI / segments;
    Vec2* vertices = new Vec2[segments + 1];
    Vec2* thisVertices = vertices;
    for (unsigned int i = 0; i <= segments; ++i, ++thisVertices)
    {
        float rads = (segments - i) * coef;
        thisVertices->x = (int)(radius * sinf(rads));
        thisVertices->y = (int)(radius * cosf(rads));
    }
    //
    Vec2 tagCenter;
    float minX = MIN(origin.x, destination.x);
    float maxX = MAX(origin.x, destination.x);
    float minY = MIN(origin.y, destination.y);
    float maxY = MAX(origin.y, destination.y);

    unsigned int dwPolygonPtMax = (segments + 1) * 4;
    Vec2* pPolygonPtArr = new Vec2[dwPolygonPtMax];
    Vec2* thisPolygonPt = pPolygonPtArr;
    int aa = 0;
    //вСио╫г
    tagCenter.x = minX + radius;
    tagCenter.y = maxY - radius;
    thisVertices = vertices;
    for (unsigned int i = 0; i <= segments; ++i, ++thisPolygonPt, ++thisVertices)
    {
        thisPolygonPt->x = tagCenter.x - thisVertices->x;
        thisPolygonPt->y = tagCenter.y + thisVertices->y;
        ++aa;
    }
    //срио╫г
    tagCenter.x = maxX - radius;
    tagCenter.y = maxY - radius;
    thisVertices = vertices + segments;
    for (unsigned int i = 0; i <= segments; ++i, ++thisPolygonPt, --thisVertices)
    {
        thisPolygonPt->x = tagCenter.x + thisVertices->x;
        thisPolygonPt->y = tagCenter.y + thisVertices->y;
        ++aa;
    }
    //сроб╫г
    tagCenter.x = maxX - radius;
    tagCenter.y = minY + radius;
    thisVertices = vertices;
    for (unsigned int i = 0; i <= segments; ++i, ++thisPolygonPt, ++thisVertices)
    {
        thisPolygonPt->x = tagCenter.x + thisVertices->x;
        thisPolygonPt->y = tagCenter.y - thisVertices->y;
        ++aa;
    }
    //вСоб╫г
    tagCenter.x = minX + radius;
    tagCenter.y = minY + radius;
    thisVertices = vertices + segments;
    for (unsigned int i = 0; i <= segments; ++i, ++thisPolygonPt, --thisVertices)
    {
        thisPolygonPt->x = tagCenter.x - thisVertices->x;
        thisPolygonPt->y = tagCenter.y - thisVertices->y;
        ++aa;
    }

    if (bFill)
    {
        drawNode->drawSolidPoly(pPolygonPtArr, dwPolygonPtMax, color);
    }
    else
    {
        drawNode->drawPoly(pPolygonPtArr, dwPolygonPtMax, true, color);
    }

    CC_SAFE_DELETE_ARRAY(vertices);
    CC_SAFE_DELETE_ARRAY(pPolygonPtArr);
}
