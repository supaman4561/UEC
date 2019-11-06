function h = im2hist64(I)
    X64 = im2x64(I);
    X64_vec = reshape(X64, 1, numel(X64));
    h = histcounts(X64_vec, [0:63]);
end