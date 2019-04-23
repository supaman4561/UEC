theta = [0:0.1:2*%pi+0.1];
// Amplitudes
A = 2;
B = 3;
// frequency
fa = 3;
fb = 4;

// phase
phase = 0;

x = A * sin( fa * theta + phase );
y = B * sin( fb * theta );

plot(x, y);
