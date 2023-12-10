#include"manager.h"
Manager::Manager(int id, string name, int did) {
	this->m_Id = id;
	this->m_Name = name;
	this->DeptId = did;
}
void Manager::showInfo() {
	cout << "经理编号：" << this->m_Id
		<< "\t经理的姓名：" << this->m_Name
		<< "\t岗位：" << this->getDeptName()
		<<"\t岗位职责:完成老板交给的任务，并下发任务给员工"<<endl;
}
string Manager::getDeptName() {
	return string("经理");
}