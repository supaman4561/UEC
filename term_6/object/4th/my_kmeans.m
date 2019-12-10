function [IDX, C] = my_kmeans(X, K)
    MAX_ITER = 1000;
    iter = 0;
    [rX, cX] = size(X);
    C = X(randsample(rX, K), :);
    oldC = zeros(K, cX);
    IDX = zeros(rX);
    while ~isequal(C, oldC) && (iter <= MAX_ITER)
        iter = iter + 1;
        oldC = C;
        vecC = reshape(repmat(reshape(C,1,K*cX),rX,1),rX*K,cX);
        vecX = repmat(X, K, 1);
        dist = reshape(sum((vecC - vecX) .^ 2, 2)',[rX,K]);
        [dummy,IDX] = min(dist,[],2);
        for i=1:K
            C(i) = mean(X(IDX==i));
        end
    end 
end