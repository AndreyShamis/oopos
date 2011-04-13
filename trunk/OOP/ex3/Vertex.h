/*

//  @ Project : Lights = EX3
//  @ File Name : Vertex.cpp
//  @ Authors : Ilia Gaysinski and Andrey Shamis
//	@ Description :		Class of Vertex

	This class provide vertex used in graph store for game lights.
	For more information see functions desctiptions

	Have only one constructor wich get cordinates x and y
	size of potential vector of neighbors and minimal distance between
	two neighbors.


*/
#pragma once
#include "macros.h"
#include <vector>

//=============================================================================
class Vertex 
{
public:
	bool operator==(const Vertex &other) const;
	Vertex(const float X, const float Y,
		const int EdgesSize,const float dist);
	void	SetID(const int val);
	void	Draw();
	int		GetID()const;
	float	getX()const;
	float	getY()const;
	void	Shift();
	void	ChangeEdge(const int place);
	void	LightOFF();
	void	LightON();
	void	setFather(const int value);
	const	std::vector<bool> getFutEdg()const;

private:
	float			_x;
	float			_y;
	bool			_lighted;
	int				_id;
	float			_dist;
	static  float	rads;
	int				_father;
	int				MAX_VEC_SIZE;
	std::vector<bool> _future_edge;

};
