function list = loadimpath()
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
end