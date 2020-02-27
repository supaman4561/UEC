function accuracy = cross_validation(cv, pos, neg, func)
  acc = zeros(1, cv);             % accuracy   
  pos_size = size(pos, 2);
  neg_size = size(neg, 2);
  pos = pos(randperm(pos_size));  % ランダム置換
  neg = neg(randperm(neg_size)); 
  pIdx = [1:pos_size];
  nIdx = [1:neg_size];
  for i = 1:cv
    train_p  = pos(:, find(mod(pIdx, cv)~=(i-1)));
    test_p   = pos(:, find(mod(pIdx, cv)==(i-1)));
    train_n  = neg(:, find(mod(nIdx, cv)~=(i-1)));
    test_n = neg(:, find(mod(nIdx, cv)==(i-1)));
    
    acc_ = func(train_p, train_n, test_p, test_n);
    fprintf("[%d] acc = %f\n", i, acc_);
    acc(i) = acc_;
  end
  accuracy = mean(acc);
end