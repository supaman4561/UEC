function I = normImage(imgpath)
  I = imread(imgpath);
end

// colorhistgramの作成
function acc = NN_ColHist(train, test)
  train_ch = cellfun(im2ColorHist, train, 'UniformOutput', false)
  test_ch = cellfun(im2ColorHist, test, 'UniformOutput', false)
  
end
