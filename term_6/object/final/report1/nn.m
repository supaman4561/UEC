% nearest neighbor method
% 各引数は配列とする
function acc = nn(train_p, train_n, test_p, test_n)
    train = [train_p; train_n];
    test = [test_p; test_n];
    
    % 全組み合わせでtrainのベクトルとtestのベクトル間の距離を算出
    train_ = repmat(train, size(test, 1), 1);
    test_ = reshape(repmat(reshape(test, 1, []), size(train, 1), 1), [], size(test, 2));
    dist = sum((train_ - test_).^2, 2);
    
    % 最近傍のindexを取得
    dist_mat = reshape(dist, size(train, 1), size(test, 1));
    [~,nIdx] = min(dist_mat);
    
    % 認識率の計算
    border = size(train_p, 1);
    nIdxP = nIdx(1:size(test_p, 1));                % ポジティブの分類先Index
    nIdxN = nIdx((size(test_p, 1)+1):end);  % ネガティブの分類先Index
    total = size(test, 1);
    acc = (sum(nIdxP <= border) + sum(nIdxN > border)) / total;  % TP+TN/total
end