% nearest neighbor method
% 各引数は配列とする
function idx = NN(src, dst)
    % 全組み合わせでtrainのベクトルとtestのベクトル間の距離を算出
    src_ = repmat(src, size(dst, 1), 1);
    dst_ = reshape(repmat(reshape(dst, 1, []), size(src, 1), 1), [], size(dst, 2));
    dist = sum((src_ - dst_).^2, 2);
    
    % 最近傍のindexを取得
    dist_mat = reshape(dist, size(src, 1), size(dst, 1));
    [~,idx] = min(dist_mat);
end