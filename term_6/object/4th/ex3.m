addpath('/usr/local/class/object/MATLAB/sift');
run('/usr/local/class/object/MATLAB/vlfeat/vl_setup');
n=0; list={};
LIST={'cat' 'dog' 'elephant' 'fish' 'horse' 'lion' 'penguin' 'tiger' 'whale' 'wildcat'};
DIR0='/usr/local/class/object/animal/';
for i=1:length(LIST)
    DIR=strcat(DIR0,LIST(i),'/');
    W=dir(DIR{:});

    for j=1:size(W)
        if (strfind(W(j).name,'.jpg'))
            fn=strcat(DIR{:},W(j).name);
            n=n+1;
            fprintf('[%d] %s\n',n,fn);
            list={list{:} fn};
        end
    end
end

imload = @(path) im2double(rgb2gray(imread(path)));

% positive images (cats)
P = cellfun(imload, list(1:100), 'UniformOutput', false);
% negative images (other animals)
rp = randperm(900, 100) + 100;
N = cellfun(imload, list(rp), 'UniformOutput', false);

% SIFT feature vectors
[pnt, desc] = cellfun(@(I) sift_rand(I, 'randn', 300), [P N], ...
                      'UniformOutput', false);
                  
% make codebook
vec = cell2mat(desc);
[codebook, idx] = vl_kmeans(vec, 500);

save('codebook.mat', 'codebook');