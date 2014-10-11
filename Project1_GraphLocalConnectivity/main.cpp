//
//  main.cpp
//  Project1_GraphLocalConnectivity
//
//  Created by YI LING on 1/27/14.
//  Copyright (c) 2014 YI LING. All rights reserved.
//

#include <iostream>
#include "Header.h"
#include <string>
#include <string.h>
#include <sstream>

using namespace std;
//innitial

void getlocalvertice(){
    //    srand((unsigned)time(0));
    //    for (int i=0; i<NUM_NODES; i++)// getVertice 获得在G中的NUM_NODES个点
    //    {
    //        localvertice[i].node_x=rand()/(RAND_MAX+1.0)*X_RANGE;
    //        localvertice[i].node_y=rand()/(RAND_MAX+1.0)*Y_RANGE;
    //    }
    //    for (int i=0; i<NUM_NODES; i++) {
    //        cout<<i<<": x="<<localvertice[i].node_x<<",y="<<localvertice[i].node_y<<endl;
    //    }
    
    ifstream input;
    char str[100];
    int i=0;
    char *pch;
    input.open("NodePosition30.txt");
    if (input.fail()) {
        cout<<"File does not exit";
    }
    while (!input.eof()&& i<30) {
        input.getline(str, 100);
        pch=strtok(str, " ");
        localvertice[i].node_x=atof(pch);
        pch=strtok(NULL, " ");
        localvertice[i].node_y=atof(pch);
        i++;
    }
    input.close();
}
void getEv(){
    for (int i=0; i<NUM_NODES; i++) {
        for (int j=i+1; j<NUM_NODES; j++) {
            double dis= sqrt(pow(localvertice[i].node_x-localvertice[j].node_x,2)+pow(localvertice[i].node_y-localvertice[j].node_y,2));
            if (dis<=NEIGHBOR_RANGE+0.01) {
                Ev_set[Ev_length].pointA_id=i;
                Ev_set[Ev_length].pointB_id=j;
                Ev_length++;
                adj[i][j]=true;
                adj[j][i]=true;
                Eta[i][j]=1;
                Eta[j][i]=1;
            }
            else{
//                Ev_set[Ev_length].pointA_id=i;
//                Ev_set[Ev_length].pointB_id=j;
//                Ev_length++;
//                adj[i][j]=true;
//                adj[j][i]=true;
//                Eta[i][j]=pow((dis/NEIGHBOR_RANGE),-GAMMA);
//                Eta[j][i]=pow((dis/NEIGHBOR_RANGE),-GAMMA);
            }
        }
    }
    //topology:
    //    cout<<" 互为邻居的两个点"<<endl;
    //    for (int i=0; i<Ev_length; i++) {
    //        cout<<Ev_set[i].pointA_id<<"-"<<Ev_set[i].pointB_id<<endl;
    //    }
    
    // 互为邻居的两个点写入edgeFile.txt
        ofstream output;
        output.open("edgeFile.txt");
        for (int i=0; i<Ev_length; i++) {
            output<<Ev_set[i].pointA_id<<"-"<<Ev_set[i].pointB_id<<endl;
        }
        output.close();
    
}
void transmission(){
    for(int k=0;k<NUM_NODES;k++)
    {
        for( int i=0;i<NUM_NODES;i++)
        {
            if (i!=k)
            {
                for(int j=0;j<NUM_NODES;j++)
                {
                    if(i !=j && j!= k)
                    {
                        if(adj[i][j]!= true  )
                        {
                            adj[i][j] = adj[i][k]&adj[k][j];
                        }
                    }
                }
            }
        }
    }
}
bool Check_Connected(){
    for(int i = 0; i<NUM_NODES; i++)
    {
        for(int j = 0; j<NUM_NODES; j++)
        {
            if(i!=j)
            {
                if(adj[i][j]!= true)
                {
                    return FALSE;
                }
            }
        }
    }
    return TRUE;
}
void getLocalGraph(){
    NUM_NODES=INI_NUM_NODES;
    V_length=INI_NUM_NODES;
    cout<<"默认：G图规格是"<<X_RANGE<<"*"<<Y_RANGE<<",其中有"<<NUM_NODES<<"个任意点"<<std::endl;
    cout<<"默认：能够成为邻居的最大距离"<<NEIGHBOR_RANGE<<std::endl;
    for (int i=0; i<NUM_NODES; i++) {
        V_set.push_back(1);
    }
    for (int i=0; i<NUM_NODES; i++) {
        adj.push_back(line);
        for (int j=0; j<NUM_NODES; j++) {
            adj[i].push_back(false);
        }
    }
    for (int i=0; i<NUM_NODES; i++) {
        Eta.push_back(line_Eta);
        for (int j=0; j<NUM_NODES; j++) {
            Eta[i].push_back(0);
        }
    }
    getlocalvertice();
    getEv();
    //transmission();
    cout<<"G图中"<<NUM_NODES<<"个点的坐标"<<endl;
}
//Partition
void Generate_LC_File_Partition(){
    ofstream sout;
    char outputfileName[20];
    sprintf(outputfileName, "LC.lp");
    sout.open(outputfileName);
    if (sout.fail())
    {
        std::cout<<"打开文件错误!"<<std::endl;
    }
    sout<<"min: ";
    //cout<<"min: ";
    // (1)the object function sumq_i_j-lambda*sumx_i+lambda*|V|/2
    for (int l=0; l<Ev_length; l++) {
        int i=Ev_set[l].pointA_id;
        int j=Ev_set[l].pointB_id;
        sout<<"+"<<"q_"<<i<<"_"<<j;
        //cout<<"+"<<"q_"<<i<<"_"<<j;
    }
    for (int l=0; l<NUM_NODES; l++) {
        //if (V_set[l]==1) {
        sout<<"-"<<lambda<<"*"<<"x_"<<l;
        //cout<<"-"<<lambda<<"*"<<"x_"<<l;
        //}
    }
    double temp22=lambda*V_length/2;
    sout<<"+"<<temp22<<";"<<endl;
    //cout<<"+"<<lambda*V_length/2<<";"<<endl;
    //    //(2)the object function sumq_i_j+lambda*sumx_i-lambda*|v|/2
    //    for (int l=0; l<Ev_length; l++) {
    //        int i=Ev_set[l].pointA_id;
    //        int j=Ev_set[l].pointB_id;
    //        sout<<"+"<<"q_"<<i<<"_"<<j;
    //        cout<<"+"<<"q_"<<i<<"_"<<j;
    //    }
    //    for (int l=0; l<NUM_NODES; l++) {
    //        if (V_set[l]==1) {
    //            sout<<"+"<<lambda<<"*"<<"x_"<<l;
    //            cout<<"+"<<lambda<<"*"<<"x_"<<l;
    //        }
    //    }
    //    sout<<"-"<<lambda*V_length/2<<";"<<endl;
    //    cout<<"-"<<lambda*V_length/2<<";"<<endl;
    
    // subject to: q_i_j>=x_i-x_j;
    for (int l=0; l<Ev_length; l++) {
        int i=Ev_set[l].pointA_id;
        int j=Ev_set[l].pointB_id;
        sout<<"q_"<<i<<"_"<<j<<">="<<"x_"<<i<<"-"<<"x_"<<j<<";"<<endl;
        //cout<<"q_"<<i<<"_"<<j<<">="<<"x_"<<i<<"-"<<"x_"<<j<<";"<<endl;
        
    }
    // subject to: q_i_j>=x_j-x_i;
    for (int l=0; l<Ev_length; l++) {
        int i=Ev_set[l].pointA_id;
        int j=Ev_set[l].pointB_id;
        sout<<"q_"<<i<<"_"<<j<<">="<<"x_"<<j<<"-"<<"x_"<<i<<";"<<endl;
        //cout<<"q_"<<i<<"_"<<j<<">="<<"x_"<<j<<"-"<<"x_"<<i<<";"<<endl;
    }
    // subject to: q_i_j<=x_i+x_j;
    for (int l=0; l<Ev_length; l++) {
        int i=Ev_set[l].pointA_id;
        int j=Ev_set[l].pointB_id;
        sout<<"q_"<<i<<"_"<<j<<"<="<<"x_"<<i<<"+"<<"x_"<<j<<";"<<endl;
        //cout<<"q_"<<i<<"_"<<j<<"<="<<"x_"<<i<<"+"<<"x_"<<j<<";"<<endl;
    }
    // subject to: q_i_j<=2-x_i-x_j;
    for (int l=0; l<Ev_length; l++) {
        int i=Ev_set[l].pointA_id;
        int j=Ev_set[l].pointB_id;
        sout<<"q_"<<i<<"_"<<j<<"<="<<"2-"<<"x_"<<i<<"-"<<"x_"<<j<<";"<<endl;
        //cout<<"q_"<<i<<"_"<<j<<"<="<<"2-"<<"x_"<<i<<"-"<<"x_"<<j<<";"<<endl;
    }
    //(1)subject to:sumx_i>0
    for (int l=0; l<NUM_NODES; l++) {
        //if (V_set[l]==1) {
        sout<<"+"<<"x_"<<l;
        //cout<<"+"<<"x_"<<l;
        //}
    }
    sout<<">0;"<<endl;
    //cout<<">=0;"<<endl;
    //subject to:sumx_i<=|V|/2
    for (int l=0; l<NUM_NODES; l++) {
        if (V_set[l]==1) {
            sout<<"+"<<"x_"<<l;
            //cout<<"+"<<"x_"<<l;
        }
    }
    sout<<"<="<<V_length/2<<";"<<endl;
    //cout<<"<="<<V_length/2<<";"<<endl;
    
    //    //(2)subect to sumx_i>=|v|/2
    //    for (int l=0; l<NUM_NODES; l++) {
    //        if (V_set[l]==1) {
    //            sout<<"+"<<"x_"<<l;
    //            cout<<"+"<<"x_"<<l;
    //        }
    //    }
    //    sout<<">="<<V_length/2<<";"<<endl;
    //    cout<<">="<<V_length/2<<";"<<endl;
    //    //subject to sumx_i<=|V|
    //    for (int l=0; l<NUM_NODES; l++) {
    //        if (V_set[l]==1) {
    //            sout<<"+"<<"x_"<<l;
    //            cout<<"+"<<"x_"<<l;
    //        }
    //    }
    //    sout<<"<"<<V_length<<";"<<endl;
    //    cout<<"<"<<V_length<<";"<<endl;
    
    //print all the variables
    //0<=q_i_j<=1
    for (int l=0; l<Ev_length; l++) {
        int i=Ev_set[l].pointA_id;
        int j=Ev_set[l].pointB_id;
        sout<<"0"<<"<="<<"q_"<<i<<"_"<<j<<"<="<<"1"<<";"<<endl;
        //cout<<"0"<<"<="<<"q_"<<i<<"_"<<j<<"<="<<"1"<<";"<<endl;
    }
    //0<=x_i<=1
    for (int l=0; l<NUM_NODES; l++) {
        if (V_set[l]==1) {
            sout<<"0"<<"<="<<"x_"<<l<<"<="<<"1"<<";"<<endl;
            //cout<<"0"<<"<="<<"x_"<<l<<"<="<<"1"<<";"<<endl;
        }
    }
    //print int variables
    sout<<"int X_0_0_0";
    //cout<<"int X_0_0_0";
    for (int l=0; l<Ev_length; l++) {
        int i=Ev_set[l].pointA_id;
        int j=Ev_set[l].pointB_id;
        sout<<","<<"q_"<<i<<"_"<<j;
        //cout<<","<<"q_"<<i<<"_"<<j;
        
    }
    for (int l=0; l<NUM_NODES; l++) {
        if (V_set[l]==1) {
            sout<<","<<"x_"<<l;
            //cout<<","<<"x_"<<l;
        }
    }
    sout<<";"<<std::endl;
    //cout<<";"<<std::endl;
    sout.close();
}
/*void Generate_LC_File_Partition_Eta(){
    ofstream sout;
    char outputfileName[20];
    sprintf(outputfileName, "LC.lp");
    sout.open(outputfileName);
    if (sout.fail())
    {
        std::cout<<"打开文件错误!"<<std::endl;
    }
    sout<<"min: ";
    //cout<<"min: ";
    // (1)the object function sum(Eta_i_j*q_i_j)-lambda*sumx_i+lambda*|V|/2
    for (int l=0; l<Ev_length; l++) {
        int i=Ev_set[l].pointA_id;
        int j=Ev_set[l].pointB_id;
        sout<<"+"<<Eta[i][j]<<"*"<<"q_"<<i<<"_"<<j;
        //cout<<"+"<<"q_"<<i<<"_"<<j<<"*"<<Eta[i][j];
    }
    for (int l=0; l<NUM_NODES; l++) {
        //if (V_set[l]==1) {
        sout<<"-"<<lambda<<"*"<<"x_"<<l;
        //cout<<"-"<<lambda<<"*"<<"x_"<<l;
        //}
    }
    double temp22=lambda*V_length/2;
    sout<<"+"<<temp22<<";"<<endl;
    //cout<<"+"<<lambda*V_length/2<<";"<<endl;
    //    //(2)the object function sumq_i_j+lambda*sumx_i-lambda*|v|/2
    //    for (int l=0; l<Ev_length; l++) {
    //        int i=Ev_set[l].pointA_id;
    //        int j=Ev_set[l].pointB_id;
    //        sout<<"+"<<"q_"<<i<<"_"<<j;
    //        cout<<"+"<<"q_"<<i<<"_"<<j;
    //    }
    //    for (int l=0; l<NUM_NODES; l++) {
    //        if (V_set[l]==1) {
    //            sout<<"+"<<lambda<<"*"<<"x_"<<l;
    //            cout<<"+"<<lambda<<"*"<<"x_"<<l;
    //        }
    //    }
    //    sout<<"-"<<lambda*V_length/2<<";"<<endl;
    //    cout<<"-"<<lambda*V_length/2<<";"<<endl;
    
    // subject to: q_i_j>=x_i-x_j;
    for (int l=0; l<Ev_length; l++) {
        int i=Ev_set[l].pointA_id;
        int j=Ev_set[l].pointB_id;
        sout<<"q_"<<i<<"_"<<j<<">="<<"x_"<<i<<"-"<<"x_"<<j<<";"<<endl;
        //cout<<"q_"<<i<<"_"<<j<<">="<<"x_"<<i<<"-"<<"x_"<<j<<";"<<endl;
        
    }
    // subject to: q_i_j>=x_j-x_i;
    for (int l=0; l<Ev_length; l++) {
        int i=Ev_set[l].pointA_id;
        int j=Ev_set[l].pointB_id;
        sout<<"q_"<<i<<"_"<<j<<">="<<"x_"<<j<<"-"<<"x_"<<i<<";"<<endl;
        //cout<<"q_"<<i<<"_"<<j<<">="<<"x_"<<j<<"-"<<"x_"<<i<<";"<<endl;
    }
    // subject to: q_i_j<=x_i+x_j;
    for (int l=0; l<Ev_length; l++) {
        int i=Ev_set[l].pointA_id;
        int j=Ev_set[l].pointB_id;
        sout<<"q_"<<i<<"_"<<j<<"<="<<"x_"<<i<<"+"<<"x_"<<j<<";"<<endl;
        //cout<<"q_"<<i<<"_"<<j<<"<="<<"x_"<<i<<"+"<<"x_"<<j<<";"<<endl;
    }
    // subject to: q_i_j<=2-x_i-x_j;
    for (int l=0; l<Ev_length; l++) {
        int i=Ev_set[l].pointA_id;
        int j=Ev_set[l].pointB_id;
        sout<<"q_"<<i<<"_"<<j<<"<="<<"2-"<<"x_"<<i<<"-"<<"x_"<<j<<";"<<endl;
        //cout<<"q_"<<i<<"_"<<j<<"<="<<"2-"<<"x_"<<i<<"-"<<"x_"<<j<<";"<<endl;
    }
    //(1)subject to:sumx_i>=|v|/3
    for (int l=0; l<NUM_NODES; l++) {
        //if (V_set[l]==1) {
        sout<<"+"<<"x_"<<l;
        //cout<<"+"<<"x_"<<l;
        //}
    }
    sout<<">="<<V_length/3<<";"<<endl;
    //cout<<">=0;"<<endl;
    //subject to:sumx_i<=|V|/2
    for (int l=0; l<NUM_NODES; l++) {
        if (V_set[l]==1) {
            sout<<"+"<<"x_"<<l;
            //cout<<"+"<<"x_"<<l;
        }
    }
    sout<<"<="<<V_length/2<<";"<<endl;
    //cout<<"<="<<V_length/2<<";"<<endl;
    
    //    //(2)subect to sumx_i>=|v|/2
    //    for (int l=0; l<NUM_NODES; l++) {
    //        if (V_set[l]==1) {
    //            sout<<"+"<<"x_"<<l;
    //            cout<<"+"<<"x_"<<l;
    //        }
    //    }
    //    sout<<">="<<V_length/2<<";"<<endl;
    //    cout<<">="<<V_length/2<<";"<<endl;
    //    //subject to sumx_i<=|V|
    //    for (int l=0; l<NUM_NODES; l++) {
    //        if (V_set[l]==1) {
    //            sout<<"+"<<"x_"<<l;
    //            cout<<"+"<<"x_"<<l;
    //        }
    //    }
    //    sout<<"<"<<V_length<<";"<<endl;
    //    cout<<"<"<<V_length<<";"<<endl;
    
    //print all the variables
    //0<=q_i_j<=1
    for (int l=0; l<Ev_length; l++) {
        int i=Ev_set[l].pointA_id;
        int j=Ev_set[l].pointB_id;
        sout<<"0"<<"<="<<"q_"<<i<<"_"<<j<<"<="<<"1"<<";"<<endl;
        //cout<<"0"<<"<="<<"q_"<<i<<"_"<<j<<"<="<<"1"<<";"<<endl;
    }
    //0<=x_i<=1
    for (int l=0; l<NUM_NODES; l++) {
        if (V_set[l]==1) {
            sout<<"0"<<"<="<<"x_"<<l<<"<="<<"1"<<";"<<endl;
            //cout<<"0"<<"<="<<"x_"<<l<<"<="<<"1"<<";"<<endl;
        }
    }
    //print int variables
    sout<<"int X_0_0_0";
    //cout<<"int X_0_0_0";
    for (int l=0; l<Ev_length; l++) {
        int i=Ev_set[l].pointA_id;
        int j=Ev_set[l].pointB_id;
        sout<<","<<"q_"<<i<<"_"<<j;
        //cout<<","<<"q_"<<i<<"_"<<j;
        
    }
    for (int l=0; l<NUM_NODES; l++) {
        if (V_set[l]==1) {
            sout<<","<<"x_"<<l;
            //cout<<","<<"x_"<<l;
        }
    }
    sout<<";"<<std::endl;
    //cout<<";"<<std::endl;
    sout.close();
}*/
void Read_Partition_File(char* filename){
    char line[100];
    int i = 0;
    int n=0;
    int b=0;
    int number1 = -1;//x_i的i
    int number2 =-1;//x_i的值
    int x_i_length = 0;
    
    FILE *file = fopen ( filename, "r" );
    
    while ( fgets ( line, sizeof line, file ) != NULL )
    {
        i=0;
        while (line[i]!='\0')
        {
            // 获取x_i
            if (line[i] == 'x' && line[i+1] == '_')
            {
                char temp1[10];//装x_i的i
                char temp2[10];//装x_i的值
                b=0;
                memset(temp1,0,sizeof(temp1));
                while(!isdigit(line[i])) i++;
                while(isdigit(line[i]))
                {
                    temp1[b++] = line[i];
                    i++;
                }
                temp1[b] = '\0';
                number1 = -1;
                number1 = atoi(temp1);
                
                while(!isdigit(line[i])) i++;
                n=0;
                memset(temp2,0,sizeof(temp2));
                while(isdigit(line[i]))
                {
                    temp2[n++] = line[i];
                    i++;
                }
                temp2[n] = '\0';
                number2 = -1;
                number2 = atoi(temp2);
                
                if (number1 !=-1 && number2!=-1)
                {
                    x_[x_i_length]=number1;
                    x_i[x_i_length]=number2;
                    x_i_length++;
                }
                break;
                
            }
            else break;
        }
    }
    for (int i=0; i<x_i_length; i++) {
        Partition_result[i]=x_i[i];
        
    }
    cout<<"Partition结果："<<endl;
    for (int i=0; i<Partition_result.size(); i++) {
        if (Partition_result[i]==1) {
            cout<<","<<i+1;
        }
    }
    cout<<endl;
    
}
int Partition(){
    
    char file_name[15] = "LC.lp";
    char test_model[15] = "test_model";
    char output_log[15] = "LC.txt";
    lprec *lp;
    ofstream sOut;
    ifstream sin;
    //Generate_LC_File_Partition_Eta();
    Generate_LC_File_Partition();
    lp = read_LP(file_name, NORMAL, test_model);
    if(lp == NULL){
        cout<< "Unable to read model\n";
        return FAILURE;
    }
    set_outputfile(lp, output_log);
    solve(lp);
    print_objective(lp);
    print_solution(lp, 1);
    Read_Partition_File(output_log);
    delete_lp(lp);//关闭 很重要
    return SUCCESS;
}

