
    % Leer datos desde el archivo generado por Python
    data = load('datos.txt');

    n = data(:,1);
    ne = data(:,2);
    en = data(:,3);

    % Graficar
    figure;
    plot(n, ne, 'b', 'DisplayName', 'ne');
    hold on;
    plot(n, en, 'r--', 'DisplayName', 'e^n');
    hold off;

    xlabel('n');
    ylabel('Valor de las funciones');
    title('Comparación de ne y e^n');
    legend;
    grid on;
    