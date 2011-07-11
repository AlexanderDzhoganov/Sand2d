#ifndef __SAND_H
#define __SAND_H

class Sand : public Particle {
	public:
	Sand(ParticleMgr* pmgr_n, int x, int y);
	~Sand();
	void update(int* ret_x, int* ret_y);
};

#endif