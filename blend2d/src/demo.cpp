#include <SDL2/SDL.h>
#include "blend2d.h"
#include <list>
#include <stdio.h>
#include <unistd.h>
#include "box2d.h"
#include "draw.h"
using namespace std;
struct touch{
	
	bool down;
	float x,y;
	
	
}touch[10];

int main(){
    SDL_Window * window;
    SDL_Renderer * renderer;
    
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
     
    }
    
    if(!(window = SDL_CreateWindow("win", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1026, 800, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE))){
    
    }
    
    if(!(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC))){
       
    }
    
    SDL_Event e;
    int screenw,screenh;
    SDL_GetWindowSize(window,&screenw,&screenh);
    printf("%d %d\n",screenw,screenh);
   SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0,1026,800,32,SDL_PIXELFORMAT_ARGB8888);
  
     BLImage img;
    img.createFromData(surface->w,surface->h,BL_FORMAT_PRGB32,(void*)surface->pixels,surface->w*4);
   // BLContextCreateInfo bl_cci;
   // bl_cci.threadCount = 1;
   // BLContext ctx(img,bl_cci);
   BLContext ctx;
   BLPath path;
   BLFontFace fontface;
   BLFont font;
   fontface.createFromFile("/system/fonts/SysSans-Hant-Regular.ttf");
   font.createFromFace(fontface,60);
   //ctx = BLContext(img);
   /*= BLContext(img);
  
    ctx.setCompOp(BL_COMP_OP_DST_COPY);
    ctx.fillAll();
    
    ctx.setCompOp(BL_COMP_OP_SRC_OVER);
    ctx.setFillStyle(BLRgba32(0,0,0,255));
    ctx.fillRoundRect(50, 50, 400, 400, 50);
    
    //ctx.end();
    */
  //  img.writeToFile("img.png");
    
 //  BLImageData data;
    //img.getData(&data);
    //SDL_UpdateTexture(texture, NULL, data.pixelData, int(data.stride));
  BLImageData data;
  SDL_Texture*texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 1026, 800);
    char str[ ] = "hello world";//800 1000
    SDL_Rect rect = {0,0,1026,800};
     int x = 0;
     int frame = 0;
     uint32_t then = SDL_GetTicks(),now;
     BLContext ctxd;BLImage imgd(600,600,BL_FORMAT_PRGB32);
     //textured = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 500, 500);
    
  //SDL_SetTextureBlendMode(textured, SDL_BLENDMODE_BLEND);
  const float rad = M_PI/180;
  const float meter = 100.f;
  b2World*world = new b2World(b2Vec2(0.0f,9.8f));//重力
  b2Body*body1;
  b2BodyDef box1;
  box1.type = b2_dynamicBody;
  float box1x = 600/meter,box1y = 0.0f/meter,box1w = 1.0f,box1h=1.0f;
  box1.angle = 0.0f;
  box1.position.Set(box1x,box1y);
  body1 = world->CreateBody(&box1);
  //b2PolygonShape dybox1;
  //dybox1.SetAsBox(box1w/2-dybox1.m_radius,box1h/2-dybox1.m_radius);
  
  /*b2CircleShape dybox1;
  dybox1.m_p.Set(0,0);
  dybox1.m_radius = 0.5f;*/
  b2PolygonShape dybox1;
  //b2Vec2 point[6] = {{1.f,2.f},{2,1},{3,1.6},{3,2},{3,3},{2,2+2}};
  b2Vec2 point[3] = {{0,-1},{-1,1},{1,1}};
  point[0].Set(0.5,0.5);
  point[1].Set(-0.5,0.5);
  point[2].Set(0,-0.5);
  dybox1.Set(point,3);
  b2FixtureDef fixd1;
  fixd1.shape = &dybox1;
  fixd1.density = 1.0f;
  fixd1.friction = 0.5f;
  fixd1.restitution = 0.5f+0.2;
  
  body1->CreateFixture(&fixd1);
  //body1->SetLinearVelocity(b2Vec2(0,-5.f+6+2));
  
  b2Body*body;
  b2BodyDef box;
  box.type = b2_dynamicBody;
 // float angle =  0.0f*M_PI/180;
  //float meter = 100;
  float boxx = 200/meter;
  float boxy = 10/meter;
  float boxw = 100/meter;
  float boxh = 100/meter;
  box.angle = 0.0f*rad;
  //ibox.allowSleep = false;
  box.position.Set(boxx,boxy);
  
  //b2Vec2 vel;
  //vel.Set(0.0,-5.0f);
  //vel.Set(1.0f+1.20f,-6.0f-14.0f);
  body = world->CreateBody(&box);
  
  //body->SetLinearVelocity(vel);
  //body->SetGravityScale(0);
  //body->SetFixedRotation(true);
  b2PolygonShape dybox;
  dybox.SetAsBox(boxw/2-dybox.m_radius,boxh/2-dybox.m_radius);
  printf("%f\n",dybox.m_radius);
  b2FixtureDef fixd;
    fixd.shape = &dybox;
    fixd.density = 1.f;
    fixd.friction = 0.1f;
    fixd.restitution = 0.1f;
    body->CreateFixture(&fixd);
    
   b2Vec2 sp,sp1,ep,ep1;
   //float groundx = 0.0f;
   //float groundy = 0.0f;
    sp.x = 0.0f;
    sp.y = 15.0f;
    
    sp1.x = 0.0f;
    sp1.y = 6.0f;
    ep.x = 8.0f;
    ep.y = 6.0f-0.4+0.4;
    
    ep1.x = 6.0f+4.0f;
    ep1.y = 5.0f;
    b2BodyDef ground;
    ground.type = b2_staticBody;
    //ground.position.Set(groundx,groundy);
    ground.angle = 0;
    b2Body*gbody = world->CreateBody(&ground);
    b2EdgeShape edgeshape;
   
    //edgeshape.SetOneSided(sp,sp1,ep,ep1);
    edgeshape.SetTwoSided(sp1,ep);
    
    b2FixtureDef edgefix;
    edgefix.density= 1;
    edgefix.friction = 0.1;
    edgefix.restitution = 0.1;
    edgefix.shape = &edgeshape;
    gbody->CreateFixture(&edgefix);
    DebugDraw draw(ctx);
    draw.SetFlags(b2Draw::e_shapeBit|b2Draw::e_jointBit);
    world->SetDebugDraw(&draw);

    while (true) {
        frame++;
        while (SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT)
                 exit(0);
                
            switch(e.type){
                case SDL_FINGERDOWN:
                touch[e.tfinger.fingerId].down = true;
                touch[e.tfinger.fingerId].x=e.tfinger.x*screenw;
               touch[e.tfinger.fingerId].y =e.tfinger.y*screenh;
           //printf("%f,%f\n",touch[0].x,touch[0].y);
                break;
                
                case SDL_FINGERMOTION:
                
                break;
                
                case SDL_FINGERUP:
                
                 touch[e.tfinger.fingerId].down = 0;
                 touch[e.tfinger.fingerId].x = 0.0;
                 
                 touch[e.tfinger.fingerId].y = 0.0;
                
           }     
        }
        	    
        //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_SetRenderDrawColor(renderer,0,0,0,0);
     
        SDL_RenderClear(renderer);
    
     //lctx = BLContext(img);
      //lctx.save();
    //  ctx.setCompOp(BL_COMP_OP_DST_OVER);
 //ctx.save();
