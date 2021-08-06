#pragma once
#include "string"



class LoginController
{
public:
	/// <summary>
	/// ��¼����
	/// </summary>
	/// <param name="username">�û���</param>
	/// <param name="password">����</param>
	/// <returns>�Ƿ�ɹ�</returns>
	bool loginHandle(const std::string& username, const std::string& password);
	
	/// <summary>
	/// ע�ᴦ��
	/// </summary>
	/// <param name="username">�û���</param>
	/// <param name="password">����</param>
	/// <param name="passwordOK">ȷ������</param>
	/// <returns>�Ƿ�ע��ɹ�</returns>
	bool registerHandle(const std::string& username, const std::string& password, const std::string& passwordOK);

};