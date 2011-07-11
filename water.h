#ifndef __WATER_H
#define __WATER_H

class Water : public Particle {
	public:
	Water(ParticleMgr* pmgr_n, int x, int y);
	~Water();
	void update(int* ret_x, int* ret_y);
};

#endif