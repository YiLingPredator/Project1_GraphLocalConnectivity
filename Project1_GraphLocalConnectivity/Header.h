//
//  Header.h
//  Project1_GraphLocalConnectivity
//
//  Created by YI LING on 1/27/14.
//  Copyright (c) 2014 YI LING. All rights reserved.
//

#ifndef Project1_GraphLocalConnectivity_Header_h
#define Project1_GraphLocalConnectivity_Header_h
#endif

#include <iostream>
#include <cstdio>
#include <cmath>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "lp_lib.h"
#include <list>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <set>
#include <iterator>
#include <algorithm>
#include <fstream>

#define INI_NUM_NODES 30
#define X_RANGE 150
#define Y_RANGE 150
#define NEIGHBOR_RANGE 50 //能成为邻居的最大范围
#define SUCCESS  0
#define FAILURE -1
#define ALFA 0.7
#define GAMMA 2

using namespace std;


typedef struct _node
{
	double node_x;
	double node_y;
	
}node;

typedef struct _edge
{
	int pointA_id;
	int pointB_id;
	
}edge;

int NUM_NODES=0;
int V_length=0;
//Partition
vector<node> localvertice(INI_NUM_NODES);//node localvertice[NUM_NODES]={};//localgraph中的点坐标集合
vector<int>V_set;
vector<edge> Ev_set(((INI_NUM_NODES-1)*INI_NUM_NODES)/2);//edge Ev_set[((NUM_NODES+1)*NUM_NODES)/2]; //一个变量里存储了由两个端点表示的边，localgraph中的边（互为邻居的点有一条边）
vector<vector<double>>Eta;
vector<double>line_Eta;


vector<vector<bool>>adj;//bool adj[NUM_NODES][NUM_NODES];
vector<bool>line;
int Ev_length=0;
float lambda=0.85;
vector<int>Partition_result(INI_NUM_NODES);//int Partition_result[NUM_NODES]={0};
vector<int> x_(INI_NUM_NODES);
vector<int> x_i(INI_NUM_NODES);







//RelayNode
vector<edge>Ec(((INI_NUM_NODES+1)*INI_NUM_NODES)/2);//edge Ec[((NUM_NODES+1)*NUM_NODES)/2];
int Ec_length=0;
vector<int>W(INI_NUM_NODES);//int W[NUM_NODES]={};// A set
int W_length=0;
vector<int>Z(INI_NUM_NODES);//int Z[NUM_NODES]={};// A bar set
int Z_length=0;
vector<int>c(INI_NUM_NODES);//int c[NUM_NODES]={0};
vector<int>Relaynode_result(INI_NUM_NODES);//int Relaynode_result[NUM_NODES]={0};
vector<int> z_(INI_NUM_NODES);
vector<int> z_i(INI_NUM_NODES);







