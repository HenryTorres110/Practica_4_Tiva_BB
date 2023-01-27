%% Conexión al Puerto 
clear all; 
puerto = input("A qué puerto deseas conectarte? ", "s"); 
baud_rate = input("Baud rate: "); 
s = serialport(puerto, baud_rate); 
comenzar = input("Desea empezar a leer? ", "s");
samples = 10000;

% Vectores de Almacenamiento de datos del ADC
vector_de_datos = cell(1, 6); % Usamos por 3 porque haremos 3 lecturas
for ii=1:6
    vector_de_datos{ii} = zeros(1, samples);
end

% Lectura 
canal = 1;
ith_entry = 1;

% Figura
figure("Name", "Voltaje de ADC");
title("ADC", "Interpreter", "latex", "FontSize", 16);
xlabel("Time [t]",'Interpreter', 'latex', 'FontSize',12);
ylabel("Voltage [V]", "Interpreter", "latex", "FontSize", 12);
grid on; 
hold on;
time = 1:1:samples;
ylim([0 3.5]);
xlim([0 samples]);
counter = 1;

adc_0 = animatedline('Color', 'r');
adc_1 = animatedline('Color', 'g');
adc_2 = animatedline('Color', 'b');
adc_3 = animatedline('Color', 'c');
adc_8 = animatedline('Color', 'm'); 
adc_b = animatedline('Color', 'y');

legend("Channel 0", "Channel 1", "Channel 2", "Channel 3", "Channel 8", "Channel B");

while true
    vector_de_datos{1}(ith_entry) = str2double(readline(s));
    vector_de_datos{2}(ith_entry) = str2double(readline(s));
    vector_de_datos{3}(ith_entry) = str2double(readline(s));
    vector_de_datos{4}(ith_entry) = str2double(readline(s));
    vector_de_datos{5}(ith_entry) = str2double(readline(s));
    vector_de_datos{6}(ith_entry) = str2double(readline(s));


    voltage_adc_0 = (vector_de_datos{1}(ith_entry) * 3.3)/ 4095;
    voltage_adc_1 = (vector_de_datos{2}(ith_entry) * 3.3)/ 4095;
    voltage_adc_2 = (vector_de_datos{3}(ith_entry) * 3.3)/ 4095;
    voltage_adc_3 = (vector_de_datos{4}(ith_entry) * 3.3)/ 4095;
    voltage_adc_8 = (vector_de_datos{5}(ith_entry) * 3.3)/ 4095;
    voltage_adc_b = (vector_de_datos{6}(ith_entry) * 3.3)/ 4095;

    addpoints(adc_0, time(ith_entry), voltage_adc_0);
    addpoints(adc_1, time(ith_entry), voltage_adc_1);
    addpoints(adc_2, time(ith_entry), voltage_adc_2); 
    addpoints(adc_3, time(ith_entry), voltage_adc_3);
    addpoints(adc_8, time(ith_entry), voltage_adc_8);
    addpoints(adc_b, time(ith_entry), voltage_adc_b); 
    drawnow

    ith_entry = ith_entry + 1;
    if ith_entry == samples
        break
    end
end
