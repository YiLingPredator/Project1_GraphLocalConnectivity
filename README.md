Project1_GraphLocalConnectivity
===============================
This repository including two branches: partition and partitionWithEta. 

The former one is based on Globecom 2014. It can do partition and relay node deployment. How it works?
1. Read the NodePosition.txt
2. Do the partition.
3. Based on the partition, get the Ci value. Unfortunately, this program can not generate ci by itself. 
4. When get the ci from other program. Do the relaynode deployment to get the zi values which indicate which node can connect the relaynode.
5. Using Matlab to run CVX_relaynode_Globecom.m to get the position of relaynode.

The latter one is based on newassignment3.txt. It also can do partition and relay node deployment. The difference between them is that the latter don't need ci value. 
It only use partition result to get relaynode position.
1.Read the NodePosition.txt
2. Do the partition.
3. Using Matlab to run CVX_approx_exact.m which only use partition result and NodePosition to get the relaynode position.
