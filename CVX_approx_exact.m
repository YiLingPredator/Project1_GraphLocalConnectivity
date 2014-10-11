n=2;
k=30;
%get all vertices position
[X,Y]=textread('Position.txt','%f %f');
bis=[X,Y];
%get the partition
A=[1,2,5,7,10,12,13,14,16,19,22,24,26,27,29];
A_bar=[3,4,6,8,9,11,15,17,18,20,21,23,25,28,30];

%set the radius to 50
ris=ones(1,k)*50;

cvx_begin
variable pt(n);
variable dist(k);
variable z(k);
variable sum_A;
variable sum_A_bar;

maximize(sum(z));
subject to
    pt(1) >= 0;
    pt(2) >= 0;
	pt(1) <= 150;
	pt(2) <= 150;

    for  j=1:k
        norm(pt'-bis(j,:))<= dist(j);
		z(j)<=min(1, -2*dist(j)/ris(j)+3);
        %z(j)<=min(1, -3/4*dist(j)/ris(j)+7/4);
        z(j)<=1;
        %z(j)>=0;
       
    end
    %pos_z=pos(z);
    sum_A >= sum(pos(z([A],1)));
    sum_A_bar >= sum(pos(z([A_bar],1)));   
    sum_A-0.7*sum_A_bar>=0;
    sum_A_bar-0.7*sum_A>=0;
cvx_end

c=sum(pos(z));
			 
zz=ones(1,k);
dd=ones(1,k);
			 
for  j=1:k
  dd(j)=norm(pt'-bis(j,:));
  zz(j)=min(1, square_pos(inv_pos(dd(j)/ris(j))));
end
d=sum(zz);


