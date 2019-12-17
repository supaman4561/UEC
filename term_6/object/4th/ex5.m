load('bovmP_sift.mat');  % ポジティブ画像のBoVMベクトル
load('bovmN_sift.mat');  % ネガティブ画像のBoVMベクトル

bovmPN = [bovmP bovmN];

bovmPT = array2table(bovmP);
bovmNT = array2table(bovmN);

simIdxP = varfun(@(x) nearest(x, bovmPN, 2), bovmPT, ...
                    'OutputFormat', 'uniform');
simIdxN = varfun(@(x) nearest(x, bovmPN, 2), bovmNT, ...
                    'OutputFormat', 'uniform');
                
border = size(bovmP, 2);
total = size(bovmPN, 2);
accuracy = sum(simIdxP <= border) + sum(simIdxN > border) / total;
fprintf('accuracy : %f \n', accuracy);

function idx = nearest(dst, src, order)
    [~, n] = size(src);
    vec = repmat(dst, 1, n);
    dist = sum((src - vec).^2);
    [~, idx] = sort(dist);
    idx = idx(order);
end