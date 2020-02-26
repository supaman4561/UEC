function accuracy = cross_validation(cv, pos, neg, func)
  acc = [];                          % accuracy   
  pos = pos(randperm(size(pos, 1)));  % ランダム置換
  neg = neg(randperm(size(neg, 1))); 
  pos_n = size(pos, 1);
  neg_n = size(neg, 1);
  pIdx = [1:pos_n];
  nIdx = [1:neg_n];
  for i = 1:cv
    train_p  = pos(find(mod(pIdx, cv)~=(i-1)), :);
    test_p   = pos(find(mod(pIdx, cv)==(i-1)), :);
    train_n  = neg(find(mod(nIdx, cv)~=(i-1)), :);
    test_n = neg(find(mod(nIdx, cv)==(i-1)), :);
    
    acc_ = func(train_p, train_n, test_p, test_n);
    acc = [acc acc_];
  end
  accuracy = mean(acc);
end