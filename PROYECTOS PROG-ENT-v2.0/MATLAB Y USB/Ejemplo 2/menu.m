


function varargout = menu(varargin)
% Esto se ejecuta cada vez que se interactua con el menu
% MENU M-file for menu.fig
%      MENU, by itself, creates a new MENU or raises the existing
%      singleton*.
%
%      H = MENU returns the handle to a new MENU or the handle to
%      the existing singleton*.
%
%      MENU('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in MENU.M with the given input arguments.
%
%      MENU('Property','Value',...) creates a new MENU or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before menu_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to menu_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help menu

% Last Modified by GUIDE v2.5 22-Feb-2010 12:35:56

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @menu_OpeningFcn, ...
                   'gui_OutputFcn',  @menu_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT
end

% --- Executes just before menu is made visible.
% S?lo se ejecuta al inicio
function menu_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to menu (see VARARGIN)

global t data_in data_out vid_pid_norm out_pipe in_pipe conectado my_in_pipe my_out_pipe handles1

handles1 = handles;
% Choose default command line output for menu
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes menu wait for user response (see UIRESUME)
% uiwait(handles.figure1);


conectado = 0;

data_in = eye(1,64,'uint8');       % Se declara el vector de datos de entrada (el que se recibe del PIC)
data_out = eye(1,64,'uint8');      % Se declara el vector de datos de salida (el que se envia al PIC)
                                   % TODOS LOS DATOS SE DECLARAN COMO
                                   % UINT8 de lo contrario no hay
                                   % comunicaci?n.
                                    
vid_pid_norm = libpointer('int8Ptr',[uint8('vid_04d8&pid_000b') 0]); 
out_pipe = libpointer('int8Ptr',[uint8('\MCHP_EP1') 0]); 
in_pipe = libpointer('int8Ptr',[uint8('\MCHP_EP1') 0]); 

%SE DECLARA LA RUTINA QUE DEBE DE EJECUTARSE AL CERRAR LA APLICACI?N
set(handles.figure1,'CloseRequestFcn',@closeGUI);
%CREAMOS EL OBJETO TIMER Y SE ARRANCA
t = timer('TimerFcn',@tiempo, 'ExecutionMode', 'fixedSpacing' ,'BusyMode', 'queue' ,'Period', 0.25);
start (t);

loadlibrary mpusbapi _mpusbapi.h alias libreria 
% Los archivos _mpusbapi.c y mpusbapi.dll deben de estar en la misma
% carpeta de trabajo y se obtienen de la descarga del driver en la 
% pagina de microchip ("Microchip MCHPFSUSB v2.4 Installer.zip"),
% al instalarse queda ubicado en X:\Microchip Solutions\USB
% Tools\MCHPUSB Custom Driver\Mpusbapi\Dll\Borland_C, en caso de descargar
% una version de driver m?s reciente, reemplace ?stos archivos por los m?s
% nuevos.

%libisloaded libreria               % Confirma que la librer?a ha sido
                                    % cargada
%libfunctions('libreria', '-full')  % Muestra en la l?nea de comandos las
                                    % funciones de la librer?a
%libfunctionsview libreria          % Muestra en un cuadro lo mismo que la
                                    % instrucci?n anterior

%calllib('libreria','MPUSBGetDLLVersion');

while (conectado == 0)
    [conectado] = calllib('libreria','MPUSBGetDeviceCount',vid_pid_norm);
    if (conectado ==0)
        selection = questdlg('La tarjeta de evaluaci?n no se encuentra',...
                        'Tarjeta no encontrada',...
                        'Buscar de nuevo','Cancelar','Cancelar');
        switch selection,
            case 'Cancelar',
                stop (t);
                return
            case 'Buscar de nuevo'
                conectado = 0;
        end
    end
end
if conectado == 1   % Es importante seguir ?sta secuencia para comunicarse con el PIC:
                    % 1. Abrir tuneles, 2. Enviar/Recibir dato
                    % 3. Cerrar tuneles

    [my_out_pipe] = calllib('libreria', 'MPUSBOpen',uint8 (0), vid_pid_norm, out_pipe, uint8(0), uint8 (0)); % Se abre el tunel de envio
    [my_in_pipe] = calllib('libreria', 'MPUSBOpen',uint8 (0), vid_pid_norm, in_pipe, uint8 (1), uint8 (0)); % Se abre el tunel de recepci?n
end
end

% --- Outputs from this function are returned to the command line.
function varargout = menu_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;
end

% --- Executes on button press in radiobutton1.
function radiobutton1_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hint: get(hObject,'Value') returns toggle state of radiobutton1
end
% --- Executes on button press in radiobutton2.
function radiobutton2_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hint: get(hObject,'Value') returns toggle state of radiobutton2
end

% --- Executes on button press in radiobutton3.
function radiobutton3_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hint: get(hObject,'Value') returns toggle state of radiobutton3
end

% --- Executes on button press in radiobutton4.
function radiobutton4_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hint: get(hObject,'Value') returns toggle state of radiobutton4
end

% --- Executes on button press in radiobutton5.
function radiobutton5_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hint: get(hObject,'Value') returns toggle state of radiobutton5
end

% --- Executes on button press in radiobutton6.
function radiobutton6_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hint: get(hObject,'Value') returns toggle state of radiobutton6
end

% --- Executes on button press in radiobutton7.
function radiobutton7_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hint: get(hObject,'Value') returns toggle state of radiobutton7
end

% --- Executes on button press in radiobutton8.
function radiobutton8_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hint: get(hObject,'Value') returns toggle state of radiobutton8
end

% --- Executes on button press in checkbox1.
function checkbox1_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hint: get(hObject,'Value') returns toggle state of checkbox1
end

% --- Executes on button press in checkbox2.
function checkbox2_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox2
end

% --- Executes on button press in checkbox3.
function checkbox3_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox3
end

% --- Executes on button press in checkbox4.
function checkbox4_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox4
end

% --- Executes on button press in checkbox5.
function checkbox5_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox5
end

% --- Executes during object creation, after setting all properties.
function text2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to text2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
end


function closeGUI(source,eventdata)
%src is the handle of the object generating the callback (the source of the event)
%evnt is the The event data structure (can be empty for some callbacks)
global t my_in_pipe my_out_pipe conectado
selection = questdlg('Desea cerrar la aplicaci?n?',...
                     'Confirmaci?n',...
                     'Si','No','Si');
switch selection,
   case 'Si',
     stop (t);
     if conectado == 1
        calllib('libreria', 'MPUSBClose', my_in_pipe);  % Se cierra el tunel de recepci?n
        calllib('libreria', 'MPUSBClose', my_out_pipe); % Se cierra el tunel de envio
     end
     unloadlibrary libreria      % Importante descargar la librer?a de memoria, de lo contrario genera errores
     delete(gcf)
     close all
     clear all
   case 'No'
     return
end
 end

 %TIMER EMPIEZA A REALIZAR TAREA ASIGNADA
function tiempo(hObject, eventdata) %(source,eventdata)
 
global conectado my_out_pipe my_in_pipe data_in data_out handles1
int16 data;
%a = a + 1
if conectado == 1
    calllib('libreria', 'MPUSBWrite',my_out_pipe, data_out, uint8(64), uint8(64), uint8(200)); % Se envia el dato al PIC
    [aa,bb,data_in,dd] = calllib('libreria', 'MPUSBRead',my_in_pipe, data_in, uint8(64), uint8(64), uint8(200)); % Se recibe el dato que envia el PIC
    %data_out (1) = data_out (1)+ 1;     % Se incrementa el primer dato del vector que se envia
    %data_in(1)                          % Se muestra el primer valor del vector recibido
end

%Se actualizan los datos que el PIC nos envia en la interfaz de usuario.
% Se recibe un n?mero binario procedente del PIC, se analiza bit a bit y se
% activa/desactiva el checkbox correspondiente en la interfaz de usuario.
i=2;
while (i<7)
if (bitget(data_in(2), i) == 1)
    set(handles1.(strcat('checkbox',int2str(i-1))),'value',0);
else
    set(handles1.(strcat('checkbox',int2str(i-1))),'value',1);
end
i = i + 1;
end

% Se actualizan los datos que se envia al PIC y que son modificados desde la interfaz de usuario.
% Se genera un n?mero binario de 8 bit de acuerdo a la combinaci?n de los
% botones seleccionados
i = 1;
while (i<9)
Hint=get(handles1.(strcat('radiobutton',int2str(i))),'value'); %returns toggle state of radiobutton
if (Hint==1)
    data_out(1) = bitor(data_out(1), uint8(2 ^ (i-1)));
else
    %El byte 0 se le aplica un complemento a 1 de 2^7
    data_out(1) = bitand(data_out(1), bitcmp(uint8(2^(i-1)))); 
end
i = i + 1;
end

% Se actualiza la lectura anal?gica en el cuadro de texto

data = (uint16(data_in(4)) * uint16(256)) + uint16(data_in(3));
set(handles1.text2,'String',(num2str(data)));
end
 


