addpath('/usr/local/class/object/matconvnet');
addpath('/usr/local/class/object/matconvnet/matlab');
vl_setupnn;

pos_size = 50;
neg_size = 500;
pos_path = loadImagePath('relevance_yakitori');
pos_path = pos_path(1:pos_size);
neg_path = loadImagePath('/usr/local/class/object/bgimg');
neg_path = neg_path(randperm(size(neg_path, 2), neg_size));

pos_dcnnf = cell2mat(cellfun(@(p) makeDcnnf(p), pos_path, 'UniformOutput', false));
neg_dcnnf = cell2mat(cellfun(@(p) makeDcnnf(p), neg_path, 'UniformOutput', false));

all_dcnnf = [pos_dcnnf neg_dcnnf];
label = [ones(pos_size, 1); ones(neg_size, 1)*(-1)];
model = fitcsvm(all_dcnnf', label, 'KernelFunction', 'linear');

target_path = loadImagePath('latest_yakitori');
target_dcnnf = cell2mat(cellfun(@(p) makeDcnnf(p), target_path, 'UniformOutput', false));
[plabel, score] = predict(model, target_dcnnf');

[sorted_score, sorted_idx] = sort(score(:,2), 'descend');
FID = fopen('result/reranking50.txt', 'w');
for i=1:numel(sorted_idx)
    fprintf(FID, '%s %f\n', target_path{sorted_idx(i)}, sorted_score(i));
end
fclose(FID);