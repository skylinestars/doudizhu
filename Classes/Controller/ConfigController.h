#pragma
#include <map>
#include "cocos2d.h"

USING_NS_CC;

class ConfigController
{

public:
	static ConfigController* getInstance();
	std::string getWordById(int id);
	void initWord();
	void setScale(float scale)
	{
		this->_scale = scale;
	}
	float getScale()
	{
		return this->_scale;
	}
private:
	ConfigController();
	static ConfigController* _instance;
	float _scale;
	std::map<int, Value> _words;
};