n=0; db=[];
LIST={'cat' 'dog' 'elephant' 'fish' 'horse' 'lion' 'penguin' 'tiger' 'whale' 'wildcat'};
DIR0='/usr/local/class/object/animal/';
for i=1:length(LIST)
    DIR=strcat(DIR0,LIST(i),'/');
    W=dir(DIR{:});

    for j=1:size(W)
        if (strfind(W(j).name,'.jpg'))
            fn=strcat(DIR{:},W(j).name);
            h = im2hist64(imread(fn));
            h = h / sum(h);
            db = [db; {fn h}];
        end
    end
end

save('db.mat', 'db');