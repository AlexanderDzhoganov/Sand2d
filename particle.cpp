#include "../include/headers.h"

// particle

Particle::Particle(ParticleMgr* pmgr_n, int x, int y) {
	pmgr = pmgr_n;
	pos_x = x;
	pos_y = y;
	color = 0xffffffff;
	type = SAND;
}

Particle::~Particle() {

}

void Particle::update(int* ret_x, int* ret_y) {
	bool moved = false;

	if(!pmgr->collide(pos_x, pos_y+1)) {
		pos_y++;
		moved = true;
	} else {
		if(rand()%2==1) {
			if(!pmgr->collide(pos_x+1, pos_y+1)) {
				pos_x++;
				pos_y++;
				moved = true;
			} else if(!pmgr->collide(pos_x-1, pos_y+1)) {
				pos_x--;
				pos_y++;
				moved = true;
			}
		} else {
			if(!pmgr->collide(pos_x-1, pos_y+1)) {
				pos_x--;
				pos_y++;
				moved = true;
			} else if(!pmgr->collide(pos_x+1, pos_y+1)) {
				pos_x++;
				pos_y++;
				moved = true;
			}
		}
	}

	if(pmgr->collide(pos_x, pos_y-1) && !moved) {
		if(rand()%2==1) {
			if(!pmgr->collide(pos_x+1, pos_y)) {
				pos_x++;
			} else if(!pmgr->collide(pos_x-1, pos_y)) {
				pos_x--;
			}
		} else {
			if(!pmgr->collide(pos_x-1, pos_y)) {
				pos_x--;
			} else if(!pmgr->collide(pos_x+1, pos_y)) {
				pos_x++;
			}
		}
	}

	*ret_x = pos_x;
	*ret_y = pos_y;
	
	
}

void Particle::drawSelf() {
	pmgr->plot(pos_x, pos_y, color);
}

void Particle::getPosition(int* ret_x, int* ret_y) {
	*ret_x = pos_x;
	*ret_y = pos_y;
}

void Particle::setPosition(int x, int y) {
	pos_x = x;
	pos_y = y;
}

ParticleType Particle::getType() { 
	return type;
}

// particlemgr

ParticleMgr::ParticleMgr(Tmpl8::Game* game_n) {
	game = game_n;
	game->addNode(this);

	timeAccumulator = 0.f;

	for(int x=0; x<GRID_WIDTH; x++) {
		for(int y=0; y<GRID_HEIGHT; y++) {
			spatial[x][y] = EMPTY;
			collisionMap[x][y] = 0;
		}
	}



	buildSpatial();
	loadCollisionMap("collision.bmp");
	particles_n = 0;
}

ParticleMgr::~ParticleMgr() {

}

void ParticleMgr::loadCollisionMap(char* filename) {
	for(int x=0; x<GRID_WIDTH; x++)
	for(int y=0; y<GRID_HEIGHT; y++) {
		collisionMap[x][y] = false;
	}

	collisionBitmap = new Tmpl8::Surface(filename);
	for(int x=0; x<GRID_WIDTH; x++)
	for(int y=0; y<GRID_HEIGHT; y++) {
		if(collisionBitmap->GetBuffer()[x+y*GRID_WIDTH] != 0xff000000) {
 			collisionMap[x][y] = true;
		}
	}
}

void ParticleMgr::update(float frameDelta) {
	collisionBitmap->CopyTo(game->getScreen(), 0, 0);

	timeAccumulator += frameDelta;

	if(timeAccumulator > 10.f) {
		for(std::list<Particle*>::iterator i = particles.begin(); i != particles.end(); i++) {
			int x, y;
			(*i)->getPosition(&x, &y);
			int new_x, new_y;
			(*i)->update(&new_x, &new_y);
			spatial[x][y] = EMPTY;
			spatial[new_x][new_y] = (*i)->getType();
		}
		timeAccumulator = 0.f;
		

		for(int x=0;x<10;x++) if(rand()%3==1) {
			addParticle(SAND, 400+x, rand()%5);
			particles_n++;
		}

		for(int x=0;x<10;x++) if(rand()%3==1) {
			addParticle(WATER, 100+x, rand()%5);
			particles_n++;
		}
		std::cout << particles_n << std::endl;

		//buildSpatial();
	}

	for(std::list<Particle*>::iterator i = particles.begin(); i != particles.end(); i++) {
		(*i)->drawSelf();
	}



	/*for(int x=0; x<GRID_WIDTH; x++)
	for(int y=0; y<GRID_HEIGHT; y++) {
		if(spatial[x][y] != EMPTY)
			game->getScreen()->Plot(x, y, 0xffff0000);
	}*/
}

void ParticleMgr::plot(int x, int y, unsigned long c) {
	game->getScreen()->Plot(x, y, c);
}

ParticleType ParticleMgr::collide(int x, int y) {
	if(x<0 || x>=GRID_WIDTH || y<0 || y>=GRID_HEIGHT) return COLLISIONMAP;
	if(spatial[x][y] != EMPTY) return spatial[x][y];
	if(collisionMap[x][y]) return COLLISIONMAP;
	return EMPTY;
}

void ParticleMgr::buildSpatial() {
	for(int x=0; x<GRID_WIDTH; x++)
	for(int y=0; y<GRID_HEIGHT; y++) {
		spatial[x][y] = EMPTY;
	}

	for(std::list<Particle*>::iterator i = particles.begin(); i != particles.end(); i++) {
		int x, y;
		(*i)->getPosition(&x, &y);
		spatial[x][y] = (*i)->getType();
	}
}

void ParticleMgr::addParticle(ParticleType type, int x, int y) {
	if(collide(x, y)) return;

	Particle* p;

	switch(type) {
	case WATER:
		p = new Water(this, x, y);
		particles.push_back(p);
		break;
	case SAND:
		p = new Sand(this, x, y);
		particles.push_back(p);
		break;
	}
	
}

void ParticleMgr::swapParticles(int a_x, int a_y, int b_x, int b_y) {
//Particle* tmp = spatial[a_x][a_y];
//	spatial[a_x][a_y] = spatial[b_x][b_y];
//	spatial[b_x][a_x] = tmp;

	//spatial[a_x][a_y]->setPosition(a_x, a_y);
//	spatial[b_x][b_y]->setPosition(b_x, b_y);
}