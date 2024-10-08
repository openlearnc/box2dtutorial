#include <stdio.h>
#include <stdlib.h>
//#include <android/log.h>
#include <GLES2/gl2.h>
#include <SDL2/SDL.h>
//#include <SDL2/SDL_opengles2.h>
//#define GLFW_INCLUDE_ES2
#define NANOVG_GLES2_IMPLEMENTATION
#include "nanovg.h"
#include "nanovg_gl.h"
#include "nanovg_gl_utils.h"
#include "box2d.h"
#include "draw.h"
SDL_Window*window;
static void window_size(int* width, int* height, float* pixel_ratio)
{
	int prev_width = *width;
	int prev_height = *height;
	SDL_GL_GetDrawableSize(window, width, height);
	if ((*width != prev_width || *height != prev_height)) {
		printf("%d×%d -> %d×%d\n", prev_width, prev_height, *width, *height);
	}

	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	*pixel_ratio = *width / w;
}
int main(int argc, char **argv) { //SDL entry point, at least on android
//  SDL_Window *window = NULL;
  SDL_GLContext context;
  SDL_Event event;
  NVGcontext* vg = NULL;
  
    int flags = SDL_INIT_EVERYTHING & ~(SDL_INIT_TIMER | SDL_INIT_HAPTIC);//only SDL_INIT_EVERYTHING may suffice
    if (SDL_Init(flags) < 0)//if it doesn't work, try and log a helpful error
    {
    	printf("error: sdl2 init failed: %s\n", SDL_GetError());
        return 1;
    }
    //better safe than sorry vv
    //SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_SetHint(SDL_HINT_RENDER_DRIVER,"opengl");
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);
   window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 800,
      SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);//only SDL_WINDOW_OPENGL may suffice
  //window = SDL_CreateWindow("Hello SDL2 OpenGL ES", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);
        if (!window)//if this doesn't work, it's probably becouse of an error. so we log it
        {
     printf("error2: sdl2 init failed: %s\n", SDL_GetError());
            return 1;
        }
    
    context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, context);
    
    vg = nvgCreateGLES2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);//initialize nanovg. if it fails, log it. there is no get_error though.
    if (vg == NULL) {
      printf("error: nanovg init failed\n");
        return 1;
    }
    
   int screen_width = 0;
	int screen_height = 0;
	float pixel_ratio = 0.0f;
	window_size(&screen_width, &screen_height, &pixel_ratio);
  
 
    int quit=0;
    int t = SDL_GetTicks(),tt;
    int frame = 0;
    
    
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
  b2PolygonShape dybox1;
  dybox1.SetAsBox(box1w/2-dybox1.m_radius,box1h/2-dybox1.m_radius);
  b2FixtureDef fixd1;
  fixd1.shape = &dybox1;
  fixd1.density = 1.0f;
  fixd1.friction = 0.5f;
  fixd1.restitution = 0.5f+0.2;
  
  body1->CreateFixture(&fixd1);
  
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
    
    
       DebugDraw draw(vg);
       nvgCreateFont(vg,"Sans","/system/fonts/DroidSans.ttf");
       nvgFontSize(vg, 120.0f);
       draw.SetFlags(b2Draw::e_shapeBit|b2Draw::e_jointBit);
       world->SetDebugDraw(&draw);
 
    while (!quit)//main loop
    {   
            frame++;

        SDL_PollEvent(&event);//are there any interesting events for us?

        switch(event.type)
        {
        case SDL_QUIT:
          quit=1;
          break;

        }
       
       glViewport(0, 0, screen_width-600, screen_height);
		//glClearColor(1, 1, 1, 0);
		glClearColor(0,0,0,0);
		glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		/*glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);*/
          
		nvgBeginFrame(vg, (screen_width-600) / pixel_ratio, screen_height / pixel_ratio, pixel_ratio);
      //important, guess it's not like framebuffer
      
        /*nvgBeginPath(vg);//this is your masterpiece
		nvgCircle(vg,500,200,100);//same
		nvgFillColor(vg, nvgRGBA(255,192,0,255));//same
		nvgFill(vg);//same
		
		
		{
			nvgStrokeWidth(vg,6);
			nvgBeginPath(vg);
		   
			nvgMoveTo(vg,200,200);
			nvgLineTo(vg,200,300);
			nvgLineTo(vg,300,300);
			nvgClosePath(vg);
			nvgLineCap(vg,NVG_SQUARE);
			nvgStrokeColor(vg,nvgRGBA(126,126,126,255));
		
			nvgStroke(vg);
			nvgFillColor(vg,nvgRGBA(126,126,126,126));
			nvgFill(vg);
			
			nvgBeginPath(vg);
			nvgMoveTo(vg,300,600);
			nvgLineTo(vg,300,800);
			nvgMoveTo(vg,400,400);
			nvgLineTo(vg,400,500);
			nvgStrokeColor(vg,nvgRGBA(66,66,66,255));
			nvgStroke(vg);
			
			
		}*/
		
	    nvgStrokeWidth(vg,1+1);
		world->DebugDraw();
		nvgEndFrame(vg);//if we started a frame, it makes sense to end it
		SDL_GL_SwapWindow(window);//we have double bufferring by default, so make sure our changes get on the screen
          world->Step(1.0/60.0f,6.0f,2.0f);
       
          if(frame%30==0){
          	
            tt = SDL_GetTicks();
           printf("%lf\n",frame*1000.f/(tt-t));	
          	t = tt;
          	frame = 0;
          	
          	
          }
  
      
          
              
                      }
    
    return 0;
}
