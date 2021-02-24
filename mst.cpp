#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <bits/stdc++.h>

using namespace std;

struct v{
	int x;
	int y;
	int key=INT_MAX;
	bool in=false;

};

int weight(struct v v0, struct v v1){
	float x= pow(v0.x-v1.x,2);
	float y= pow(v0.y-v1.y,2);
	float val= sqrt(x+y);

	return round(val);
}


void mst(vector<v> graph){
	int w=0;
	
	//setting up weight matrix
	graph[0].key=0;
	vector<vector<int>> weights; //establishing adjacency matrix
	for(int x=0;x<graph.size();x++){
		weights.push_back(vector<int>());
		
		for(int y=0;y<graph.size();y++)
			weights[x].push_back(weight(graph[x],graph[y]));
	}

	//prim's algorithm
	for(int c=0;c<graph.size()-1;c++){ // makes sure #edges is vertices-1
		int nxt, min=INT_MAX;
		
		for(int i=0;i<graph.size();i++){
			if(graph[i].in==false && graph[i].key<min){
				min= graph[i].key;
			 	nxt = i;
			}
		}
		graph[nxt].in=true; //declare as seen
		
		for(int i=0;i<graph.size();i++){//finding lowest value and inputting as key
			if(weights[nxt][i]<graph[i].key && graph[i].in==false)
				graph[i].key=weights[nxt][i];
		}

	}

	//add up all keys to get MST values
	for(int i=0;i<graph.size();i++){
		w+=graph[i].key;
		cout<<"Vertex "<<i<<" Key: "<<graph[i].key<<endl;
	}
	cout<<"MST Weight: "<<w<<endl;
}


int main(){
	ifstream g;
	g.open("graph.txt");

	if(!g)
		return 1;
	
 	int cases;
	g >> cases;

	for(int i=0; i<cases; i++){
		int vert;
		vector <v> graph;
		g >> vert;
		for(int x=0;x<vert;x++){
			int coords;
			struct v vtex;
			
			g >> coords;
			vtex.x=coords;
			g >> coords;
			vtex.y=coords;


			graph.push_back(vtex);
		}
		cout<<endl;

		cout<<"Test Case "<<i+1<<": "<<endl;
		mst(graph);
		cout<<endl;
	}
	g.close();
	
}
