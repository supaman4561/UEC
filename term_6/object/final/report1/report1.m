addpath('/usr/local/class/object/MATLAB/sift');
run('/usr/local/class/object/MATLAB/vlfeat/vl_setup');
addpath('/usr/local/class/object/matconvnet');
addpath('/usr/local/class/object/matconvnet/matlab');
vl_setupnn;

domainA = loadImagePath('img/frenchfries');
domainB = loadImagePath('img/hamburg');

acc = cross_validation(5, domainA, domainB, @NNWithColorHist);
fprintf('colorHist : acc = %f\n', acc);



function acc = NNWithColorHist(train_p, train_n, test_p, test_n)
    train_p = cellfun(@(p) im2ColorHist(p), train_p, 'UniformOutput', false);
    train_n = cellfun(@(p) im2ColorHist(p), train_n, 'UniformOutput', false);
    test_p = cellfun(@(p) im2ColorHist(p), test_p, 'UniformOutput', false);
    test_n = cellfun(@(p) im2ColorHist(p), test_n, 'UniformOutput', false);
    train_p = cell2mat(train_p');
    train_n = cell2mat(train_n');
    test_p = cell2mat(test_p');
    test_n = cell2mat(test_n');
    acc = nn(train_p, train_n, test_p, test_n);
end

function list = loadImagePath(dirname)
    list={};
    DIR = strcat(dirname, '/');
    W = dir(DIR);
    
    for j=1:size(W)
        if (strfind(W(j).name,'.jpg'))
            fn = strcat(DIR, W(j).name);
            list = {list{:} fn};
        end
    end
end