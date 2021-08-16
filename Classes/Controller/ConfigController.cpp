#include "ConfigController.h"


ConfigController* ConfigController::_instance = nullptr;

ConfigController::ConfigController():
    _scale(1.0f)
{
    initWord();
}

ConfigController* ConfigController::getInstance()
{
	if (_instance==nullptr)
	{
		_instance = new ConfigController();
	}
	return _instance;
}

std::string ConfigController::getWordById(int id)
{

    if (_words.size()==0 || _words.at(id).isNull())
    {
        return std::string();
    }
    else
    {
        return _words.at(id).asString();
    }
	
}

void ConfigController::initWord()
{
    //���ּ��ؽ�����ʾ
    auto configData = FileUtils::getInstance()->getValueMapFromFile("plist/font.plist");
    //������������
    for (auto vaPair : configData)
    {
        int key = atoi(vaPair.first.c_str());
        Value val = vaPair.second;
        _words.insert(std::pair<int, Value>(key, val));
    }
}
