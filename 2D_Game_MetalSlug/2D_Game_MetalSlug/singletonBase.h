#pragma once

//싱글톤 ->중요함. 반드시 알아야 할것. 공부해라.ㅋ
/*
	싱들톤 패턴은 스태틱 멤버로 하나의 인스턴스만 생성됨.
	프로그램 안에서 전역적으로 접근이 되며, 보통 클래스의 인스턴스를 하나만 유지하고자
	할때 사용함.

	전역변수를 이용해도 하나의 인스턴스를 유지할수 있지만 싱글톤 패턴을 사용하면
	클래스 자신이 자기의 유일한 인스턴스로 접근하는 방법을 캡슐화 하여 관리 할수 있음.
	상속, 객체 생성, 객체 소멸, 인스턴스의 개수 제어등등 활용에 용이함.

	더 좋은 방법은 자기 스스로가 자기의 유일한 인스턴스로 접근하는 방법을 자체적으로 관리하는 방법임.
	이 싱글톤 베이스는 다른 인스턴스가 생성되지 않도록 처리할수 있고 접근 방법또한 제한을 둘수 있음.

*/
template <typename T>
class singletonBase
{
protected:
	//싱글톤 인스턴스 선언
	static T* singleton;

	singletonBase() {};
	~singletonBase() {};

public:
	//싱글톤 객체 가져오기
	static T* getSingleton();
	void releaseSingleton();
};
//싱글톤 인스턴스선언
template <typename T>
T* singletonBase<T>::singleton = nullptr;

//싱글톤 객체 가져오기
template <typename T>
T* singletonBase<T>::getSingleton()
{//싱글톤 객체가 없으면 새로 만들자
	if ( !singleton )singleton = new T;

	return singleton;
}
template <typename T>
void singletonBase<T>::releaseSingleton()
{
	//싱글톤 객체가 있다면 메모리에서 해제하자.
	if ( singleton )
	{
		delete singleton;
		singleton = nullptr;
	}
}
