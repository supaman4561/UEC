function idx = nearest(dst, src, order)
    [~, n] = size(src);
    vec = repmat(dst, 1, n);
    dist = sum((src - vec).^2);
    [~, idx] = sort(dist);
    idx = idx(order);
end