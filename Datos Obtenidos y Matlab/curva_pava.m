% Abrir archivo
fid = fopen('/home/santiago/Documentos/PlatformIO/Projects/Control_Avanzado_I/Datos Obtenidos y Matlab/curva_octave.csv', 'r');

% Leer dos columnas numéricas separadas por coma
data = textscan(fid, '%f%f', 'Delimiter', ';');

% Cerrar archivo
fclose(fid);

% Extraer columnas
tiempo = data{1};
temperatura = data{2};

% Graficar
figure(1);
plot(tiempo, temperatura, 'b-o');
xlabel('Tiempo [s]');
ylabel('Temperatura [°C]');
title('Curva térmica');
axis([0 1500 20 90]);
grid on;

pkg load optim;  % Activar el paquete optim

modelo = @(b, t) b(1) + b(2) * (1 - exp(-t / b(3)));  % T0 + K*(1 - exp(-t/tau))
b0 = [min(temperatura), max(temperatura)-min(temperatura), 200];  % [T0, K, tau]

bajuste = lsqcurvefit(modelo, b0, tiempo, temperatura);

figure(1);
plot(tiempo, temperatura, 'b', 'LineWidth', 1.5); hold on;
plot(tiempo, modelo(bajuste, tiempo), 'r--', 'LineWidth', 2);
legend('Datos reales', 'Modelo ajustado', 'location', 'southeast');
xlabel('Tiempo [s]');
ylabel('Temperatura [°C]');
title('Ajuste térmico con lsqcurvefit');
grid on;

fprintf('T0 = %.2f °C\n', bajuste(1));
fprintf('K  = %.2f °C\n', bajuste(2));
fprintf('Tau = %.2f s\n', bajuste(3));

pkg load control
s = tf('s');
% a = bajuste(2)/70;
a = 94/70;
tau = bajuste(3);
G = (a / tau) / (s + 1 / tau)

h = a/tau;
fprintf('%.2f', h);

figure(2)
[y,x] = step(70*G);
plot(tiempo, temperatura);
hold on;
plot(x,y);
