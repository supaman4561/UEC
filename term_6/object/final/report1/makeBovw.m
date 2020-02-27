function bovw = makeBovw(codebook, imgpath, pn)
    [~, n] = size(codebook);
    bovw = zeros(n, 1);
    I = im2double(rgb2gray(imread(imgpath)));
    [~, desc] = sift_rand(I, 'randn',  pn);
    desc_ = reshape(repmat(desc, size(codebook, 2), 1), size(desc, 1), []);
    codebook_ = repmat(codebook, 1, size(desc, 2));
    dist = sum((desc_ - codebook_).^2);
    [~, cluster] = min(reshape(dist, size(codebook, 2), []));

    for i = 1:size(codebook, 2)
        bovw(i) = sum(cluster == i);
    end
end
