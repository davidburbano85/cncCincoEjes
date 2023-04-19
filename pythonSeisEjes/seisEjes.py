from tkinter import*
import tkinter as tk 
import threading, serial,time
from ayuda import *
from variables import *
import variables as va


arduino= serial.Serial('COM3', 9600)
entrada_de_arduino=[]
arduino_pantalla=[]
diccionario=''

ventana= tk.Tk()
ventana.title('six axis machine CNC TT120')
ventana.geometry('1650x750')



# //////////////////////FRAMES////////////////////////////
 # ///////////////////////////////////////////////////

#estas son solo fondos
fondo_general = tk.Frame(ventana, bg='black')
fondo_general.pack(expand=True, fill='both')

#///////////////esta seria el frame principal sobre el cual se hara 4 filas
fondo_negro=tk.Frame(fondo_general, bg='gray23')
fondo_negro.place(relheight=.995, relwidth=.985, relx=.0025, rely=.0125)

#estas son las filas dividen la zona de envio la zona de botones y la zona de recepcion
fila_recepcion_datos=tk.Frame(fondo_negro, bg='orange red')
fila_recepcion_datos.place(relwidth=.985, relheight=.45, relx=.0075, rely=.0120)

fila_botones=tk.Frame(fondo_negro, bg='orange red')
fila_botones.place(relwidth=.985, relheight=.35, relx=.0075, rely=.47)

fila_envio_datos=tk.Frame(fondo_negro, bg='orange red')
fila_envio_datos.place(relwidth=.985, relheight=.05, relx=.0075, rely=.83)

fila_copyright=tk.Frame(fondo_negro, bg='orange red')
fila_copyright.place(relwidth=.995, relheight=.03, relx=.0075, rely=.885)

#estas columnas estan dentro de la fila de botones 
#divide en botones generales botones especificos e informacion

columna_botones_generales=tk.Frame(fila_botones, bg='gray25')
columna_botones_generales.place(relheight=.98, relwidth=.3, relx=.005, rely=.012)

columna_botones_especficos=tk.Frame(fila_botones, bg='gray25')
columna_botones_especficos.place(relheight=.98, relwidth=.25, relx=.31, rely=.012)

columna_informacion=tk.Frame(fila_botones, bg='gray25')
columna_informacion.place(relheight=.98, relwidth=.4325, relx=.565, rely=.012)




#/////////////////////LABELS//////////////////////////
# //////////////////////////////////////////////////
mensaje='COPYRIGHT 2023 Designed by David Burbano'
mensaje_Del_Serial=tk.Label(fila_copyright, text=mensaje, background='gray6', font= 'bold15', fg='orange red')
mensaje_Del_Serial.place(relheight=.7, relwidth=.98, relx=.012, rely=.2)

mensaje=''' 
1) Leer bien las instruccions, luego clic en SIGUIENTE.
2) En la parte superior te pediran ingresar unos datos especificos.
3) En la caja de datos de la parte inferior escribir su respuesta.
4) Darle clic en INGRESAR DATOS.
5) clic en SIGUIENTE para ver la nueva solicitud.
6) cuando no haya peticion darle clic en SIGUIENTE.
7) clic aquí si deseas obtener

 '''
instrucciones=tk.Label(columna_informacion, text='INSTRUCCIONES', bg='gray15', font='bold25', fg='orange red')
instrucciones.place(relheight=.25, relwidth=1, relx=0, rely=.012)

infor_inicio=tk.Label(columna_informacion, text=mensaje, bg='gray20', font='bold25', fg='orange red' )
infor_inicio.place(relheight=.75, relwidth=1, relx=0, rely=.25 )

def mensaje_serial():
    global primer_mensaje_Del_Serial#creamos esta variabla global para que pueda ser manipulada en todo el programa
    primer_mensaje_Del_Serial=tk.Label(fila_recepcion_datos, text='', bg='gray20', font= 'bold25', fg='orange red')
    primer_mensaje_Del_Serial.place(relheight=.985, relwidth=.992, relx=.005, rely=.005, anchor='nw')

    if entrada_de_arduino==[]:
      primer_mensaje_Del_Serial.config(text='''Te damos la bienvenida,
      gracias por adquirir nuestros equipos, somos TramarT CNC. 
      antes de  dar clic en SIGUIENTE para comenzar la comunicacion con tu maquina
      te sugerimos leer las INSTRUCCIONES.''')
    else:
      primer_mensaje_Del_Serial.config(text=arduino_pantalla)

        #//////////ENTRADA DE DATOS ENTRY O INPUTS/////////////
         # //////////////////////////////////////////////////

escritura_datos=tk.Entry(fila_envio_datos,  bg='gray62', fg='orange red', font='bold 15')
escritura_datos.place(relheight=.8, relwidth=.45, relx=.3, rely=.1)

        #/////////////FUNCIONES_PARA_EL_PROGRAMA//////////////////
          #/////////////////////////////////////////////////////


mensaje_serial()

def botones(valor):
    arduino.write(valor.encode())
    print(valor)


     




#            /////////////FUNCIONES_PARA_ARDUINO//////////////////
              #/////////////////////////////////////////////////

