#include <vector>
#include <queue>
#include <iostream>
#include "headers/gate.h"
#include "headers/and.h"

class OR: public Gate
{
	public:	
		bool * left;
		bool * right;
		OR(Gate * l, Gate * r)
		{
			inputs = 2;
			state = false;
			left = &(l->state);
			right = &(r->state);
			matrix[r->num][num] = true;
			matrix[l->num][num] = true;
		}
		void update()
		{
			state = (*left) | (*right);
		}
};

class XOR: public Gate
{
	public:
		bool * left;
		bool * right;
		XOR(Gate * l, Gate * r)
		{
			inputs = 2;
			state = false;
			left = &(l->state);
			right = &(r->state);
			matrix[r->num][num] = true;
			matrix[l->num][num] = true;
		}
		void update()
		{
			state = (*left) ^ (*right);
		}
};

class NOT: public Gate
{
	public:
		bool * input;
		NOT(Gate * g)
		{
			inputs = 1;
			state = false;
			input = &(g->state);
			matrix[g->num][num] = true;
		}
		void update()
		{
			state = !(*input);
		}
};

//I choose to make values gates because it makes my life more sane.
class ON: public Gate
{
	public:
		ON()
		{
			inputs = 0;
			state = true;
		}
		void update()
		{
			;
		}
};

class OFF: public Gate
{
	public:
		OFF()
		{
			inputs = 0;
			state = false;
		}
		void update()
		{
			;
		}
};

//The following function is written by the proceeding author

// Sean Szumlanski
// COP 3503, Fall 2013

vector <Gate *> topoSort()
{
	vector <Gate *> toRet;
	vector <int> incoming;
	incoming.resize(matrix.size());
	
	for(unsigned int i = 0; i < incoming.size(); ++i)
		incoming[i] = 0;
	
	int cnt = 0;

	// Count the number of incoming edges incident to each vertex. For sparse
	// graphs, this could be made more efficient by using an adjacency list.

	for(unsigned int i = 0; i < matrix.size(); ++i)
		for(unsigned int j = 0; j < matrix[i].size(); ++j)
			if(matrix[i][j])
				++incoming[j];

	queue <Gate *> q;

	// Any vertex with zero incoming edges is ready to be visited, so add it to
	// the queue.
	for (int i = 0; i < matrix.size(); i++)
		if (incoming[i] == 0)
			q.push(gates[i]);

	while (!q.empty())
	{
		// Pull a vertex out of the queue and add it to the topological sort.
		Gate * node = q.front();
		toRet.push_back(q.front());
		q.pop();

		// Count the number of unique vertices we see.
		++cnt;


		// All vertices we can reach via an edge from the current vertex should
		// have their incoming edge counts decremented. If one of these hits
		// zero, add it to the queue, as it's ready to be included in our
		// topological sort.
		for (int i = 0; i < matrix.size(); i++)
			if (matrix[node->num][i] && --incoming[i] == 0)
				q.push(gates[i]);
	}

	// If we pass out of the loop without including each vertex in our
	// topological sort, we must have a cycle in the graph.
	if (cnt != matrix.size())
		cout << "Error: Graph contains a cycle!" << endl;

	return toRet;
}

void init()
{
	//Read in each line of input

	//Initialize each gate per line

	//Example input line:
	//AND and3 : on1 on2
}

int main()
{
	ON term1;

	ON term2;

	XOR sum (&term1, &term2);
	
	AND carry (&term1, &term2);

	vector<Gate *> order = topoSort();

	for(Gate * g: order)
		g->update();
	
	cout << "Term1 is: " << term1.state << endl;
	cout << "Term2 is: " << term2.state << endl;
	cout << "Sum is: " << sum.state << endl;
	cout << "Carry is: " << carry.state << endl;

}