clear; clc; close all;
%% --- Q3-a: Theoretical FM Spectrum (β=3)
fs = 1e7; fc = 5e5; fm = 1e4; beta = 3;
N_bessel = ceil(beta + 5);
n = -N_bessel:N_bessel;
Jn = besselj(n, beta);
f_theo = fc + n * fm;

fprintf('n\tf (Hz)\tJ_n(beta)\n');
for k = find(abs(Jn) > 1e-3)
    fprintf('%d\t%.1f\t%.4f\n', n(k), f_theo(k), Jn(k));
end

figure;
stem(f_theo, Jn, 'filled');
xlabel('Frequency (Hz)');
ylabel('Amplitude');
title('Q3-a: Theoretical FM Spectrum');

%% --- Q3-b: Generate FM Signal
duration = 3e-4;
t = 0:1/fs:duration;
x_fm = cos(2*pi*fc*t + beta*sin(2*pi*fm*t));

figure;
plot(t, x_fm);
xlabel('Time (s)');
ylabel('Amplitude');
title('Q3-c: Frequency Modulated Signal (β=3) for 0.0003 s');

%% --- Q3-c: Spectrum Analysis
Nfft = length(x_fm);
X = fftshift(fft(x_fm)) / Nfft;
f_shift = (-Nfft/2:Nfft/2-1) * (fs/Nfft);

figure;
plot(f_shift, abs(X));
xlabel('Frequency (Hz)');
ylabel('Magnitude');
title('Q3-c: Magnitude Spectrum of x_{FM}(t), β=3');
xlim([-1e6, 1e6]);
grid on;


%% --- Q3-d: Verify Spectrum Peaks and Compare with Theory
[~, idxs] = sort(abs(X), 'descend');
fprintf('Top 5 numerical spectral lines:\n');
for k = 1:5
    fprintf('f=%.0f Hz, |X|=%.4f\n', f_shift(idxs(k)), abs(X(idxs(k))));
end

% Theoretical sideband locations based on Bessel coefficients
n_theory = -2:2;  % Orders -2, -1, 0, 1, 2
Jn_theory = besselj(n_theory, beta);
f_theory = fc + n_theory * fm;

fprintf('Theoretical spectral components:\n');
for k = 1:length(n_theory)
    fprintf('Theoretical: f = %.0f Hz, J_%d(β)=%.4f\n', f_theory(k), n_theory(k), Jn_theory(k));
end


%% --- Q3-e: Differentiate and Extract Envelope
dx_fm = gradient(x_fm, 1/fs);
env = abs(hilbert(dx_fm));

figure;
plot(t, dx_fm); hold on; plot(t, env, 'r--');
xlabel('Time (s)');
ylabel('Amplitude');
title('Q3-e: Derivative and Envelope');
legend('Derivative', 'Envelope');

% --- Q3-f: Hard Limiter Implementation
x_hard = x_fm;
x_hard(x_hard > 0.1) = 0.1;
x_hard(x_hard < -0.1) = -0.1;

figure;
plot(t(1:500), x_fm(1:500), 'b-', t(1:500), x_hard(1:500), 'r--');
xlabel('Time (s)');
ylabel('Amplitude');
title('Q3-f: Zoomed Comparison: Original vs. ±0.1 Hard Limiterd');
legend('Original', 'Hard-Limited');

%% --- Q3-g: Spectrum of Hard-Limited Signal ---
fs = 1e7;           % Sampling frequency
fc = 5e5;           % Carrier frequency
fm = 1e4;           % Modulating frequency
beta = 3;           % Modulation index
duration = 3e-4;
t = 0:1/fs:duration;

% Generate FM signal
x_fm = cos(2*pi*fc*t + beta*sin(2*pi*fm*t));

% Apply hard limiter (±0.1 clipping)
x_hard = max(min(x_fm, 0.1), -0.1);

% Perform FFT with high resolution
Nfft = 4 * 2^nextpow2(length(x_hard));  % Increase FFT resolution
Xh = fftshift(fft(x_hard, Nfft)) / Nfft;
f_shift = (-Nfft/2:Nfft/2-1) * (fs/Nfft);

% Plot the spectrum (observe harmonics within ±5 MHz)
figure;
plot(f_shift, abs(Xh));
xlabel('Frequency (Hz)');
ylabel('Magnitude');
title('Q3-g: Spectrum of Hard-Limited Signal');
xlim([-5e6, 5e6]);
grid on;

%% --- Q3-h: Bandpass Filtering and Spectrum Verification ---
% Design a high-order Butterworth bandpass filter
filt_order = 8;
BW = 2 * (beta + 1) * fm; % Carson’s Rule: bandwidth ≈ ±(β+1)*fm = ±40 kHz
Wn = [(fc - BW) / (fs/2), (fc + BW) / (fs/2)];
[b, a] = butter(filt_order, Wn);

% Apply zero-phase filtering to avoid phase distortion
x_bp = filtfilt(b, a, x_hard);
x_bp = x_bp / max(abs(x_bp)); % Normalize amplitude

% FFT analysis after bandpass filtering
Y_bp = fftshift(fft(x_bp, Nfft)) / Nfft;
f_bp = (-Nfft/2:Nfft/2-1) * (fs/Nfft);

% Time-domain comparison between original FM and bandpass-filtered signal
figure;
subplot(2,1,1);
plot(t(1:500), x_fm(1:500));
title('Q3-h: Original FM Signal (Zoomed)');
xlabel('Time (s)');
ylabel('Amplitude');
grid on;

subplot(2,1,2);
plot(t(1:500), x_bp(1:500));
title('Q3-h: Bandpass-Filtered Signal (Zoomed)');
xlabel('Time (s)');
ylabel('Amplitude');
grid on;

% Full spectrum plot after bandpass filtering
figure;
plot(f_bp, abs(Y_bp));
title('Q3-h: FFT after Bandpass Filtering');
xlabel('Frequency (Hz)');
ylabel('Magnitude');
xlim([-5e6, 5e6]);
grid on;
