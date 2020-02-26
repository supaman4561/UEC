function makeCodebook(imgpaths, sz)
    imload = @(path) im2double(rgb2gray(imread(path)));
    I = cellfun(imload, imgpaths, 'UniformOutput', false);
    [~, desc] = cellfun(@(I_) sift_rand(I_, 'randn', 300), I, ...
                           'UniformOutput', false);
    vec = cell2mat(desc);
    [codebook, ~] = vl_kmeans(vec, sz);  % クラスタリング
    
    save('codebook.mat', 'codebook');  % 保存
end