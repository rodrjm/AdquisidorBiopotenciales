%%Funcion ECG
close all;
clc;
voltaje=0; %guarda los datos
muestras=1000; %numero de muestras
delete(instrfind({'port'},{'COM7'})); %borrar datos previos
puerto=serial('COM7'); %declaración del pierto serie
puerto.BaudRate=980000; %velocidad de transmision de datos
fopen(puerto); %abre el puerto COM
contador=1; %inicializa contador

%Grafica de la trasmisión el ECG
figure("Name","Grafica voltaje")
title("Transmision del ECG");
xlabel("Numero de muestras");
ylabel("Volataje (V)");
grid off;
hold on;

%Ciclo para la toma de muestras
while contador<=muestras
    ylim([0,0.00007]);
    xlim([0,contador+5]);
    valorAdc=fscanf(puerto,'%b');
    print(valorAdc);
    voltaje(contador)=valorAdc(1)*(2.4/8388608); %Transformacion del ADC a voltaje
    plot(voltaje);
    drawnow;
    contador=contador+1;
end
fclose(puerto); %Cierra el puerto
delete(puerto);