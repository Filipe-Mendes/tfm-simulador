%global f0_lp w0_lp qsi f0_acc w0_acc f0_vel w0_vel f0_pos w0_pos;

% low pass filter ordem 2
f0_lp = 1;
w0_lp = 2*pi*f0_lp;
qsi = 1;

% high pass filter acc
f0_acc = 0.1;
w0_acc = 2*pi*f0_acc;

f0_vel = 0.3;
w0_vel = 2*pi*f0_vel;

f0_pos = 1;
w0_pos = 2*pi*f0_pos;