def esto_es_lo_que_lee_de_arduino():
    leerArduino=arduino.readline().decode().strip()
    entrada_de_arduino.append(leerArduino)
    escritura_datos.focus_set()
    for clave in entrada_de_arduino:
      diccionario=diccionario_variables(clave)
      if diccionario:
        arduino_pantalla.append(diccionario)
      if len(arduino_pantalla)>1:
         arduino_pantalla.pop(0)
    mensaje_serial()

    
      
def escribir_a_arduino(escritura):
    escritura=escritura
    arduino.write(escritura.encode())

def responder_a_arduino():
    respuestas=escritura_datos.get()
    respuesta1=threading.Thread(target=escribir_a_arduino, args=(respuestas, ))
    respuesta1.start()
    escritura_datos.delete(0, END)

def reinicio():
    arduino.open()
    esto_es_lo_que_lee_de_arduino()
    boton_Reiniciar.place_forget()#aqui se vuelve a esconder el boton reiniciar

def destruir_mensaje():
    primer_mensaje_Del_Serial.config(text='')
    primer_mensaje_Del_Serial.destroy()#destruira todo el label asi que obligatorio reiniciar
    arduino.close()
    boton_Reiniciar.place(relheight=.15, relwidth=.45, relx=.05, rely=.33)#cuando se activa la funcion aparece el boton reiniciar

def cerrar_programa():
    ventana.destroy()
    arduino.close()

#            ///////////////////////////BOTONES////////////////////
            # ////////////////////BOTONES GENERALES///////////////////////////
mensaje='''REINICIAR
CONEXION'''
boton_Reiniciar=tk.Button(columna_botones_generales, text=mensaje, bg='OrangeRed2', fg='black',font='bold 10',  command=reinicio )
#medidas y posicionamiento se quitan para que por defecto no 
# aparezcan sin embargo estan en las funciones de destruir_mensaje y reinicio

mensaje='''MAS INFORMACION...'''
boton_ayuda=tk.Button(columna_informacion, text=mensaje, bg='orange red', fg='black',font='bold 12',  command=ven_ayuda)
boton_ayuda.place(relheight=.08, relwidth=.3, relx=.65, rely=.83)


mensaje='''SIGUIENTE'''
boton_Inicio=tk.Button(columna_botones_generales, text=mensaje, bg='orange red', fg='black',font='bold 12',  command=esto_es_lo_que_lee_de_arduino)
boton_Inicio.place(relheight=.15, relwidth=.45, relx=.05, rely=.13)

mensaje='''INGRESAR
DATOS'''
boton_Ingresar_Datos=tk.Button(columna_botones_generales, text=mensaje, bg='OrangeRed2', fg='black',font='bold 12',  command=responder_a_arduino )
boton_Ingresar_Datos.place(relheight=.15, relwidth=.45, relx=.52, rely=.13)

mensaje='''ELIMINAR TODOS
LOS DATOS'''
boton_Eliminar=tk.Button(columna_botones_generales, text=mensaje, bg='OrangeRed2', fg='black',font='bold 12',  command=destruir_mensaje )
boton_Eliminar.place(relheight=.15, relwidth=.45, relx=.52, rely=.33)



mensaje='''CERRAR PROGRAMA Y SERIAL'''
boton_Cerrar=tk.Button(columna_botones_generales, text=mensaje, bg='OrangeRed2', fg='black',font='bold 10',  command=cerrar_programa )
boton_Cerrar.place(relheight=.15, relwidth=.97, relx=.018, rely=.53)


            #/////////////////////////////BOTONES ESPECIFICOS///////////////////////

mensaje='''EJE B
PROFUNDIDAD'''
boton_Inicio=tk.Button(columna_botones_especficos, text=mensaje, bg='OrangeRed2', fg='black',font='bold 12',  command=lambda:botones("b") )
boton_Inicio.place(relheight=.15, relwidth=.38, relx=.0135, rely=.25)

mensaje='''EJE Y
HORIZONTAL'''
boton_Destruir=tk.Button(columna_botones_especficos, text=mensaje, bg='OrangeRed2', fg='black',font='bold 12',  command=lambda:botones('y') )
boton_Destruir.place(relheight=.15, relwidth=.38, relx=.61, rely=.25)

mensaje='''CAMBIO
GIRO'''
boton_Destruir=tk.Button(columna_botones_especficos, text=mensaje, bg='OrangeRed2', fg='black',font='bold 12',  command=lambda:botones('d')  )
boton_Destruir.place(relheight=.15, relwidth=.20, relx=.40, rely=.25)

mensaje='''EJE Z
VERTICAL'''
boton_Destruir=tk.Button(columna_botones_especficos, text=mensaje, bg='OrangeRed2', fg='black',font='bold 12',  command=lambda:botones('z') )
boton_Destruir.place(relheight=.15, relwidth=.3, relx=.345, rely=.085)

mensaje='''EJE A
 ROTACION'''
boton_Destruir=tk.Button(columna_botones_especficos, text=mensaje, bg='OrangeRed2', fg='black',font='bold 12',  command=lambda:botones('a') )
boton_Destruir.place(relheight=.15, relwidth=.3, relx=.345, rely=.415)

mensaje='''EJE X
EMPUJE DE MATERIAL'''
boton_Destruir=tk.Button(columna_botones_especficos, text=mensaje, bg='OrangeRed2', fg='black',font='bold 12',  command=lambda:botones('x') )
boton_Destruir.place(relheight=.15, relwidth=.8, relx=.1, rely=.6)



ventana.mainloop()