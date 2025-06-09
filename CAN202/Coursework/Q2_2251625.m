clear; clc; close all;
%% --- Q2-a: Load signal and plot spectrum ---
load('soundtrack.mat');  
N = length(soundtrack);
Fs = Fs_new;

X = fftshift(fft(soundtrack));
f = (-N/2:N/2-1)*(Fs/N);

figure;
plot(f, abs(X));
title('Spectrum of soundtrack (shifted)');
xlabel('Frequency (Hz)');
ylabel('Magnitude');
grid on;

%% --- Q2-e: High-quality superheterodyne receiver implementation ---
fc = 200e3;    % Carrier frequency
fi = 50e3;     % Intermediate frequency (IF)
BW = 5e3;      % Bandwidth
fs1 = Fs_new;  % Sampling rate
t = (0:N-1)'/fs1;

% 1. RF front-end bandpass filter (high-order)
bp_fc = fir1(800, [(fc-BW)/(fs1/2), (fc+BW)/(fs1/2)], 'bandpass');
x1 = filter(bp_fc, 1, soundtrack);

% Plot spectrum after RF BPF (treated as Filter1)
Ny = length(x1);
Xy = fftshift(fft(x1));
fy = (-Ny/2:Ny/2-1)*(fs1/Ny);
figure;
plot(fy, abs(Xy));
xlabel('Frequency (Hz)');
ylabel('Magnitude');
title('Spectrum of After Filter1');
grid on;

% 2. First mixing stage (downconvert to IF)
Fs2 = (115/114)*fs1;
[p2, q2] = rat(Fs2 / fs1, 1e-6);
x1_resample = resample(x1, p2, q2);
t2 = (0:length(x1_resample)-1)' / Fs2;

lo1 = cos(2*pi*(fc+fi)*t2);
m1 = x1_resample .* (2*lo1);

% Plot spectrum after Mixer1
Nm1 = length(m1);
Xm1 = fftshift(fft(m1));
fm1 = (-Nm1/2:Nm1/2-1)*(Fs2/Nm1);
figure;
plot(fm1, abs(Xm1));
xlabel('Frequency (Hz)');
ylabel('Magnitude');
title('Spectrum of Mixer1 Output');
grid on;

% 3. IF-stage bandpass filter (high-order)
bp_if = fir1(400, [(fi-BW)/(Fs2/2), (fi+BW)/(Fs2/2)], 'bandpass');
x2 = filter(bp_if, 1, m1);

% Plot spectrum after IF Filter
Nx2 = length(x2);
Xx2 = fftshift(fft(x2));
fx2 = (-Nx2/2:Nx2/2-1)*(Fs2/Nx2);
figure;
plot(fx2, abs(Xx2));
xlabel('Frequency (Hz)');
ylabel('Magnitude');
title('Spectrum of After Filter2');
grid on;

% 4. Second mixing stage (downconvert to baseband)
lo2 = cos(2*pi*fi*t2);
m2 = x2 .* (2*lo2);

% Plot spectrum after Mixer2
Nm2 = length(m2);
Xm2 = fftshift(fft(m2));
fm2 = (-Nm2/2:Nm2/2-1)*(Fs2/Nm2);
figure;
plot(fm2, abs(Xm2));
xlabel('Frequency (Hz)');
ylabel('Magnitude');
title('Spectrum of Mixer2 Output');
grid on;

% 5. Baseband lowpass filter (high-order)
lp_bb = fir1(400, BW/(Fs2/2));
bb = filter(lp_bb, 1, m2);

% Plot spectrum after Baseband LPF
Nbb = length(bb);
Xbb = fftshift(fft(bb));
fbb = (-Nbb/2:Nbb/2-1)*(Fs2/Nbb);
figure;
plot(fbb, abs(Xbb));
xlabel('Frequency (Hz)');
ylabel('Magnitude');
title('Spectrum of After Filter3 (Resampled)');
grid on;

% 6. Downsample to audio sampling rate (10 kHz)
decimFactor = round(Fs2 / 1e4);
audio = decimate(bb, decimFactor);
fs_audio = 1e4;

% Normalize output audio
audio = audio / max(abs(audio));

% 7. Play the demodulated audio
soundsc(audio, fs_audio);

% Display max value for verification
disp(['Demodulated signal max: ', num2str(max(audio))]);
