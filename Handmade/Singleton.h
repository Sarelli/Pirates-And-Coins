/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : November 2015

  -----------------------------------------------------------------------------------------------

- This is a Singleton template class.

- It will instantiate another class of any type and allow access to it via the Instance() member 
  function.

- The constructor, copy constructor and assignment operator all need to be private so that this
  class cannot be individually instantiated.

*/

#ifndef SINGLETON_H
#define SINGLETON_H

template <class T>
class Singleton
{

public:

	static T* Instance();	

private:

	Singleton() {}
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);

};

//------------------------------------------------------------------------------------------------------
//template function that will create an instance of any type and return its address
//------------------------------------------------------------------------------------------------------
template <class T> T* Singleton<T>::Instance()
{

	//declare a pointer to the object and assign it NULL value
	//this will happen only once, ie - the first iteration of this function
	static T* s_singletonObject = 0;

	//check if pointer is NULL, and if it is, instantiate the object
	if (!s_singletonObject)
	{
		s_singletonObject = new T();
	}

	//alternatively just return the address
	return s_singletonObject;

}

#endif

