function out = makesnd(f, t)
    volume = 1;
    fs = 22050;
    y = volume * sin(2 * %pi * f * [0:1:(fs * t)] / fs);   
    out = y;
endfunction

function out = hardclipping(wave)
    amp = 100;
    wave = wave * amp;
    wave = min(wave, 0.5);
    wave = max(wave, -0.5);
    out = wave;
endfunction

fs = 22050;

/* sounds */
C4  = 261.63;
C4s = 277.18; 
D4  = 293.66;
D4s = 311.13;
E4  = 329.63;
F4  = 349.23;
F4s = 369.99;
G4  = 392.00;
G4s = 415.30;
A4  = 440.00;
A4s = 466.16;
B4  = 493.88;
C5  = 523.25;
C5s = 554.37;
D5  = 587.33;
D5s = 622.25;
E5  = 659.26;
F5  = 698.46;
F5s = 739.99;
G5  = 783.99;
G5s = 830.61;
A5  = 880.00;
A5s = 932.33;
B5  = 987.77;
C6  = 1046.50;
C6s = 1108.73;
D6  = 1174.66;
D6s = 1244.51;
E6  = 1318.51;
F6  = 1396.91;
F6s = 1479.98;
G6  = 1567.98;
G6s = 1661.22;
A6  = 1760.00;
A6s = 1864.66;
B6  = 1975.53;

/* shoten */
playsnd(makesnd(D5, 0.3));
playsnd(makesnd(D5, 0.15));
playsnd(makesnd(D5, 0.2));
playsnd(makesnd(0, 0.1));
playsnd(makesnd(G5, 0.13));
playsnd(makesnd(E5, 0.13));
playsnd(makesnd(D5, 0.13));
playsnd(makesnd(0, 0.3));
playsnd(makesnd(E5, 0.15));
playsnd(makesnd(0, 0.10));
playsnd(makesnd(E5, 0.15));

/* Harry Potter */
/*
playsnd(hardclipping(makesnd(B4, 0.6)));
playsnd(hardclipping(makesnd(E5, 0.8)));
playsnd(hardclipping(makesnd(0, 0.08)));
playsnd(hardclipping(makesnd(G5, 0.2)));
playsnd(hardclipping(makesnd(F5s, 0.4)));
playsnd(hardclipping(makesnd(E5, 0.8)));
playsnd(hardclipping(makesnd(B5, 0.6)));
playsnd(hardclipping(makesnd(A5, 1.2)));
playsnd(hardclipping(makesnd(F5s, 1.2)));
playsnd(hardclipping(makesnd(E5, 0.8)));
playsnd(hardclipping(makesnd(G5, 0.2)));
playsnd(hardclipping(makesnd(F5s, 0.4)));
playsnd(hardclipping(makesnd(D5s, 0.8)));
playsnd(hardclipping(makesnd(F5, 0.4)));
playsnd(hardclipping(makesnd(B4, 1.2)));
*/