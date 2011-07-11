#include "headers.h"

Water::Water(ParticleMgr* pmgr_n, int x, int y) : Particle(pmgr_n, x, y) {
	type = WATER;
	color = 0xff0022ff;
}

Water::~Water() {

}

void Water::update(int* ret_x, int* ret_y) {
	bool moved = false;

	if(!pmgr->collide(pos_x, pos_y+1)) {
		pos_y++;
		moved = true;
	}
	
	if(rand()%2==1) {
		if(!pmgr->collide(pos_x+1, pos_y)) {
			pos_x++;
			moved = true;
		} else if(!pmgr->collide(pos_x-1, pos_y)) {
			pos_x--;
			moved = true;
		}
	} else {
		if(!pmgr->collide(pos_x-1, pos_y)) {
			pos_x--;
			moved = true;
		} else if(!pmgr->collide(pos_x+1, pos_y)) {
			pos_x++;
			moved = true;
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