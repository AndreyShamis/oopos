#pragma once
#include "macros.h"
#include "Iterators.h"
#include "Graph.h"

template <class T> 
class GraphIterator : public Iterators<T>
{
public:
	GraphIterator(Graph<T> *someGraph)
	{
		_someGraph = someGraph;
		_insideVector = _someGraph->getVectorOfIds();
		_position=0;
	}
	//const T* 
	void operator++(int)
	{
		_position++;
		//return(*this);
		//*this = ;
		//return(_someGraph->getData(_insideVector[_position-1]));
	}

	const T* getCurent()
	{
		return(_someGraph->getData(_insideVector[_position]));
	}

	bool end()
	{
		if((int)_insideVector.size() <= _position)
			return(false);

		return(true);
	}

	GraphIterator &operator=(const GraphIterator &Other)
	{
		_position = Other._position;

		return(*this);
	}



//	~GraphIterator();

private:

	std::vector<int> _insideVector;
	int _position;
	Graph<T> *_someGraph;
};





//template <class T> 
//GraphIterator::GraphIterator(Graph<T> *someGraph)
//{
//	_insideVector = someGraph->getVectorOfIds();
//}

//
//template <class T> 
//GraphIterator::~GraphIterator()
//{
//
//}
