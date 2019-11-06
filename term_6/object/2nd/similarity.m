function sim = similarity(I1, I2)
    h1 = im2hist64(I1);
    h2 = im2hist64(I2);
    h1 = h1 / sum(h1);  % ³‹K‰»
    h2 = h2 / sum(h2);  % ³‹K‰»
    sim = sum(min(h1, h2));
end