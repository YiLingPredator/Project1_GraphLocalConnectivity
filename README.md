Introduction to partition
===============================
This repository including two branches: partition and partitionWithEta. 

Ps: the Read_RelayNode_file() function is wrong. I have to updates it by checking LC_RelayNode.txt.

The partition is based on Globecom 2014. It can do partition and relay node deployment. How it works?
1. Read the NodePosition.txt
2. Do the partition.
3. Based on the partition, get the Ci value. Unfortunately, this program can not generate ci by itself. 
4. When get the ci from other program. Do the relaynode deployment to get the zi values which indicate which node can connect the relaynode.
5. Using Matlab to run CVX_relaynode_Globecom.m to get the position of relaynode.
