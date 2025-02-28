% Cargar datos desde el archivo generado por Python
data = load('datos.txt');

n = data(:, 1);      % Valores de n
ne = data(:, 2);     % Valores de ne
en = data(:, 3);     % Valores de e^n

% Crear una nueva figura
figure;

% Graficar ne (definida para todo n)
plot(n, ne, 'b', 'LineWidth', 2, 'DisplayName', 'ne');
hold on;

% Graficar e^n solo para n >= 0 (ya que e^n no está definida para n < 0 en números reales)
valid_indices = ~isnan(en);  % Ignorar valores NaN
plot(n(valid_indices), en(valid_indices), 'r--', 'LineWidth', 2, 'DisplayName', 'e^n');

% Configurar los límites de los ejes
xlim([-10, 10]);  % Rango de x desde -10 hasta 10
ylim([-10, 10]);  % Rango de y desde -10 hasta 10

% Etiquetas y título
xlabel('n');
ylabel('Valor de las funciones');
title('Comparación de ne y e^n');

% Leyenda
legend;

% Cuadrícula
grid on;

% Mantener la figura abierta
hold off;
disp('Presione una tecla para cerrar MATLAB...');
pause;