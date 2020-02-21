% nearest neighbor method
% 各引数は配列とする
function nIdx = nn(train_p, train_n, test_p, test_n)
    train = [train_p; train_n];
    test = [test_p; test_n];
    
    % 全組み合わせでtrainのベクトルとtestのベクトル間の距離を算出
    train_ = repmat(train, size(test, 1), 1);
    test_ = reshape(repmat(reshape(test, 1, []), size(train, 1), 1), [], size(test, 2));
    dist = sum((train_ - test_).^2, 2);
    
    % 最近傍のindexを取得
    dist_mat = reshape(dist, size(train, 1), size(test, 1));
    [~,nIdx] = min(dist_mat);
end