/*ctx.setCompOp(BL_COMP_OP_CLEAR);
  ctx.fillAll();
ctx.setCompOp(BL_COMP_OP_SRC_OVER);*/
//ctx.setFillStyle(BLRgba32(0,255,255,125));
 //ctx.fillAll();
 ctx = BLContext(img);
 ctx.clearAll();
 ctx.setCompOp(BL_COMP_OP_SRC_OVER);
 ctx.setStrokeWidth(2);
 world->DebugDraw();
    //  ctx.rotate(x*M_PI/180,200,200);
    // ctx.restore();
     //ctx.save();
     /*dctx.save();
     ctx.setFillStyle(BLRgba32(255,126,126,255));
    ctx.setCompOp(BL_COMP_OP_SRC_OVER);
    ctx.setStrokeWidth(1);
    ctx.strokeLine(edgeshape.m_vertex1.x*meter,edgeshape.m_vertex1.y*meter,edgeshape.m_vertex2.x*meter,edgeshape.m_vertex2.y*meter);
    ctx.restore();
    
    ctx.save();
    ctx.setFillStyle(BLRgba32(0,0,0,255));
    ctx.rotate(body1->GetAngle(),body1->GetPosition().x*meter,body1->GetPosition().y*meter);
    ctx.fillRect((body1->GetPosition().x-box1w/2)*meter,(body1->GetPosition().y-box1h/2)*meter,box1w*meter,box1h*meter);
    //ctx.fillCircle(body1->GetPosition().x*meter,body1->GetPosition().y*meter,0.5*meter);
    /*b2Vec2 p1 = body1->GetPosition();
    for(int i = 0;i<3-1;i++){
    	
    	ctx.strokeLine((point[i].x+p1.x)*meter,(point[i].y+p1.y)*meter,(point[i+1].x+p1.x)*meter,(point[i+1].y+p1.y)*meter);
    	
    	
    }
    ctx.strokeLine((point[2].x+p1.x)*meter,(point[2].y+p1.y)*meter,(point[0].x+p1.x)*meter,(point[0].y+p1.y)*meter);*/
    /* dctx.restore();
    
    	ctx.save();
    	ctx.rotate(cibody->GetAngle(),cibody->GetPosition().x*meter,cibody->GetPosition().y*meter);
    	
    	ctx.setFillStyle(BLRgba32(0,255,0,255));
    	ctx.fillCircle(cibody->GetPosition().x*meter,cibody->GetPosition().y*meter,(0.5)*meter);
    	ctx.setStrokeWidth(6);
    	ctx.strokeLine(cibody->GetPosition().x*meter,cibody->GetPosition().y*meter,cibody->GetPosition().x*meter,(cibody->GetPosition().y+0.5)*meter);
    	ctx.restore();
    	
    	
    	
    
    ctx.save();
    ctx.setFillStyle(BLRgba32(0,255,255,255));
    pos= body->GetPosition();
    ctx.rotate(body->GetAngle(),pos.x*meter,pos.y*meter);
    ctx.setStrokeWidth(6);
    ctx.strokeLine(pos.x*meter,pos.y*meter,pos.x*meter,(pos.y+boxh/2)*meter);     
    ctx.setFillStyle(BLRgba32(0,0,125,126));
    ctx.fillRect((pos.x-boxw/2)*meter,(pos.y-boxh/2)*meter,boxw*meter,boxh*meter);d*/
    //ctx.rotate(body->GetAngle()*rad,pos.x*meter,pos.y*meter);
    //dctx.restore();

   // img.writeToFile("2.png");
 //  BLImageData data;
   
   img.getData(&data);
    
     SDL_UpdateTexture(texture,NULL,data.pixelData,data.stride);
     SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_BLEND);
     //   SDL_SetRenderDrawColor(renderer,0,0,0,255);
          
        //SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,surface);
         
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
        
        //rect.x+=4;
        SDL_RenderPresent(renderer);
        //SDL_DestroyTexture(texture);
        world->Step(1.0f/60.0f,6.0f,2.0f);

        now = SDL_GetTicks();
        if(now>then){
        	if(frame%30==0){
        	//if(((now-then)%2000)>1960){
        		
        		printf("%f\n",((double)frame*1000)/(now-then));
        		printf("%d\n",now-then);printf("%f\n",body->GetPosition().y);
        		frame = 0;
        		then = now;
        
        	//	img.writeToFile("ima.png");
        		}
        	
        
        	}
       // SDL_Delay(2);
     
    }
      
         SDL_FreeSurface(surface);
         
         delete world; 
   
   
}