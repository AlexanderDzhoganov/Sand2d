#ifndef __PARTICLE_H
#define __PARTICLE_H

class ParticleMgr;

enum ParticleType {
	EMPTY = 0,
	SAND,
	WATER,
	OIL,
	COLLISIONMAP,
};

class Particle {
	public:
	unsigned long color;
	ParticleType type;
	ParticleMgr* pmgr;
	int pos_x, pos_y;

	Particle(ParticleMgr* pmgr_n, int x, int y);
	~Particle();
	virtual void update(int* ret_x, int* ret_y);
	void drawSelf();
	void getPosition(int* ret_x, int* ret_y);
	void setPosition(int x, int y);
	ParticleType getType();
};

class ParticleMgr : public GameNode {
	ParticleType spatial[GRID_WIDTH][GRID_HEIGHT];
	bool collisionMap[GRID_WIDTH][GRID_HEIGHT];
	std::list<Particle*> particles;
	Tmpl8::Surface* collisionBitmap;

	float timeAccumulator;

	int particles_n;

	public:
	ParticleMgr(Tmpl8::Game* game_n);
	~ParticleMgr();
	void loadCollisionMap(char* filename);
	void update(float frameDelta);
	void plot(int x, int y, unsigned long c);
	ParticleType collide(int x, int y);
	void buildSpatial();
	void addParticle(ParticleType type, int x, int y);
	void swapParticles(int a_x, int a_y, int b_x, int b_y);
};

#endif