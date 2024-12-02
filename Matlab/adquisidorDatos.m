%%Funcion ECG
close all;
clc;
muestras=1000; %numero de muestras
muestra_actual=int32(zeros(1,4));
matriz_muestras=int32(zeros(muestras,4));
ECG=zeros(1,muestras,'int32');
LSB = (2 * 2.4) / (2^24);
delete(instrfind({'port'},{'COM11'})); %borrar datos previos
puerto=serial('COM11'); %declaración del pierto serie
puerto.BaudRate=980000; %velocidad de transmision de datos
set(puerto,'StopBits',1);
set(puerto,'DataBits',8);
set(puerto,'Parity','none');
set(puerto,'Timeout',1);
set(puerto,'RequestToSend','off');
fopen(puerto); %abre el puerto COM
contador=1; %inicializa contador

%Grafica de la trasmisión el ECG
figure("Name","Grafica voltaje");
title("Transmision del ECG");
xlabel("Numero de muestras");
ylabel("Volataje (V)");
grid off;
hold on;
ylim([-1,1.5]);
%Ciclo para la toma de muestras
while contador<=muestras
    if muestras <= 50
        xlim([0,contador+5]);
    else
        xlim([contador-50,contador+5]);
    end
    muestra_actual(:)=fread(puerto,4,'uint8');
    matriz_muestras(contador,:)=muestra_actual;
    valor_ecg = matriz_muestras(contador,1)*2^0 + matriz_muestras(contador,2)*2^8 + matriz_muestras(contador,3)*2^16 + matriz_muestras(contador,4)*2^24;
    disp(['El valores: ', num2str(muestra_actual)]);
    disp(['El valores: ', num2str(valor_ecg)]);
    %if(bitget(valor_ecg,24)==1)
      %  valor_ecg=bitor(int32(valor_ecg),val_neg);
    %end

    ECG(contador) = valor_ecg;

    %ECGV=(ECG*ADCres)*10^(6);
    ECGV = (ECG * LSB);
    plot(ECGV);
    drawnow;
    contador=contador+1;
end
fclose(puerto); %Cierra el puerto
delete(puerto);
%pan_tompkin(ECG,1000,1);