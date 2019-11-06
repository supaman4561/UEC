m = 128;
n = 10000;
A = rand(n, m);
sample = rand(1, m);

tic
mask = repmat(sample, n, 1);
D = sum((A - mask).^2, 2);
[dummy, i] = min(D);
toc

fprintf('result: %d\n', i);