#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<functional>
#include<iterator>
#include<algorithm>
using namespace std;

class Listen
{
public:
	Listen(string name):_name(name){}
	virtual void Handlemsg(int msgid)=0;
protected:
	string _name;
};

class Listen1:public Listen
{
public:
	Listen1(string name):Listen(name){}
	void Handlemsg(int msgid)
	{
		cout<<_name<<"   recive:" ;
		switch(msgid)
		{
			case 1:
				cout<<"1 msg"<<endl;
				break;
			case 2:
				cout<<"2 msg"<<endl;
				break;
			case 3:
				cout<<"3 msg"<<endl;
				break;
			default:
				break;
		}
	}
};

class Listen2:public Listen
{
public:
	Listen2(string name):Listen(name){}
	void Handlemsg(int msgid)
	{
		cout<<_name<<"   recive:" ;

		switch(msgid)
		{
			case 1:
				cout<<"1 msg"<<endl;
				break;
			case 3:
				cout<<"3 msg"<<endl;
				break;
			default:
				break;
		}
	}

};

class Listen3:public Listen
{
public:
	Listen3(string name):Listen(name){}
	void Handlemsg(int msgid)
	{
		cout<<_name<<"   recive:";
		switch(msgid)
		{
			case 3:
				cout<<"3 msg"<<endl;
				break;
			default:
				break;
		}
	}
};

class Observe
{
public:
	void Register(int msgid,Listen* listener)
	{
		map<int,vector<Listen*>>::iterator it=_observerMap.find(msgid);
		if(it==_observerMap.end())
		{
			vector<Listen*> tmpvec;
			tmpvec.push_back(listener);
			_observerMap[msgid]=tmpvec;
		}
		else
			it->second.push_back(listener);
	}
	void Dispath(int msgid)
	{
		map<int,vector<Listen*>>::iterator it=_observerMap.find(msgid);
		if(it==_observerMap.end())
			return ;
		
		vector<Listen*>::iterator vit=it->second.begin();
		for(;vit!=it->second.end();++vit)
			(*vit)->Handlemsg(msgid);
	}
private:
	map<int,vector<Listen*>> _observerMap;
};
int main()
{
	Observe ob;

	Listen *p1=new Listen1("listener1");
	Listen *p2=new Listen2("listener2");
	Listen *p3=new Listen3("listener3");
	
	int msgid;
	ob.Register(1,p1);
	ob.Register(2,p1);
	ob.Register(3,p1);
	ob.Register(1,p2);
	ob.Register(3,p2);
	ob.Register(3,p3);

	while(true)
	{
		cout<<"**************************"<<endl;
		cout<<"input msgID:"<<endl;
		
		cin>>msgid;
		
		if(msgid==-1)
			break;
		
		ob.Dispath(msgid);
	}
	
	return 0;
}
