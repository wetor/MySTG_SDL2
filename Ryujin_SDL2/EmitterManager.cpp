#include "pch.h"
#include "define.h"
#include "global.h"
#include "Manager.h"

NspEmitter::Emitter emitter[EMITTER_MAX];

namespace NspEmitter {
	void EmitterInit() {
		//emitter = new Emitter[EMITTER_MAX];
		//bullet = new NspBullet::Bullet[BULLET_MAX];
	}
	inline int search_emitter() {
		for (int i = 0; i < EMITTER_MAX; i++) {
			if (!emitter[i].isExist()) {
				return i;
			}
		}
		return -1;
	}

	int EmitterEnter(int enemy_id) {

		int k = search_emitter();
		if (k != -1)
			emitter[k].Init(enemy_id);
		return k;
	}

	void EmitterUpdate() {
		for (int i = 0; i < EMITTER_MAX; i++) {
			if (emitter[i].isExist()) {
				emitter[i].Update();
			}
		}
	}

	void EmitterClear() {
		for (int i = 0; i < EMITTER_MAX; i++) {
			emitter[i].Clear();
			
		}
	}
#ifdef DEBUG
	void EmitterNumberShow(int x, int y) {
		int num = 0;
		for (int i = 0; i < EMITTER_MAX; i++) {
			if (emitter[i].isExist()) {
				num++;
			}
		}
		NumberShow(x, y, "Emitter num", num);
	}
#endif
}