%{  
// Copyright (C) Junio 2009 <Ing. Gabriel Pool>

// Este programa es software libre. Puede redistribuirlo y/o modificarlo bajo 
// los t�rminos de la Licencia P�blica General de GNU seg�n es publicada 
// por la Free Software Foundation, bien de la versi�n 2 de dicha Licencia 
// o bien �seg�n su elecci�n� de cualquier versi�n posterior. 

// Este programa se distribuye con la esperanza de que sea �til, 
// pero SIN NINGUNA GARANT�A, incluso sin la garant�a MERCANTIL impl�cita 
// o sin garantizar la CONVENIENCIA PARA UN PROP�SITO PARTICULAR. Para m�s 
// detalles, v�ase la Licencia P�blica General de GNU.

%}

% Este programa se limita a incrementar dato_out (0), enviar el vector 
% de 64 Bytes al PIC y mostrar el vector que nos envia de vuelta el PIC
% espec�ficamente dato_in(0) en la l�nea de comandos de matlab

clear all;
close all;
loadlibrary mpusbapi _mpusbapi.h alias libreria 
% Los archivos _mpusbapi.c y mpusbapi.dll deben de estar en la misma
% carpeta de trabajo y se obtienen de la descarga del driver en la 
% pagina de microchip ("Microchip MCHPFSUSB v2.4 Installer.zip"),
% al instalarse queda ubicado en X:\Microchip Solutions\USB
% Tools\MCHPUSB Custom Driver\Mpusbapi\Dll\Borland_C, en caso de descargar
% una version de driver m�s reciente, reemplace �stos archivos por los m�s
% nuevos.

%libisloaded libreria               % Confirma que la librer�a ha sido
                                    % cargada
%libfunctions('libreria', '-full')  % Muestra en la l�nea de comandos las
                                    % funciones de la librer�a
%libfunctionsview libreria          % Muestra en un cuadro lo mismo que la
                                    % instrucci�n anterior

data_in = eye(1,64,'uint8');       % Se declara el vector de datos de entrada (el que se recibe del PIC)
data_out = eye(1,64,'uint8');      % Se declara el vector de datos de salida (el que se envia al PIC)
                                   % TODOS LOS DATOS SE DECLARAN COMO
                                   % UINT8 de lo contrario no hay
                                   % comunicaci�n.
                                    
vid_pid_norm = libpointer('int8Ptr',[uint8('vid_04d8&pid_000b') 0]); 
out_pipe = libpointer('int8Ptr',[uint8('\MCHP_EP1') 0]); 
in_pipe = libpointer('int8Ptr',[uint8('\MCHP_EP1') 0]); 

%calllib('libreria','MPUSBGetDLLVersion');
[conectado] = calllib('libreria','MPUSBGetDeviceCount',vid_pid_norm)


if conectado == 1   % Es importante seguir �sta secuencia para comunicarse con el PIC:
                    % 1. Abrir tuneles, 2. Enviar/Recibir dato
                    % 3. Cerrar tuneles

    [my_out_pipe] = calllib('libreria', 'MPUSBOpen',uint8 (0), vid_pid_norm, out_pipe, uint8(0), uint8 (0)); % Se abre el tunel de envio
    [my_in_pipe] = calllib('libreria', 'MPUSBOpen',uint8 (0), vid_pid_norm, in_pipe, uint8 (1), uint8 (0)); % Se abre el tunel de recepci�n

    while (data_out (1) <= 254)     
    % En caso de tener problemas de transmisi�n y recepci�n incremente 
    % Receive_delay_ms y SendDelay_ms (son los �ltimos par�metros de 
    % MPUSBWrite y MPUSBRead) hasta obtener mejores resultados
    calllib('libreria', 'MPUSBWrite',my_out_pipe, data_out, uint8(64), uint8(64), uint8(10)); % Se envia el dato al PIC
    [aa,bb,data_in,dd] = calllib('libreria', 'MPUSBRead',my_in_pipe, data_in, uint8(64), uint8(64), uint8(10)); % Se recibe el dato que envia el PIC
    data_out (1) = data_out (1)+ 1;     % Se incrementa el primer dato del vector que se envia
    data_in(1)                          % Se muestra el primer valor del vector recibido
    %pause (0.1);   % En caso de que se desee ver la operaci�n m�s lenta
    end
    calllib('libreria', 'MPUSBClose', my_in_pipe);  % Se cierra el tunel de recepci�n
    calllib('libreria', 'MPUSBClose', my_out_pipe); % Se cierra el tunel de envio
end
unloadlibrary libreria      % Importante descargar la librer�a de memoria, de lo contrario genera errores
close all
clear all
