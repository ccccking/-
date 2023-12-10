#include"workerManager.h"
#include"boss.h"
#include"employee.h"
#include"manager.h"
WorkerManager::WorkerManager() {
	//文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//读文件
	if (!ifs.is_open()) {
		cout << "文件不存在" << endl;
		//初始化属性
		//初始化人数
		this->m_EmpNum = 0;
		//初始化指针
		this->m_EmpArry = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件存在
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//文件为空
		cout << "文件为空" << endl;
		this->m_EmpNum = 0;
		//初始化指针
		this->m_EmpArry = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件存在，且有记录
	int num = this->get_EmpNum();
	cout << "职工人数为：" << num << endl;
	this->m_EmpNum = num;
	//开辟空间
	this->m_EmpArry = new Worker * [this->m_EmpNum];
	//将文件中的数据，存到数组中
	this->init_Emp();
	//for (int i = 0; i < this->m_EmpNum; i++) {
	//	cout << "职工编号：" << this->m_EmpArry[i]->m_Id
	//		<< " 姓名："<<this->m_EmpArry[i]->m_Name
	//		<<" 部门编号："<<this->m_EmpArry[i]->DeptId << endl;
	//}
}
void WorkerManager::Show_Menu() {
	cout << "*********************************************************" << endl;
	cout << "*****************  欢迎使用职工管理系统  ****************" << endl;
	cout << "********************  0.退出管理程序  *******************" << endl;
	cout << "********************  1.增加职工信息  *******************" << endl;
	cout << "********************  2.显示职工信息  *******************" << endl;
	cout << "********************  3.删除离职职工  *******************" << endl;
	cout << "********************  4.修改职工信息  *******************" << endl;
	cout << "********************  5.查找职工信息  *******************" << endl;
	cout << "********************  6.按照编号排序  *******************" << endl;
	cout << "********************  7.清空所有文档  *******************" << endl;
	cout << "*********************************************************" << endl;
}
void WorkerManager::ExitSystem() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);//退出程序
}
void WorkerManager::Add_Emp() {
	cout << "请输入添加职工的数量：" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0) {
		int newSize = this->m_EmpNum + addNum;
		//开辟空间
		Worker **newSpace=new Worker* [newSize];
		if (this->m_EmpArry != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArry[i];
			}
		}
		//批量添加新数据
		for (int i = 0; i < addNum; i++) {
			int id;
			string name;
			int dSelect;
			cout << "请输入第" << i + 1 << "个新职工编号：" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个新职工姓名：" << endl;
			cin >> name;
			cout << "请选择该职工岗位：" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;
			Worker* worker = NULL;
			switch (dSelect) {
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Employee(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			newSpace[this->m_EmpNum + i] = worker;

		}
		//释放原有空间
		delete[] this->m_EmpArry;
		//更改新空间指向
		this->m_EmpArry = newSpace;
		//更新新的职工人数
		this->m_EmpNum = newSize;
		//更新职工不为空的标志
		this->m_FileIsEmpty = false;
		//提示添加成功
		cout << "成功添加" << addNum << "名新职工！" << endl;
		//保存数据
		this->save();
	}
	else {
		cout << "数据有误" << endl;
	}
	//按任意键，清屏回到上级目录
	system("pause");
	system("cls");
}
void WorkerManager::save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//用输出方式打开文件
	//写文件
	for (int i = 0; i < this->m_EmpNum; i++) {
		ofs << this->m_EmpArry[i]->m_Id << " "
			<< this->m_EmpArry[i]->m_Name << " "
			<< this->m_EmpArry[i]->DeptId << endl;
	}
	ofs.close();
}
int WorkerManager::get_EmpNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		num++;
	}
	return num;
}
//初始化职工
void WorkerManager::init_Emp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		Worker* worker = NULL;
		if (dId == 1) {//普通职工
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2) {
			worker = new Manager(id, name, dId);
		}
		else {
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArry[index] = worker;
		index++;
	}
	ifs.close();
}
void WorkerManager::Show_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		for (int i = 0; i < m_EmpNum; i++) {
			//调用程序接口
			this->m_EmpArry[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}
//删除职工
void WorkerManager::Del_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在" << endl;
	}
	else {
		//按职工编号删除
		cout << "请输入想要删除的职工编号：" << endl;
		int id = 0;
		cin >> id;
		int index=this->IsExist(id);
		if (index != -1) {//说明职工存在，并且删除index位置的职工
			for (int i = index; i < this->m_EmpNum - 1; i++) {
				this->m_EmpArry[i] = this->m_EmpArry[i + 1];
			}
			this->m_EmpNum--;
			this->save();//更新文件
			cout << "删除成功！" << endl;
		}
		else {
			cout << "删除失败，未找到职工" << endl;
		}
	}
	system("pause");
	system("cls");
}
//判断职工是否存在 如果存在返回职工所在数组位置，不存在返回-1
int WorkerManager::IsExist(int id) {
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++) {
		if (this->m_EmpArry[i]->m_Id == id) {
			//找到职工
			index = i;
			break;
		}
	}
	return index;
}
//修改职工
void WorkerManager::Mod_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件为空或记录为空！" << endl;
	}
	else {
		cout << "请输入修改职工的编号：" << endl;
		int id;
		cin >> id;
		int ret=this->IsExist(id);
		if (ret != -1) {
			delete this->m_EmpArry[ret];
			int newId = 0;
			string newName = "";
			int dSelect = 0;
			cout << "查到：" << id << "号职工，请输入新职工号:" << endl;
			cin >> newId;
			cout << "请输入新姓名：" << endl;
			cin >> newName;
			cout << "请输入新的岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;
			Worker* worker = NULL;
			switch (dSelect) {
			case 1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}
			this->m_EmpArry[ret] = worker;
			cout << "修改成功！" << endl;
			//保存文件
			this->save();
		}
		else {
			cout << "修改失败,查无此人！" << endl;
		}
		

	}
	system("pause");
	system("cls");
}
//查找职工
void WorkerManager::Find_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空！" << endl;
	}
	else {
		cout << "请输入查找的方式：" << endl;
		cout << "1.按照职工编号查找" << endl;
		cout << "2.按照职工姓名查找" << endl;
		int select = 0;
		cin >> select;
		if (select == 1) {
			int id;
			cout << "请输入查找的职工编号：" << endl;
			cin >> id;
			int ret = IsExist(id);
			if (ret != -1) {
				cout << "查找成功！该职工信息如下：" << endl;
				this->m_EmpArry[ret]->showInfo();
			}
			else {
				cout << "查找失败，查无此人！" << endl;
			}
		}
		else if(select==2){
			string name;
			cout << "请输入查找的姓名：" << endl;
			cin >> name;
			//判断是否查到
			bool flag = false;
			for (int i = 0; i < m_EmpNum; i++) {
				if (this->m_EmpArry[i]->m_Name == name) {
					cout << "查找成功，职工编号为：" << this->m_EmpArry[i]->m_Id << "号职工如下" << endl;
					flag = true;
					this->m_EmpArry[i]->showInfo();
				}

			}
			if (flag == false) {
				cout << "查找失败，查无此人！" << endl;
			}
		}
		else {
			cout << "输入选项有误！" << endl;
		}
		
	}
	system("pause");
	system("cls");
}
void WorkerManager::Sort_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空！" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "请选择排序方式：" << endl;
		cout << "1.按职工号进行升序" << endl;
		cout << "2.按职工号进行降序" << endl;
		int select = 0;
		cin >> select;
		for (int i = 0; i < m_EmpNum; i++) {
			int minOrMax = i;
			for(int j=i+1;j<this->m_EmpNum;j++)
			{
				if (select == 1) {
					if (this->m_EmpArry[minOrMax]->m_Id > this->m_EmpArry[j]->m_Id) {
						minOrMax = j;
					}
				}
				else {
					if (this->m_EmpArry[minOrMax]->m_Id <this->m_EmpArry[j]->m_Id) {
						minOrMax = j;
					}
				}
			}
			if (i != minOrMax) {
				Worker * temp = this->m_EmpArry[i];
				this->m_EmpArry[i] = this->m_EmpArry[minOrMax];
				this->m_EmpArry[minOrMax] = temp;
			}
		}
		cout << "排序 成功！排序后的结果为：" << endl;
		this->save();
		this->Show_Emp();
	}
}
void WorkerManager::Clean_File() {
	cout << "确定清空吗？" << endl;
	cout << "1、确定" << endl;
	cout << "2、返回" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		if (this->m_EmpArry != NULL) {
			//删除堆区的每个职工对象
			for (int i = 0; i < this->m_EmpNum; i++) {
				delete this->m_EmpArry[i];
				this->m_EmpArry[i] = NULL;
			}
			//删除堆区数组指针
			delete[] this->m_EmpArry;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}
WorkerManager::~WorkerManager() {
	if (this->m_EmpArry != NULL) {
		delete[] this->m_EmpArry;
		this->m_EmpArry = NULL;
	}
}