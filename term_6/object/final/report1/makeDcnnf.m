function dcnnf = makeDcnnf(imgpath)
    net = load('imagenet-caffe-alex.mat');
    ims = loadImage(net, imgpath);
    res = vl_simplenn(net, ims);
    dcnnf = squeeze(res(end-3).x);
    dcnnf = dcnnf / norm(dcnnf);
end

function im = loadImage(net, imgpath)
    im_ = imread(imgpath);
    im_ = single(im_);
    im_ = imresize(im_, net.meta.normalization.imageSize(1:2));
    im = im_ - net.meta.normalization.averageImage;
end