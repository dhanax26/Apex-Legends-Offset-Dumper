#pragma once

// credits: sodium_bromate

template <class T> class singleton
{
public:

	static T* instance( )
	{
		if ( !ob_instance )
			ob_instance = new T( );

		return ob_instance;
	}

	virtual ~singleton( )
	{
		ob_instance = nullptr;
	}

private:
	inline static T* ob_instance = nullptr;

protected:
	singleton( ) = default;
};

//template <class T> T* singleton<T>::ob_instance = nullptr;