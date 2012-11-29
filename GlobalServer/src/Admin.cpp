#include "Admin.h"

std::string Admin::get_cmd()
{
    return m_cmd;
}

void Admin::set_cmd(std::string cmd)
{
 m_cmd = cmd;
}

std::string Admin::get_passwd()
{
    return m_passwd;
}

void Admin::set_passwd(std::string passwd)
{
    m_passwd = passwd;
}

std::string Admin::get_pseudo()
{
    return m_pseudo;
}

void Admin::set_pseudo(std::string pseudo)
{
    m_pseudo = pseudo;
}



 Admin::~Admin()
{

}

 Admin::Admin():m_pseudo(""), m_passwd(""), m_cmd("")
{

}

