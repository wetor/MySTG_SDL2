# 游戏  
	
# 1、主循环  
	main.cpp [转移至 Game.cpp]  
# 2、单位管理
	UnitManager.cpp  
	## 自机  
		Player.cpp  
	## 敌人
		Enemy.cpp 
			Enemy->Emitter->Emirrer_barrage->Bullet
		Enemy_pattern.cpp  
	## BOSS
		Boss.cpp
		Boss_pattern.cpp   
		Boss_barrage.cpp  
# 3、子弹管理
	BulletManager.cpp  
## 自机子弹
		Player.cpp  
## 敌人子弹
		Shoter.cpp  
	## BOSS子弹 ;线程优化
		Shoter.cpp  
# 4、组件管理
	/*https://github.com/xysz0824/CrazyStorm2.0/tree/develop/Core/Component*/
	Component.cpp  
	## 发射器
		Emitter.cpp  
	## 多发射器
		MultiEmitter.cpp  
	## 激光发射器
		LaserEmitter.cpp  
	## 弹射版
		Rebounder.cpp  
	## 力场
		ForceField.cpp  
