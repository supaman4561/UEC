n = 10000;
m = 128;

DB = rand(n,m);
sample = rand(1,m);

tic
min = norm(sample - DB(1,:));
min_index = 1;
for i=2:n
    diff = norm(sample - DB(i,:));
    if min >= diff
        min = diff;
        min_index = i;
    end
end
toc

fprintf('result: %d\n', min_index);