function ch = im2ColorHist(I)
  % 各チャネルの要素を取得
  red = I(:, :, 1);
  green = I(:, :, 2);
  blue = I(:, :, 3);
　
  % 64色に減色
  X64 = floor(double(red)/64)*4*4 + floor(double(green)/64)*4 + floor(double(blue)/64);

  % カラーヒストグラムの作成
  X64_v = reshape(X64, 1, numel(X64));
  ch = histcounts(X64_v, [0:63]);
end
