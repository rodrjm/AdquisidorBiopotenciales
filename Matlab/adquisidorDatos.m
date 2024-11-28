%%Funcion ECG
close all;
clc;
voltaje=0; %guarda los datos
muestras=1000; %numero de muestras
muestra_actual=int32(zeros(1,9));
matriz_muestras=int32(zeros(muestras,9));
ECG=zeros(1,muestras,'int32');
val_neg=int32(-16777216);
ADCres=(2.4-(-2.4)/2^24); % 2^23 = 8388608
Fs=1000;
T=1/Fs;
L=muestras;
t=(0:L-1)*T;
ord=1000;
low=0.08;
bnd=[0.12 0.3];
a=fir1(1000,[0.07 0.13],'stop');
b=fir1(100,0.06,'low');
c=fir1(100,0.001,'high');
bW=fir1(ord,[low bnd],'DC-1');
delete(instrfind({'port'},{'COM4'})); %borrar datos previos
puerto=serial('COM4'); %declaración del pierto serie
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
ylim([-70000,70000]);

%Ciclo para la toma de muestras
while contador<=muestras
    xlim([0,contador+5]);
    muestra_actual(:)=fread(puerto,9,'uint8');
    matriz_muestras(contador,:)=muestra_actual;
    fwrite(puerto,1,'uint8');
    valor_ecg = matriz_muestras(contador,1)*2^16 + matriz_muestras(contador,2)*2^8 + matriz_muestras(contador,3)*2^0;
    if(bitget(valor_ecg,24)==1)
        valor_ecg=bitor(int32(valor_ecg),val_neg);
    end
    ECG(contador) = valor_ecg;
    ECG_f=filter(a,1,double(ECG(contador)));
    ECG_f1=filter(b,1,double(ECG_f));
    ECG_ff=fft(double(ECG_f1));
    P2_ECG=abs(ECG_ff/L);
    P1_ECG = P2_ECG(1:min(L/2+1, length(P2_ECG)));
    P1_ECG(2:end-1)=2*P1_ECG(2:end-1);
    f=Fs*(0:(L/2))/L;
    ECGV=(ECG*ADCres);
    plot(ECGV);
    drawnow;
    contador=contador+1;
end
fclose(puerto); %Cierra el puerto
delete(puerto);