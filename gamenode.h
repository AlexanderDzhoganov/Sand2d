#ifndef __GAMENODE_H
#define __GAMENODE_H

enum GameNodeType {
	PARTICLE = 0,
};

namespace Tmpl8 { 
	class Game;
};

class GameNode {
	std::list<GameNode*>* children;
	
	public:
	Tmpl8::Game* game;

	char* name;
	GameNode* parent;
	GameNodeType type;
	bool _markForDeletion;
	
	GameNode();
	virtual ~GameNode();
	void setName(char* newName);
	char* getName();
	virtual void update(float frameDelta);
	void addChild(GameNode*);
	void deleteChild(GameNode* node);
	void deleteChildren();
	std::list<GameNode*>* getChildren();
	int getChildrenNum();
	int getAbsoluteChildrenNum();
	GameNode* findNodeByName(char* search_name);
	GameNode* findNodeByType(GameNodeType search_type);
};

#endif