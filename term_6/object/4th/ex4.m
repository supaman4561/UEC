addpath('/usr/local/class/object/MATLAB/sift');
load('positive.mat');  % ポジティブ画像情報
load('negative.mat');  % ネガティブ画像情報
load('codebook.mat');  % codebook
load('PImgPath.mat');  % ポジティブ画像のパス
load('NImgPath.mat');  % ネガティブ画像のパス

images = [P N];

bovmP = cell2mat(cellfun(@(x) makeBoVM(codebook, x), P, ...
                            'UniformOutput', false));
bovmN = cell2mat(cellfun(@(x) makeBoVM(codebook, x), N, ...
                            'UniformOutput', false));
bovmPN = [bovmP bovmN];  % 200 bovms of P and N

sampleP = randperm(100, 5);        % sampling  5 idxs from P
sampleN = randperm(100, 5) + 100;  % sampling  5 idxs from N
sample = [sampleP sampleN];

samplePath = [PImgPath NImgPath];
sampleTable = array2table(bovmPN(:, sample));
simIdx = varfun(@(x) nearest(x, bovmPN, 2), sampleTable, ...
                        'OutputFormat', 'uniform');

save('bovmP.mat', 'bovmP');  % ポジティブ画像のBoVMを保存
save('bovmN.mat', 'bovmN');  % ネガティブ画像のBoVMを保存

%plot
for i = 1:10
    subplot(10, 2, i*2-1);
    imshow(imread(samplePath{sample(i)}));
    subplot(10, 2, i*2);
    imshow(imread(samplePath{simIdx(i)}));  % 2nd nearest
end

%===== function =======%
                        
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