load('db.mat');
sel = randperm(1000, 1000);
rand_path = db(sel, 1);
rand_imgs = db(sel, 2);
rand_imgs = vertcat(rand_imgs{:});

K = 10;
[C, idx] = vl_kmeans(rand_imgs', K);

figure;
for i=1:K
    paths = rand_path(idx == i);
    J = size(paths, 1);
    if J > 10
        J = 10;
    end 
    for j=1:J
        subplot(K, 10, K*(i-1)+j);
        imshow(imread(paths{j}));
    end
end
