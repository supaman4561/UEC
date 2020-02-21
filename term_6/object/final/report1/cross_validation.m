function acc = cross_validation(n, pos, neg, func)
  acc = []                           // accuracy   
  pos = pos[randperm(length(pos))]   // ランダム置換
  neg = neg[randperm(length(neg))]   // ランダム置換
  for i = 1:n
	    train = []
  end
end