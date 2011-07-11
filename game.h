#pragma once

namespace Tmpl8 {

class Surface;

class Game {
	GameNode* scene;
	ParticleMgr* pmgr;
	
	Surface* m_Screen;

	int frameCounter;
	float fpsLimit;
	int fps;
	
	float timeAccumulator;



	public:
	void SetTarget( Surface* a_Surface ) { m_Screen = a_Surface; }
	void Init();
	void Tick( float a_DT );
	void KeyDown( unsigned int code ) {}
	void KeyUp( unsigned int code ) {}
	void MouseMove( unsigned int x, unsigned int y ) {}
	void MouseUp( unsigned int button ) {}
	void MouseDown( unsigned int button ) {}
	void addNode(GameNode* node, GameNode* parent=NULL);
	Surface* getScreen();
	ParticleMgr* getParticleMgr();
};

};