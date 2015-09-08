//SingletonCRTP.h
/*More C++ Idioms/Curiously Recurring Template Pattern
ref. https://en.wikibooks.org/

ex. 14.2 Modify the xlw factory so it uses the Singleton class developed here

*/

#ifndef SINGLETON_CRTP_H
#define SINGLETON_CRTP_H

class noncopyable
{
protected:
noncopyable(){}
~noncopyable(){}

private: // emphasize the following members are private
noncopyable( const noncopyable& );
const noncopyable& operator=( const noncopyable& );

};

template<class T>
class Singleton : private noncopyable
{
public:
	static T& Instance(){
		static T one;
		return one;
	}

protected:
	Singleton(){}
};

#endif