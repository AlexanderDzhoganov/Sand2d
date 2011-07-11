// Template, major revision 3
// IGAD/NHTV - Jacco Bikker - 2006-2009

#include "../include/headers.h"

using namespace Tmpl8;

void Game::Init()
{
	srand(time(NULL));
	scene = new GameNode();
	fps = 0;
	frameCounter = 0;
	timeAccumulator = 0.f;
	fpsLimit = 1.f; 
	pmgr = new ParticleMgr(this);
}

void Game::Tick( float a_DT )
{
	m_Screen->Clear(0);
	scene->update(a_DT);
}


void Game::addNode(GameNode* node, GameNode* parent) {
	if(parent != NULL) {
		parent->addChild(node);
		node->parent = parent;
	} else {
		scene->addChild(node);
		node->parent = scene;
	}
}

Surface* Game::getScreen() {
	return m_Screen;
}

ParticleMgr* Game::getParticleMgr() {
	return pmgr;
}