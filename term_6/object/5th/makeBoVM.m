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