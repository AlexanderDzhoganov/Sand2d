#include "headers.h"

Sand::Sand(ParticleMgr* pmgr_n, int x, int y) : Particle(pmgr_n, x, y) {
	type = SAND;
	color = 0xfff88017;
}

Sand::~Sand() {

}

void Sand::update(int* ret_x, int* ret_y) {
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