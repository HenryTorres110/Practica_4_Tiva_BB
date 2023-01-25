%% Conexión al Puerto 
clear all; 
puerto = input("A qué puerto deseas conectarte? ", "s"); 
baud_rate = input("Baud rate: "); 
s = serialport(puerto, baud_rate); 
comenzar = input("Desea empezar a leer? ", "s");

% Vectores de Almacenamiento de datos del ADC
vector_de_datos = cell(1, 3); % Usamos por 3 porque haremos 3 lecturas
vector_de_datos{1} = zeros(1,10000);
vector_de_datos{2} = zeros(1,10000); 
vector_de_datos{3} = zeros(1,10000);

% Lectura 
canal = 1;
ith_entry = 1;

while strcmp(comenzar, "si")
   lectura = readline(s); 
   vector_de_datos{canal}(ith_entry) = lectura;
   canal = canal + 1;
   if canal > 3
       canal = 1;
       ith_entry = ith_entry + 1;
   end
   if ith_entry == 10000
       ith_entry = 1;
       break;
   end
end
plot(1:1:10000, vector_de_datos{1}, 'b*');
