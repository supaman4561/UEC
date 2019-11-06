n = 10;
m = 20;

A = rand(n,m);

tic
r1 = repmat(A, n, 1);
r2 = reshape(repmat(reshape(A, 1, n*m), n, 1), n*n, m);
dist = sqrt(sum(((r1-r2).^2),2));
D = reshape(dist, n, n);
toc