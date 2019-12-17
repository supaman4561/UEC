addpath('/usr/local/class/object/MATLAB/sift');
load('codebook.mat');  % codebook
load('pathlist.mat');  % 画像へのパス

imload = @(path) im2double(rgb2gray(imread(path)));
all = cellfun(imload, list, 'UniformOutput', false);
bovmAll = cell2mat(cellfun(@(x) makeBoVM(codebook, x), all, ...
                            'UniformOutput', false));
                        
save('bovmAll.mat', 'bovmAll');


%========= functions ================

function idx = nearest(dst, src, order)
    [~, n] = size(src);
    vec = repmat(dst, 1, n);
    dist = sum((src - vec).^2);
    [~, idx] = sort(dist);
    idx = idx(order);
end

function bovm = makeBoVM(codebook, I)
    [~, n] = size(codebook);
    bovm = zeros(n, 1);
    [~, desc] = sift_rand(I, 'randn', 1000);
    descT = array2table(desc);
    cluster = varfun(@(x) nearest(x, codebook, 1), descT, ...
                            'OutputFormat', 'uniform');
    
    for i = 1:n
        bovm(i) = sum(cluster == i);
    end
end
