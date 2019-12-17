run('/usr/local/class/object/MATLAB/vlfeat/vl_setup');
load('bovmAll.mat');
load('pathlist.mat');

K = 10;
[C, idx] = vl_kmeans(bovmAll, K);

Y = tsne(bovmAll');
figure;
colors = ['r' 'b' 'g' 'c' 'm' 'r' 'b' 'g' 'c' 'm'];
marker = ['o' 'o' 'o' 'o' 'o' '^' '^' '^' '^' '^'];
hold on
for i=1:K
    scatter(Y(idx==i, 1), Y(idx==i, 2), colors(i), marker(i));
end
hold off

figure;
ROW = 10;
for i=1:K
    paths = list(idx == i);
    J = length(paths);
    paths = paths(randperm(J));
    if J > ROW
        J = ROW;
    end 
    for j=1:J
        subplot(K, 10, ROW*(i-1)+j);
        imshow(imread(paths{j}));
    end
end