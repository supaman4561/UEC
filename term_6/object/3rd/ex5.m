addpath('/usr/local/class/object/MATLAB/sift');
DIR = '/home2/y2017/s1710730/workspace/UEC/term_6/object/3rd/img/';

pathlist = {};
W = dir(DIR);
for i=1:size(W)
    if (strfind(W(i).name, '.jpg'))
        fn = strcat(DIR, W(i).name);
        pathlist = [pathlist fn];
    end
end

imlist = cellfun(@(path) im2double(rgb2gray(imread(path))), pathlist, 'UniformOutput', false);
[pntlist, desclist] = cellfun(@sift, imlist, 'UniformOutput', false);
sim_matrix = cellfun(@similar, ...
                     repmat(desclist, size(desclist, 2) , 1), ...
                     repmat(desclist', 1, size(desclist, 2)));
        
        
function s = similar(desc1, desc2)
    match = size(siftmatch(desc1, desc2), 2);
    ave = (size(desc1, 2) + size(desc2, 2)) / 2;
    s = match / ave;
end
