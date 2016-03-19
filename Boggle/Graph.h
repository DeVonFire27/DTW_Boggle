#pragma once
#include "DynArray.h"
#include "SLList.h"
#include <queue>
#include <iostream>
using namespace std;

template <typename Type>
class Graph
{
public:
	struct Edge
	{
		unsigned int toVertex;
	};

	struct Vertex
	{
		Type element;
		SLList<Edge> edges;

		///////////////////////////////////////////////////////////////////////////
		// Function : addEdge
		// Parameters : toVertex - the index of the vertex we are adjacent to
		///////////////////////////////////////////////////////////////////////////
		void addEdge(const unsigned int& toVertex)
		{
			Edge newEdge;
			newEdge.toVertex = toVertex;

			edges.addHead(newEdge);
		}

	};


private:
	DynArray<Vertex> vertices;

public:
	unsigned int addVertex(const Type& value);
	Vertex& operator[](const unsigned int& index);
	Vertex& operator[](const unsigned int& index) const;
	unsigned int size() const;
	void clear();
	void printBreadthFirst(const unsigned int& startVertex);
};

/////////////////////////////////////////////////////////////////////////////
// Function : addVertex
// Parameters : value - the data to store in this vertex
// Return : unsigned int - the index this vertex was added at
/////////////////////////////////////////////////////////////////////////////
template <typename Type>
unsigned int Graph<Type>::addVertex(const Type& value)
{
	Vertex temp;
	temp.element = value;
	vertices.append(temp);

	return vertices.size()-1;

}

/////////////////////////////////////////////////////////////////////////////
// Function : operator[]
// Parameters : index - the index in the graph to access
// Return : Vertex& - the vertex stored at the specified index
/////////////////////////////////////////////////////////////////////////////
template <typename Type>
typename Graph<Type>::Vertex& Graph<Type>::operator[](const unsigned int& index)
{
	return vertices[index];
}


/////////////////////////////////////////////////////////////////////////////
// Function : size
// Return : unsiged int - the number of vertices in the graph
/////////////////////////////////////////////////////////////////////////////
template <typename Type>
unsigned int Graph<Type>::size() const
{
	return vertices.size();
}

/////////////////////////////////////////////////////////////////////////////
// Function : clear
// Notes : clears the graph and readies it for re-use
/////////////////////////////////////////////////////////////////////////////
template <typename Type>
void Graph<Type>::clear()
{
	vertices.clear();
}

/////////////////////////////////////////////////////////////////////////////
// Function : printBreadthFirst
// Parameters : startVertex - the vertex to start the traversal at
// Notes : prints contents of the graph in depth order 
//			(from closest to farthest)
/////////////////////////////////////////////////////////////////////////////
template <typename Type>
void Graph<Type>::printBreadthFirst(const unsigned int& startVertex)
{
	queue<unsigned int> order;
	int * used = new int[vertices.size()];
	order.push(startVertex);
	int depth = 0;
	char run = 0;
	Type temp1;
	used[startVertex] = depth;

	for(unsigned int x = 0; x < vertices.size(); x++)
		if(x != startVertex)
			used[x] = -1;

	while(!order.empty())
	{
		auto temp2 = order.front();
		temp1 = vertices[temp2].element;
		order.pop();

		if(run != 0)
		{
			++depth;
			run = 0;
		}

		SLLIter<Edge> x(vertices[temp2].edges);
		for(x.begin();!x.end(); ++x)
		{

			if(used[x.current().toVertex] == -1)
			{
				order.push(x.current().toVertex);
				run = 1;
				used[x.current().toVertex] = depth+1;
			}


		}

	}

	unsigned int print = 0;

	while(print < vertices.size())
	{
		for(unsigned int x = 0; x < vertices.size(); x++)
			if(used[x] == print)
				cout << vertices[x].element << " : " << used[x] << '\n';
		print++;
	}

	delete [] used;
}
