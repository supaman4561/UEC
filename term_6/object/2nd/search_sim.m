function [sorted, index, url] = search_sim(N)
    load('db.mat');
    query=db(N,2);
    sim = [];
    for i=1:size(db, 1)
        tmp = db(i, 2);
        sim = [sim intersection(tmp{:}, query{:})];
    end
    [sorted, index] = sort(sim, 'descend');
    url = db(index, 1);