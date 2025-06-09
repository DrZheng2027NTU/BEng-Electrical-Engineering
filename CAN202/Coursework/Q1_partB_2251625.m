clear; clc; close all;
%% --- Q1-m: Generate high-quality sawtooth carrier ---
% Carrier frequency (500 kHz)
fc = 500e3;                   

% Number of cycles to simulate
N_cycles = 25;                

% High sampling rate
Fs_m = 20e6;                  
Ts = 1 / Fs_m;

% Total duration
T_total = N_cycles / fc;      
t = 0 : Ts : T_total;

% Generate sawtooth wave
saw_wave = sawtooth(2 * pi * fc * t);

% Bandpass filter to extract cleaner carrier (±10 kHz)
passband = [fc - 10e3, fc + 10e3];  
saw_filtered = bandpass(saw_wave, passband, Fs_m);

% Plot original and filtered sawtooth
figure;
subplot(2,1,1);
plot(t, saw_wave);
title(['Original Sawtooth Wave — ' num2str(N_cycles) ' Cycles']);
xlabel('Time (s)');
ylabel('Amplitude');

subplot(2,1,2);
plot(t, saw_filtered);
title(['Filtered Signal (Extracted Carrier) — ' num2str(N_cycles) ' Cycles']);
xlabel('Time (s)');
ylabel('Amplitude');

%% --- Q1-n: Re-modulate the Handel sample ---
load handel;
Fs = 8192;

% Compute new sampling rate
Fs_new = ceil((Fs/2 + fc) / Fs * 2) * Fs;
[p, q] = rat(Fs_new / Fs, 1e-6);
y_resampled = resample(y, p, q);
t_carrier = (0:length(y_resampled)-1) / Fs_new;

% Interpolate carrier to match length
carrier = interp1(t, saw_filtered, t_carrier, 'linear', 'extrap')';

% AM modulation
y_dsb_sc_saw = y_resampled .* carrier;

% plot modulated waveform
figure;
plot(t_carrier, y_dsb_sc_saw);
title('AM modulated waveform (DSB-SC Saw)');
xlabel('Time (s)');
ylabel('Amplitude');
xlim([0, 100000/fc]);
grid on;


%% --- Q1-o: Demodulate the signal ---
y_demod_pre_saw = y_dsb_sc_saw .* carrier;

% High-quality low-pass filtering
f_cutoff = 5e3;
y_rec_saw = lowpass(y_demod_pre_saw, f_cutoff, Fs_new, 'Steepness', 0.98);

% Plot spectrum of recovered baseband
Nfft = 2^nextpow2(length(y_rec_saw));
f_axis = linspace(-Fs_new/2, Fs_new/2, Nfft);
M = fftshift(fft(y_rec_saw, Nfft));

figure;
subplot(2,1,1);
plot(f_axis / 1e3, abs(M));
xlabel('Frequency (kHz)');
ylabel('Magnitude');
title('Recovered Baseband Spectrum');
xlim([-6 6]);
grid on;


%% --- Q1-p: Playback recovered signal using audioplayer ---
Fs_org = 8192;
[p, q] = rat(Fs_org / Fs_new, 1e-6);
y_recovered = resample(y_rec_saw, p, q);

% Normalize to avoid clipping
y_recovered = y_recovered / max(abs(y_recovered));

% Create player object and play
player = audioplayer(y_recovered, Fs_org);
play(player);
