rect_wave = [ones(1,50), zeros(1,50)]-0.5;
sin_wave = 0.5 * sin(2*%pi * [1:100]/ 100);
saw_wave = [1:100]/100-0.5;

rect_wave = [rect_wave, rect_wave, rect_wave, rect_wave, rect_wave];
sin_wave = [sin_wave, sin_wave, sin_wave, sin_wave, sin_wave];
saw_wave = [saw_wave, saw_wave, saw_wave, saw_wave, saw_wave];

rect_fourier = fft(rect_wave);
sin_fourier = fft(sin_wave);
saw_fourier = fft(saw_wave);

rect_power_spc = rect_fourier .* conj(rect_fourier);
sin_power_spc = sin_fourier .* conj(sin_fourier);
saw_power_spc = saw_fourier .* conj(saw_fourier);

plot(rect_power_spc);
plot(sin_power_spc, color = 'red');
plot(saw_power_spc, color = 'green');
