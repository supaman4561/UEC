addpath('/usr/local/class/object/MATLAB/sift');
run('/usr/local/class/object/MATLAB/vlfeat/vl_setup');
addpath('/usr/local/class/object/matconvnet');
addpath('/usr/local/class/object/matconvnet/matlab');
vl_setupnn;

domainA = loadImagePath('img/napoli');
domainB = loadImagePath('img/yakisoba');

acc = cross_validation(5, domainA, domainB, @NNWithColorHist);
fprintf('colorHist : acc = %f\n', acc);

makeCodebook([domainA, domainB],500)
acc = cross_validation(5, domainA, domainB, @NLSVMWithBoF);
fprintf('BoF : acc = %f\n', acc);

acc = cross_validation(5, domainA, domainB, @SVMWithDCNNF);
fprintf('DCNNF : acc = %f\n', acc);

function acc = NNWithColorHist(train_p, train_n, test_p, test_n)
    % make color histogram
    train_p_ch = cellfun(@(p) im2ColorHist(p), train_p, 'UniformOutput', false);
    train_n_ch = cellfun(@(p) im2ColorHist(p), train_n, 'UniformOutput', false);
    test_p_ch = cellfun(@(p) im2ColorHist(p), test_p, 'UniformOutput', false);
    test_n_ch = cellfun(@(p) im2ColorHist(p), test_n, 'UniformOutput', false);
    
    % convert cell array to array(matrix)
    train_p_ch = cell2mat(train_p_ch');
    train_n_ch = cell2mat(train_n_ch');
    test_p_ch = cell2mat(test_p_ch');
    test_n_ch = cell2mat(test_n_ch');
    
    % nearest neighbor 
    idx = NN([train_p_ch; train_n_ch], [test_p_ch; test_n_ch]);
    % 認識率の計算
    border = size(train_p_ch, 1);
    nIdxP = idx(1:size(test_p_ch, 1));        % ポジティブの分類先Index
    nIdxN = idx((size(test_p_ch, 1)+1):end);  % ネガティブの分類先Index
    total = size([test_p_ch; test_n_ch], 1);
    acc = (sum(nIdxP <= border) + sum(nIdxN > border)) / total;  % TP+TN/total
    
    savePath([test_p(nIdxP <= border) test_n(nIdxN > border)], 'result/CH_true.txt');
    savePath([test_p(nIdxP > border) test_n(nIdxN <= border)], 'result/CH_false.txt');
end

function acc = NLSVMWithBoF(train_p, train_n, test_p, test_n)
    load('codebook.mat');
    pn = 1000;
    % make bag-of-visual-words
    train_p_bovw = cell2mat(cellfun(@(p) makeBovw(codebook, p, pn), train_p, 'UniformOutput', false));
    train_n_bovw = cell2mat(cellfun(@(p) makeBovw(codebook, p, pn), train_n, 'UniformOutput', false));
    test_p_bovw = cell2mat(cellfun(@(p) makeBovw(codebook, p, pn), test_p, 'UniformOutput', false));
    test_n_bovw = cell2mat(cellfun(@(p) makeBovw(codebook, p, pn), test_n, 'UniformOutput', false));
    
    % make dataset for non linear svm
    train = [train_p_bovw train_n_bovw];
    test = [test_p_bovw test_n_bovw];
    train_label = [ones(size(train_p, 2), 1); ones(size(train_n, 2), 1)*(-1)];
    test_label = [ones(size(test_p, 2), 1); ones(size(test_n, 2), 1)*(-1)];
    
    % svm
    model = fitcsvm(train', train_label, 'KernelFunction', 'rbf', 'KernelScale', 'auto', 'Standardize', true);
    [plabel, ~] = predict(model, test');
    acc = numel(find(test_label==plabel))/numel(test_label);
    
    testImgPath = [test_p test_n];
    savePath(testImgPath(test_label==plabel), 'result/BoF_true.txt');
    savePath(testImgPath(test_label~=plabel), 'result/BoF_false.txt'); 
end

function acc = SVMWithDCNNF(train_p, train_n, test_p, test_n)
    train_p_dcnnf = cell2mat(cellfun(@(p) makeDcnnf(p), train_p, 'UniformOutput', false));
    train_n_dcnnf = cell2mat(cellfun(@(p) makeDcnnf(p), train_n, 'UniformOutput', false));
    test_p_dcnnf = cell2mat(cellfun(@(p) makeDcnnf(p), test_p, 'UniformOutput', false));
    test_n_dcnnf = cell2mat(cellfun(@(p) makeDcnnf(p), test_n, 'UniformOutput', false));
    
    train = [train_p_dcnnf train_n_dcnnf];
    test = [test_p_dcnnf test_n_dcnnf];
    train_label = [ones(size(train_p, 2), 1); ones(size(train_n, 2), 1)*(-1)];
    test_label = [ones(size(test_p, 2), 1); ones(size(test_n, 2), 1)*(-1)];
    
    %svm
    model = fitcsvm(train', train_label, 'KernelFunction', 'linear');
    [plabel, ~] = predict(model, test');
    acc = numel(find(test_label==plabel))/numel(test_label);
    
    testImgPath = [test_p test_n];
    savePath(testImgPath(test_label==plabel), 'result/DCNNF_true.txt');
    savePath(testImgPath(test_label~=plabel), 'result/DCNNF_false.txt');    
end
