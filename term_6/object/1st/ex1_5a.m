n = 10;
m = 20;

A = rand(n,m);
D = zeros(n,n);

tic
for i=1:n
    for j=1:n
        a = A(i,:);
        b = A(j,:);
        D(i,j) = sqrt(sum((a-b).^2));
    end
end
toc