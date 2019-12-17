addpath('/usr/local/class/object/MATLAB/sift');
run('/usr/local/class/object/MATLAB/vlfeat/vl_setup');
load('positive.mat');
load('negative.mat');

% SIFT feature vectors
[pnt, desc] = cellfun(@(I) sift(I, 'threshold', 0.03), [P N], ...
                      'UniformOutput', false);
                  
% make codebook
vec = cell2mat(desc);
[codebook, idx] = vl_kmeans(vec, 500);


bovmP = cell2mat(cellfun(@(x) makeBoVM(codebook, x), P, ...
                            'UniformOutput', false));
bovmN = cell2mat(cellfun(@(x) makeBoVM(codebook, x), N, ...
                            'UniformOutput', false));

save('bovmP_sift.mat', 'bovmP');
save('bovmN_sift.mat', 'bovmN');
                        
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
    [~, desc] = sift(I, 'threshold', 0.03);
    descT = array2table(desc);
    cluster = varfun(@(x) nearest(x, codebook, 1), descT, ...
                            'OutputFormat', 'uniform');
    
    for i = 1:n
        bovm(i) = sum(cluster == i);
    end
end