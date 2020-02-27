function savePath(paths, filepath)
    FID = fopen(filepath, 'a');
    for i = 1:size(paths, 2)
        fprintf(FID, '%s\n', paths{i});
    end
end