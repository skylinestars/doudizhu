#pragma once
#include "string"



class LoginController
{
public:
	/// <summary>
	/// 登录处理
	/// </summary>
	/// <param name="username">用户名</param>
	/// <param name="password">密码</param>
	/// <returns>是否成功</returns>
	bool loginHandle(const std::string& username, const std::string& password);
	
	/// <summary>
	/// 注册处理
	/// </summary>
	/// <param name="username">用户名</param>
	/// <param name="password">密码</param>
	/// <param name="passwordOK">确认密码</param>
	/// <returns>是否注册成功</returns>
	bool registerHandle(const std::string& username, const std::string& password, const std::string& passwordOK);

};