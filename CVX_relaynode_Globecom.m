n=2;
k=10;
[X,Y]=textread('ziPosition.txt','%f %f');
bis=[X,Y];
%set the radius to 50
ris=ones(1,k)*50;


cvx_begin
variable pt(n);
variable dist(k);

minimize(sum(dist));
subject to
    pt(1) >= 0;
    pt(2) >= 0;
    for  j=1:k
		norm(pt'-bis(j,:))<= dist(j);
		dist(j) <= ris(j);
    end
cvx_end