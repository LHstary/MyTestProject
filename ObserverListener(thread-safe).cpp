#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<functional>
#include<iterator>
#include<algorithm>
#include<memory>
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
	void Register(int msgid,weak_ptr<Listen> listener)
	{
		map<int,vector<weak_ptr<Listen>>>::iterator it=_observerMap.find(msgid);
		if(it==_observerMap.end())
		{
			vector<weak_ptr<Listen>> tmpvec;
			tmpvec.push_back(listener);
			_observerMap[msgid]=tmpvec;
		}
		else
			it->second.push_back(listener);
	}
	void Dispath(int msgid)
	{
		map<int,vector<weak_ptr<Listen>>>::iterator it=_observerMap.find(msgid);
		if(it==_observerMap.end())
			return ;
		
		vector<weak_ptr<Listen>>::iterator vit=it->second.begin();
		for(;vit!=it->second.end();++vit)
		{
			shared_ptr<Listen> p=(*vit).lock();
			if(p!=NULL)
				p->Handlemsg(msgid);
		}
			//(*vit)->Handlemsg(msgid);
	}
private:
	map<int,vector<weak_ptr<Listen>>> _observerMap;
};
int main()
{
	Observe ob;

	//pthread1
	/*Listen *p1= Listen1("listener1");
	Listen *p2=new Listen2("listener2");
	Listen *p3=new Listen3("listener3");*/

	shared_ptr<Listen> p1(new Listen1("listener1"));
	shared_ptr<Listen> p2(new Listen1("listener2"));
	shared_ptr<Listen> p3(new Listen1("listener3"));
	
	ob.Register(1,p1);
	ob.Register(2,p1);
	ob.Register(3,p1);
	ob.Register(1,p2);
	ob.Register(3,p2);
	ob.Register(3,p3);

	//pthread2
	int msgid;
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