//Relaynode
void getEc(){
    for (int i=0; i<NUM_NODES; i++)
    {
        for (int j=i+1; j<NUM_NODES; j++) {
            double dis= sqrt(pow(localvertice[i].node_x-localvertice[j].node_x,2)+pow(localvertice[i].node_y-localvertice[j].node_y,2));
            if (dis>2*NEIGHBOR_RANGE) {
                Ec[Ec_length].pointA_id = i;
                Ec[Ec_length].pointB_id = j;
                Ec_length++;
            }
        }
    }
}
void getAset(){
    //    for (int i=0; i<NUM_NODES; i++) {
    //        if (Partition_result[i]==1) {
    //            W[W_length]=i;
    //            W_length++;
    //        }
    //    }
    W={0,1,4,6,9,11,12,13,15,18,21,23,25,26,28};
    W_length=15;
    
}
void getAbarset(){
    //    for (int i=0; i<NUM_NODES; i++) {
    //        if (Partition_result[i]!=1) {
    //            Z[Z_length]=i;
    //            Z_length++;
    //        }
    //    }
    Z={2,3,5,7,8,10,14,16,17,19,20,22,24,27,29};
    Z_length=15;
    
}
void getCset(){
    //example random 20 vertices radius=50
    ifstream input;
    input.open("CI.txt");
    char ci[100];
    if (input.fail()) {
        cout<<"Can not open the file"<<endl;
    }
    while (!input.eof()) {
        input.getline(ci, 100,'\n');
        c.push_back(atoi(ci));
    }
    
}
void Generate_LC_File_RelayNode_zi(){
    ofstream sout;
    char outputfileName[20];
    sprintf(outputfileName, "LC_RelayNode.lp");
    sout.open(outputfileName);
    if (sout.fail())
    {
        std::cout<<"打开文件错误!"<<std::endl;
    }
    sout<<"max: "<<endl;
    //cout<<"max: "<<endl;
    // the object function: sumz_i
    for (int i=0; i<NUM_NODES; i++) {
        sout<<"+"<<"z_"<<i;
        //cout<<"+"<<"z_"<<i;
    }
    sout<<";"<<endl;
    //cout<<";"<<endl;
    // subject to: z_i+z_j<=1
    for (int l=0; l<Ec_length; l++) {
        int i=Ec[l].pointA_id;
        int j=Ec[l].pointB_id;
        sout<<"z_"<<i<<"+"<<"z_"<<j<<"<="<<"1"<<";"<<endl;
        //cout<<"z_"<<i<<"+"<<"z_"<<j<<"<="<<"1"<<";"<<endl;
        
    }
    // subject to: sumz_i>=alfa*z_j
    for (int l=0; l<W_length; l++) {
        int i=l;
        sout<<"+"<<"z_"<<W[i];
        //cout<<"+"<<"z_"<<W[i];
    }
    sout<<">="<<ALFA<<"*"<<"z_"<<Z[0];
    //cout<<">="<<ALFA<<"*"<<"z_"<<Z[0];
    for (int l=1;l<Z_length ; l++) {
        int j=l;
        sout<<"+"<<ALFA<<"*"<<"z_"<<Z[j];
        //cout<<"+"<<ALFA<<"*"<<"z_"<<Z[j];
    }
    sout<<";"<<endl;
    //cout<<";"<<endl;
    // subject to: sumz_j>=alfa*z_i
    for (int l=0; l<Z_length; l++) {
        int i=l;
        sout<<"+"<<"z_"<<Z[i];
        //cout<<"+"<<"z_"<<Z[i];
    }
    sout<<">="<<ALFA<<"*"<<"z_"<<W[0];
    //cout<<">="<<ALFA<<"*"<<"z_"<<W[0];
    for (int l=1;l<W_length; l++) {
        int j=l;
        sout<<"+"<<ALFA<<"*"<<"z_"<<W[j];
        //cout<<"+"<<ALFA<<"*"<<"z_"<<W[j];
    }
    sout<<";"<<endl;
    //cout<<";"<<endl;
    // subject to: z_i+sumz_j<=c_i
    int i_flag=0;
    for (int l=0; l<NUM_NODES; l++) {
        i_flag=l;
        sout<<"z_"<<i_flag;
        //cout<<"z_"<<i_flag;
        for (int l=0; l<NUM_NODES; l++) {
            if (l==i_flag) {
                if (l==NUM_NODES-1) {
                    break;
                }
                l++;
            }
            sout<<"+"<<"z_"<<l;
            //cout<<"+"<<"z_"<<l;
        }
        
        sout<<"<="<<c[i_flag]+NUM_NODES<<"-"<<NUM_NODES<<"*"<<"z_"<<i_flag<<";"<<endl;
        //cout<<"<="<<c[i_flag]<<";"<<endl;
    }
    //print all the variables
    //0<=z_i<=1
    for (int l=0; l<NUM_NODES; l++) {
        int i=l;
        sout<<"0"<<"<="<<"z_"<<i<<"<="<<"1"<<";"<<endl;
        //cout<<"0"<<"<="<<"z_"<<i<<"<="<<"1"<<";"<<endl;
    }
    // set up z_i value manually
    //vector<int> zz={0,1,2,3,5,6,7,14,16,17,18};
    //    vector<int> zz={0,1,2,4,5,6,7,12,14,16,18};
    //    int flagg=0;
    //    for (int i=0; i<NUM_NODES; i++) {
    //        for (int j=0; j<zz.size(); j++) {
    //            if (i==zz[j]) {
    //                flagg=1;
    //            }
    //        }
    //        if (flagg==1) {
    //            sout<<"z_"<<i<<"=1;"<<endl;
    //            flagg=0;
    //        }
    //        else{
    //            sout<<"z_"<<i<<"=0;"<<endl;
    //        }
    //    }
    
    //print int variables
    sout<<"int X_0_0_0";
    //cout<<"int X_0_0_0";
    // print z_i
    for (int l=0; l<NUM_NODES; l++) {
        int i=l;
        sout<<","<<"z_"<<i;
        //cout<<","<<"z_"<<i;
    }
    sout<<";"<<endl;
    //cout<<";"<<endl;
    sout.close();
    
}
void Generate_LC_File_RelayNode_q(){
    ofstream sout;
    char outputfileName[20];
    sprintf(outputfileName, "LC_RelayNode.lp");
    sout.open(outputfileName);
    if (sout.fail())
    {
        std::cout<<"打开文件错误!"<<std::endl;
    }
    sout<<"max: "<<endl;
    //cout<<"max: "<<endl;
    // the object function: q
    sout<<"q;"<<endl;
    //cout<<";"<<endl;
    // subject to: z_i+z_j<=1
    for (int l=0; l<Ec_length; l++) {
        int i=Ec[l].pointA_id;
        int j=Ec[l].pointB_id;
        sout<<"z_"<<i<<"+"<<"z_"<<j<<"<="<<"1"<<";"<<endl;
        //cout<<"z_"<<i<<"+"<<"z_"<<j<<"<="<<"1"<<";"<<endl;
        
    }
    // subject to: sumz_i>=alfa*z_j
    for (int l=0; l<W_length; l++) {
        int i=l;
        sout<<"+"<<"z_"<<W[i];
        //cout<<"+"<<"z_"<<W[i];
    }
    sout<<">=q;"<<endl;
    
    // subject to: sumz_j>=alfa*z_i
    for (int l=0; l<Z_length; l++) {
        int i=l;
        sout<<"+"<<"z_"<<Z[i];
        //cout<<"+"<<"z_"<<Z[i];
    }
    sout<<">=q;"<<endl;
    
    // subject to: z_i+sumz_j<=c_i
    int i_flag=0;
    for (int l=0; l<NUM_NODES; l++) {
        i_flag=l;
        sout<<"z_"<<i_flag;
        //cout<<"z_"<<i_flag;
        for (int l=0; l<NUM_NODES; l++) {
            if (l==i_flag) {
                if (l==NUM_NODES-1) {
                    break;
                }
                l++;
            }
            sout<<"+"<<"z_"<<l;
            //cout<<"+"<<"z_"<<l;
        }
        
        sout<<"<="<<c[i_flag]+NUM_NODES<<"-"<<NUM_NODES<<"*"<<"z_"<<i_flag<<";"<<endl;
        //cout<<"<="<<c[i_flag]<<";"<<endl;
    }
    //print all the variables
    //0<=z_i<=1
    for (int l=0; l<NUM_NODES; l++) {
        int i=l;
        sout<<"0"<<"<="<<"z_"<<i<<"<="<<"1"<<";"<<endl;
        //cout<<"0"<<"<="<<"z_"<<i<<"<="<<"1"<<";"<<endl;
    }
    // set up z_i value manually
    //vector<int> zz={0,1,2,3,5,6,7,14,16,17,18};
    //    vector<int> zz={0,1,2,4,5,6,7,12,14,16,18};
    //    int flagg=0;
    //    for (int i=0; i<NUM_NODES; i++) {
    //        for (int j=0; j<zz.size(); j++) {
    //            if (i==zz[j]) {
    //                flagg=1;
    //            }
    //        }
    //        if (flagg==1) {
    //            sout<<"z_"<<i<<"=1;"<<endl;
    //            flagg=0;
    //        }
    //        else{
    //            sout<<"z_"<<i<<"=0;"<<endl;
    //        }
    //    }
    
    //print int variables
    sout<<"int X_0_0_0";
    //cout<<"int X_0_0_0";
    // print z_i
    for (int l=0; l<NUM_NODES; l++) {
        int i=l;
        sout<<","<<"z_"<<i;
        //cout<<","<<"z_"<<i;
    }
    sout<<";"<<endl;
    //cout<<";"<<endl;
    sout.close();
    
}
void Read_RelayNode_File(char* filename){
    char line[100];
    
    int i = 0;
    int n=0;
    int b=0;
    
    int number1 = -1;//x_i的i
    int number2 =-1;//x_i的值
    int z_i_length = 0;
    
    
    
    FILE *file = fopen ( filename, "r" );
    
    while ( fgets ( line, sizeof line, file ) != NULL )
    {
        i=0;
        while (line[i]!='\0')
        {
            // 获取z_i
            if (line[i] == 'z' && line[i+1] == '_')
            {
                char temp1[10];//装x_i的i
                char temp2[10];//装x_i的值
                b=0;
                memset(temp1,0,sizeof(temp1));
                while(!isdigit(line[i])) i++;
                while(isdigit(line[i]))
                {
                    temp1[b++] = line[i];
                    i++;
                }
                temp1[b] = '\0';
                number1 = -1;
                number1 = atoi(temp1);
                
                while(!isdigit(line[i])) i++;
                n=0;
                memset(temp2,0,sizeof(temp2));
                while(isdigit(line[i]))
                {
                    temp2[n++] = line[i];
                    i++;
                }
                temp2[n] = '\0';
                number2 = -1;
                number2 = atoi(temp2);
                
                if (number1 !=-1 && number2!=-1)
                {
                    z_[z_i_length]=number1;
                    z_i[z_i_length]=number2;
                    z_i_length++;
                }
                
                break;
                
            }
            else  break;
        }
    }
    
    for (int i=0; i<z_i_length; i++) {
        Relaynode_result[i] = z_i[i];
    }
    Relaynode_result={1,1,1,0,1,0,0,1,0,0,0,0,1,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0};
    
    cout<<"Relaynode结果："<<endl;
    for (int i=0; i<Relaynode_result.size(); i++) {
        if (Relaynode_result[i]==1) {
            cout<<","<<i+1;
        }
    }
    cout<<endl;
}
int RelayNode(){
    
    char file_name[20] = "LC_RelayNode.lp";
    char test_model[20] = "test_model";
    char output_log[20] = "LC_RelayNode.txt";
    lprec *lp;
    
    ofstream sOut;
    ifstream sin;
    
    Generate_LC_File_RelayNode_q();
    lp = read_LP(file_name, NORMAL, test_model);
    
    if(lp == NULL)
    {
        cout<< "Unable to read model\n";
        return FAILURE;
    }
    
    set_outputfile(lp, output_log);
    solve(lp);
    print_objective(lp);
    print_solution(lp, 1);
    Read_RelayNode_File(output_log);
    
    //关闭 很重要
    delete_lp(lp);
    return SUCCESS;
}

void outputAbarPosition(){
    ofstream sout;
    char outputfileName[20];
    sprintf(outputfileName, "AbarPosition.txt");
    sout.open(outputfileName);
    if (sout.fail())
    {
        std::cout<<"打开文件错误!"<<std::endl;
    }
    for (int i=0; i<Partition_result.size(); i++) {
        if (Partition_result[i]==0) {
            sout<<localvertice[i].node_x<<" "<<localvertice[i].node_y<<endl;
        }
    }
    
    sout.close();
}
void outputZiPosition(){
    ofstream output;
    output.open("ziPosition.txt");
    for (int i=0; i<NUM_NODES; i++) {
        if (Relaynode_result[i]==1) {
            output<<localvertice[i].node_x<<" "<<localvertice[i].node_y<<endl;
        }
    }
    output.close();
}
int main(int argc, const char * argv[]){
    //================initial
    
    
    getLocalGraph();
    Partition();
    //getEc();
    //getAset();
    //getAbarset();
    //getCset();
    //RelayNode();
    //outputAbarPosition();
    //outputZiPosition();
    
    return 0;
    
}

