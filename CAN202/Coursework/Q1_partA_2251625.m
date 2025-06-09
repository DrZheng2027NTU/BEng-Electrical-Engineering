clear; clc; close all;
%% Q1-a: Load and play the built-in Handel audio
load handel            % loads y (audio) and Fs (sampling rate = 8192 Hz)
player = audioplayer(y, Fs);
play(player);          % play the original audio

%% Q1-b: Determine maximum bandwidth under Nyquist criterion
maxBandwidth = Fs/2;   % half the sampling rate
disp(['Maximum signal bandwidth = ', num2str(maxBandwidth), ' Hz']);

%% Q1-c: Block diagram
% See report for block diagram showing DSB-SC AM transmitter and coherent detector.

%% Q1-d: Plot magnitude spectrum of the original signal
N    = length(y);
Y    = fftshift(fft(y));
f    = linspace(-Fs/2, Fs/2, N);    % frequency axis from -Fs/2 to +Fs/2
figure;
plot(f, abs(Y));
xlabel('Frequency (Hz)');
ylabel('Magnitude');
title('Magnitude Spectrum of Original Handel Signal');
grid on;

%% Q1-e: Compute new sampling rate to avoid aliasing around carrier
fc      = 5e5;                             % carrier = 5×10^5 Hz (last nonzero digit = 5)
Fs_new  = ceil((Fs/2 + fc)/Fs * 2) * Fs;   % ensure Fs_new > 2*(Fc + Fs/2)
disp(['New sampling rate Fs_new = ', num2str(Fs_new), ' Hz']);

%% Q1-f: Resample original audio to Fs_new
[p, q]       = rat(Fs_new / Fs, 1e-6);
y_resampled  = resample(y, p, q);

%% Q1-g: Plot spectrum of the resampled signal
N_res  = length(y_resampled);
Y_res  = fftshift(fft(y_resampled));
f_res  = linspace(-Fs_new/2, Fs_new/2, N_res);
figure;
plot(f_res, abs(Y_res));
xlabel('Frequency (Hz)');
ylabel('Magnitude');
title(['Spectrum of Resampled Signal (Fs\_new = ', num2str(Fs_new), ' Hz)']);
grid on;

%% Q1-h: Generate DSB-SC modulated signal
t_res       = (0:N_res-1)'/Fs_new;       % time vector
carrier     = cos(2*pi*fc*t_res);        % cosine carrier
modulated   = 2* y_resampled .* carrier;    % DSB-SC modulation

%% Q1-i: Plot spectrum of DSB-SC modulated signal
N_mod  = length(modulated);
Y_mod  = fftshift(fft(modulated));
f_mod  = linspace(-Fs_new/2, Fs_new/2, N_mod);
figure;
subplot(3,1,1);
plot(f_mod, abs(Y_mod));
xlim([fc-1e4, fc+1e4]);
xlabel('Frequency (Hz)'); ylabel('Magnitude');
title('Positive Sideband (+f_c)');
grid on;
subplot(3,1,2);
plot(f_mod, abs(Y_mod));
xlim([-fc-1e4, -fc+1e4]);
xlabel('Frequency (Hz)'); ylabel('Magnitude');
title('Negative Sideband (-f_c)');
grid on;
subplot(3,1,3);
plot(f_mod, abs(Y_mod));
xlim([-Fs_new/2, Fs_new/2]);
xlabel('Frequency (Hz)'); ylabel('Magnitude');
title('Full Spectrum of DSB-SC Signal');
grid on;

%% Q1-j: Multiply by carrier again for coherent detection
% To visualize ±2fc, first upsample by 2×
Fs2      = 2 * Fs_new;
[p2, q2] = rat(Fs2 / Fs_new, 1e-6);
mod2     = resample(modulated, p2, q2);
t2       = (0:length(mod2)-1)'/Fs2;
demod_pre= mod2 .* cos(2*pi*fc*t2);    % multiplication by carrier

% Plot spectrum before lowpass
N2    = length(demod_pre);
Y2    = fftshift(fft(demod_pre));
f2    = linspace(-Fs2/2, Fs2/2, N2);
figure;
plot(f2, abs(Y2));
xlabel('Frequency (Hz)');
ylabel('Magnitude');
title('Spectrum after Carrier Multiplication (Before LPF)');
grid on;

%% Q1-k: Apply lowpass filter to recover baseband and plot its spectrum
cutoff    = Fs/2;                      % cutoff at original Nyquist (4096 Hz)
recovered = lowpass(demod_pre, cutoff, Fs2);

% Compute spectrum of the filtered signal
N_rec = length(recovered);
Y_rec = fftshift(fft(recovered));
f_rec = linspace(-Fs2/2, Fs2/2, N_rec);

% Plot linear magnitude spectrum after LPF
figure;
plot(f_rec, abs(Y_rec));
xlabel('Frequency (Hz)');
ylabel('Magnitude');
title('Spectrum of Signal After Lowpass Filtering');
xlim([-cutoff*1.2, cutoff*1.2]);  % focus around baseband
grid on;


%% Q1-l: Downsample back to 8192 Hz and play recovered audio
[p3, q3]       = rat(Fs / Fs2, 1e-6);
recovered_down = resample(recovered, p3, q3);
sound(recovered_down, Fs);             % play the recovered audio
