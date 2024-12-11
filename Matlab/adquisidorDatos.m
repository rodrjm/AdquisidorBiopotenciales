%%Funcion ECG
close all;
clc;
muestras=1000; %numero de muestras
muestra_actual=uint32(zeros(1,4));
matriz_muestras=uint32(zeros(muestras,4));
ECG=zeros(1,muestras,'double');
Fs=1000;                          
T=1/Fs; 
L=muestras; 
t=(0:L-1)*T; 
LSB = (2.4) / (2^24);
LSB_W = (2.4) / ((2^23) - 1);
% SERIAL
delete(instrfind({'port'},{'COM4'})); %borrar datos previos
puerto=serial('COM4'); %declaración del pierto serie
puerto.BaudRate=3150000; %velocidad de transmision de datos
set(puerto,'StopBits',1);
set(puerto,'DataBits',8);
set(puerto,'Parity','none');
set(puerto,'Timeout',0.001);
set(puerto,'RequestToSend','off');
set(puerto, 'InputBufferSize', 240000); % Ajusta según la cantidad de datos esperada
fopen(puerto); %abre el puerto COM

% SERIAL PORT
%puerto = serialport('COM4', 3150000, 'Parity', 'none', 'DataBits', 8, 'StopBits', 1, 'Timeout', 0.001);
%flush(puerto); % Borrar datos previos

contador=1; %inicializa contador
%Grafica de la trasmisión el ECG
figure("Name","Grafica voltaje");
hPlot = plot(t, ECG, 'b'); % Inicializa la gráfica con datos en cero
title("Transmision del ECG");
xlabel("Tiempo (s)");
ylabel("Volataje (V)");
grid on;
%ylim([-1,0.001]);
hold on;
%Ciclo para la toma de muestras
while contador<=muestras
   try 
        if contador > 100
            xlim([(contador-1000)*T, contador*T]);
            drawnow;
        end
        %muestra_actual(:)=fread(puerto,1,'uint32');
        muestra_actual(:)=fread(puerto,4,'uint8');
        %muestra_actual(:)=read(puerto,4,'uint8'); % SE USA CON SERIALPORT
        matriz_muestras(contador,:)=muestra_actual;
        disp(['Muestra actual: ', num2str(muestra_actual)]); 
        %valor_ecg = matriz_muestras(contador,1);
        valor_ecg = matriz_muestras(contador,1)*2^0 + matriz_muestras(contador,2)*2^8 + matriz_muestras(contador,3)*2^16 + matriz_muestras(contador,4)*2^24;
        disp(['Valor ECG: ', num2str(valor_ecg)]);
        % Convertir a decimal con signo
        if (matriz_muestras(contador,4) && 0x800000)  % Si el bit más significativo es 
            valor_ecg = double(valor_ecg)-2^32;
            %disp(['Pasado a negativo: ', num2str(valor_ecg)]);
        end
        % Convertir a voltaje usando el LSB
        ECG(contador) = double(valor_ecg) * double(LSB);
        %disp(['Valor a graficar: ', num2str(ECG(contador))]);
        % Actualizar la gráfica con los puntos hasta ahora
        tiempo_actual = (0:contador-1) * T; % Generar el tiempo acumulado hasta ahora
        set(hPlot, 'XData', tiempo_actual, 'YData', ECG(1:contador)); % Actualizar gráfica
        % Ajustar dinámicamente ylim basado en los valores actuales del ECG
        min_val = min(ECG(1:contador));
        max_val = max(ECG(1:contador));
        ylim([min_val - 0.01, max_val + 0.01]);
        %drawnow;
        contador=contador+1;
        if contador > muestras
            contador=1;
        end
    catch ME
        %disp(['Estoy ACA: ', num2str(contador)]);
        pause(0.1); % Pausa breve para intentar reanudar
    end
end
%fclose(puerto); %Cierra el puerto
delete(puerto);
%pan_tompkin(ECG,1000,1);