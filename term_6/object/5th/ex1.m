addpath('/usr/local/class/object/MATLAB/sift');
run('/usr/local/class/object/MATLAB/vlfeat/vl_setup');
load('bovmP.mat');
load('bovmN.mat');

pr_pos = sum(bovmP') + 1;
pr_pos = pr_pos/sum(pr_pos);
pr_pos = log(pr_pos);

pr_neg = sum(bovmN')  + 1;
pr_neg = pr_neg/sum(pr_neg);
pr_neg = log(pr_neg);

bovmPN = [bovmP bovmN];

cnt = 0;
for i=1:200
    bovm = bovmPN(:,i)';
    max0=max(bovm); 
    idx=[];
    for j=1:max0
        idx=[idx find(bovm>=j)];
    end

    pr_im_pos=sum(pr_pos(idx));
    pr_im_neg=sum(pr_neg(idx));
    
    if ~xor((pr_im_pos > pr_im_neg), (i<=100))
        cnt = cnt + 1;
    end
end

accuracy = cnt / 200;