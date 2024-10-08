#include "draw.h"
 

DebugDraw::DebugDraw(BLContext &context):meter(100.f),ctx(context){
	
 //ctx = context;
	

}




void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color){
	
	b2Vec2 p1 = vertices[vertexCount-1];
	for(int i = 0;i<vertexCount;i++){
		
		b2Vec2 p2 = vertices[i];
		ctx.strokeLine(p1.x*meter,p1.y*meter,p2.x*meter,p2.y*meter,rgba(color));
		
		p1 = p2;
		
		
		
	}
	
	
	
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color){
		
       BLPoint point[vertexCount];
       for(int i = 0;i<vertexCount;i++){
       	
       	point[i].x = vertices[i].x*meter;
       	point[i].y = vertices[i].y*meter;
       	
       }
		//b2Color fillcolor(0.5*color.r,0.5*color.g,0.5*color.b,0.5);
		b2Color fillcolor(color.r,color.g,color.b,0.5);
		ctx.fillPolygon(point,vertexCount,rgba(fillcolor));
	      ctx.strokePolygon(point,vertexCount,rgba(color));
		
		
	}

	void DebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color){
		
		ctx.strokeCircle(center.x*meter,center.y*meter,radius*meter,rgba(color));
		
		
	}

	void DebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color){
		
		b2Vec2 p = center + radius*axis;
		//b2Color fillcolor(0.5*color.r,0.5*color.g,0.5*color.b,0.5);
		b2Color fillcolor(color.r,color.g,color.b,0.5);
		ctx.fillCircle(center.x*meter,center.y*meter,radius*meter,rgba(fillcolor));
		ctx.strokeCircle(center.x*meter,center.y*meter,radius*meter,rgba(color));         
		ctx.strokeLine(center.x*meter,center.y*meter,p.x*meter,p.y*meter,rgba(color));
		
		
		
	}

	void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color){
		
		
		ctx.strokeLine(p1.x*meter,p1.y*meter,p2.x*meter,p2.y*meter,rgba(color));
		
		
		
	}

	void DebugDraw::DrawTransform(const b2Transform& xf){
		const float k_axisScale = 0.4f;
	b2Color red(1.0f, 0.0f, 0.0f);
	b2Color green(0.0f, 1.0f, 0.0f);
	b2Vec2 p1 = xf.p, p2;
	
	p2 = p1 + k_axisScale * xf.q.GetXAxis();
     
     ctx.strokeLine(p1.x*meter,p1.y*meter,p2.x*meter,p2.y*meter,rgba(red));

	p2 = p1 + k_axisScale * xf.q.GetYAxis();
		
      ctx.strokeLine(p1.x*meter,p1.y*meter,p2.x*meter,p2.y*meter,rgba(green));
		
		
	}

	void DebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color){
		
		
		ctx.fillCircle(p.x*meter,p.y*meter,size,rgba(color));
		
		
		
	}
	BLRgba32 DebugDraw::rgba(const b2Color&color){
	
	
	return BLRgba32(color.r*255,color.g*255,color.b*255,color.a*255);
	
	
}