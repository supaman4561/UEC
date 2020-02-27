function list = loadImagePath(dirname)
    list={};
    DIR = strcat(dirname, '/');
    W = dir(DIR);
    
    for j=1:size(W)
        if (strfind(W(j).name,'.jpg'))
            fn = strcat(DIR, W(j).name);
            list = {list{:} fn};
        end
    end
end