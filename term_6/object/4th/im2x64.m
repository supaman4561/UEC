function X6function X64 = im2x64(I)
    RED = I(:,:,1);
    GREEN = I(:,:,2);
    BLUE = I(:,:,3);
    X64 = floor(double(RED)/64) *4 *4 + floor(double(GREEN)/64) * 4 + floor(double(BLUE)/64);
end4 = im2x64(I)
    RED = I(:,:,1);
    GREEN = I(:,:,2);
    BLUE = I(:,:,3);
    X64 = floor(double(RED)/64) *4 *4 + floor(double(GREEN)/64) * 4 + floor(double(BLUE)/64);
end