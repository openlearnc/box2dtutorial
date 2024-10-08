#include"draw.h"

DebugDraw::DebugDraw(NVGcontext*&context):meter(100.f),ctx(context){
	
	
	
	
	
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color){

       //nvgBeginPath(ctx);
     b2Vec2 p1 = vertices[vertexCount-1];
     nvgBeginPath(ctx);
     nvgMoveTo(ctx,p1.x*meter,p1.y*meter);
     for(int i = 0;i<vertexCount;i++){
     	
     	b2Vec2 p2 = vertices[i];
     	nvgLineTo(ctx,p2.x*meter,p2.y*meter);
     	
    }
     
     
     nvgStrokeColor(ctx,rgba(color));
     nvgStroke(ctx);
	
	
}

	void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color){
		
		
		//b2Color fillcolor(0.5f*color.r,0.5f*color.g,0.5f*color.b,0.5f);
		b2Color fillcolor(0.5f*color.r,0.5f*color.g,0.5f*color.b,1.0f);
		b2Vec2 p1 = vertices[vertexCount-1];
		
		nvgBeginPath(ctx);
		nvgMoveTo(ctx,p1.x*meter,p1.y*meter);
		for(int i = 0;i<vertexCount;i++){
			
			b2Vec2 p2 = vertices[i];
			nvgLineTo(ctx,p2.x*meter,p2.y*meter);
			
		}
		
		nvgFillColor(ctx,rgba(fillcolor));
		nvgFill(ctx);
		
		nvgBeginPath(ctx);
		nvgMoveTo(ctx,p1.x*meter,p1.y*meter);
		for(int i = 0;i<vertexCount;i++){
			
			b2Vec2 p2 = vertices[i];
			
			nvgLineTo(ctx,p2.x*meter,p2.y*meter);
			
			
			
		}
		nvgStrokeColor(ctx,rgba(color));
		nvgStroke(ctx);
		
		
	}

	void DebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color){
		
		nvgBeginPath(ctx);
		
		nvgCircle(ctx,center.x*meter,center.y*meter,radius*meter);
		nvgStrokeColor(ctx,rgba(color));
		nvgStroke(ctx);
		
		
	}

	void DebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color){
		
		//b2Color fillcolor(0.5f*color.r,0.5f*color.g,0.5f*color.b,0.5f);
		  b2Color fillcolor(0.5f*color.r,0.5f*color.g,0.5f*color.b,1);
		nvgBeginPath(ctx);
		
		nvgCircle(ctx,center.x*meter,center.y*meter,radius*meter);
		
		nvgFillColor(ctx,rgba(fillcolor));
		
		b2Vec2 p = center + radius*axis;
		
		nvgBeginPath(ctx);
		
		nvgMoveTo(ctx,center.x*meter,center.y*meter);
		nvgLineTo(ctx,p.x*meter,p.y*meter);
		nvgStrokeColor(ctx,rgba(color));
		nvgStroke(ctx);
		
		
	}

	void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color){
		
		  nvgBeginPath(ctx);
		  nvgMoveTo(ctx,p1.x*meter,p1.y*meter);
		  nvgLineTo(ctx,p2.x*meter,p2.y*meter);
		  
		  nvgStrokeColor(ctx,rgba(color));
		  
		  nvgStroke(ctx);
		
		
	}

	void DebugDraw::DrawTransform(const b2Transform& xf){
		
		const float k_axisScale = 0.4f;
	b2Color red(1.0f, 0.0f, 0.0f);
	b2Color green(0.0f, 1.0f, 0.0f);
	b2Vec2 p1 = xf.p, p2;

	p2 = p1 + k_axisScale * xf.q.GetXAxis();
	nvgBeginPath(ctx);
	nvgMoveTo(ctx,p1.x*meter,p1.y*meter);
	nvgLineTo(ctx,p2.x*meter,p2.y*meter);
	
	nvgStrokeColor(ctx,rgba(red));
	nvgStroke(ctx);


	p2 = p1 + k_axisScale * xf.q.GetYAxis();
	
	  nvgBeginPath(ctx);
	  nvgMoveTo(ctx,p1.x*meter,p1.y*meter);
	  nvgLineTo(ctx,p2.x*meter,p2.y*meter);
	  nvgStrokeColor(ctx,rgba(green));
	  nvgStroke(ctx);
		
		
	}

	void DebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color){
		
		nvgBeginPath(ctx);
		nvgCircle(ctx,p.x*meter,p.y*meter,size);
		nvgFillColor(ctx,rgba(color));
		nvgFill(ctx);
		
		
		
		
	}
	
	
	NVGcolor DebugDraw::rgba(const b2Color &color){
		
		
		NVGcolor colord;
		colord.r = color.r;
		colord.g = color.g;
		colord.b = color.b;
		colord.a = color.a; 
		
		return colord;
		
	}