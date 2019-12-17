function matches = my_siftmatch(desc1, desc2)    
    matches = [];
    for i1 = 1:size(desc1, 2)
        d = repmat(desc1(:, i1), 1, size(desc2, 2));
        dist = sum((desc2 - d).^2);
        [m1, i2] = min(dist);
        dist(i2) = [];
        m2 = min(dist);
        if (m2 > m1 * 1.5)
            matches = [matches [i1 i2]'];
        end
    end
 end