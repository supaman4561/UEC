load('db.mat');
sel = randperm(1000, 1000);
rand_path = db(sel, 1);
rand_imgs = db(sel, 2);
rand_imgs = vertcat(rand_imgs{:});

K = 10;
tic;
[C, idx] = vl_kmeans(rand_imgs', K);
toc;
Y = tsne(rand_imgs);

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
    paths = rand_path(idx == i);
    J = length(paths);
    if J > ROW
        J = ROW;
    end 
    for j=1:J
        subplot(K, 10, ROW*(i-1)+j);
        imshow(imread(paths{j}));
    end
end