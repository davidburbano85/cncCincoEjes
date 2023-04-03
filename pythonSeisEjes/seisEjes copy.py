from tkinter import*
import tkinter as tk 
import threading, serial,time

arduino= serial.Serial('COM3', 9600)

ventana= tk.Tk()
ventana.title('six axis machine CNC TT120')
ventana.geometry('1650x700')
entrada_de_arduino=[]

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
fila_recepcion_datos.place(relwidth=.985, relheight=.25, relx=.0075, rely=.0075)

fila_botones=tk.Frame(fondo_negro, bg='orange red')
fila_botones.place(relwidth=.985, relheight=.55, relx=.0075, rely=.27)

fila_envio_datos=tk.Frame(fondo_negro, bg='orange red')
fila_envio_datos.place(relwidth=.985, relheight=.05, relx=.0075, rely=.83)

fila_copyright=tk.Frame(fondo_negro, bg='orange red')
fila_copyright.place(relwidth=.985, relheight=.03, relx=.0075, rely=.9)

#estas columnas estan dentro de la fila de botones 
#divide en botones generales botones especificos e informacion

columna_botones_generales=tk.Frame(fila_botones, bg='gray25')
columna_botones_generales.place(relheight=.98, relwidth=.325, relx=.005, rely=.012)

columna_botones_especficos=tk.Frame(fila_botones, bg='gray25')

columna_botones_especficos.pack()

columna_informacion=tk.Frame(fila_botones, bg='gray25')
columna_informacion.place(relheight=.98, relwidth=.332, relx=.665, rely=.012)

#/////////////////////LABELS//////////////////////////
# //////////////////////////////////////////////////

# mensaje_Del_Serial=tk.Label(fondo_negro, text='', background='gray6', font= 'bold25', fg='orange red')
# mensaje_Del_Serial.place(relheight=.3, relwidth=.98, relx=.012, rely=.012)
def mensaje_serial():
    global primer_mensaje_Del_Serial#creamos esta variabla global para que pueda ser manipulada en todo el programa
    primer_mensaje_Del_Serial=tk.Label(fila_recepcion_datos, text='', background='gray20', font= 'bold25', fg='orange red')
    primer_mensaje_Del_Serial.place(relheight=.985, relwidth=.992, relx=.005, rely=.005, anchor='nw')

    if entrada_de_arduino==[]:
      primer_mensaje_Del_Serial.config(text='''Te damos la bienvenida,
      gracias por adquirir nuestros equipos somos TramarT CNC 
      dale clic en iniciar para comenzar la comunicacion con tu maquina''')
    else:
      primer_mensaje_Del_Serial.config(text=entrada_de_arduino)
mensaje_serial()

        #//////////ENTRADA DE DATOS ENTRY O INPUTS/////////////
         # //////////////////////////////////////////////////

escritura_datos=tk.Entry(fila_envio_datos,  bg='gray62', fg='orange red', font='bold 15')
escritura_datos.place(relheight=.75, relwidth=.45, relx=.3, rely=.15)


        #/////////////FUNCIONES_PARA_EL_PROGRAMA//////////////////
          #/////////////////////////////////////////////////////

def destruir_mensaje():
    primer_mensaje_Del_Serial.destroy()#destruira todo el label asi que obligatorio reiniciar
    arduino.close()

def botones(valor):
    arduino.write(valor.encode())
    print(valor)

array_datos=[dir, velocida ,numeroVueltas ,rotor]
if(arranca)
var item = 0
var buffer=''
    while(5)
        leerDATO=leerdatosarduiono()

        if(leerDATO=100 && buffer!=100)
            escribirDato(array_datos[item])    
            buffer=leerDATO
                    
        if(leerDATO==2)
            escribirDato(array_datos[item+1]) 
            buffer=leerDATO

        if(leerDATO==3)
            escribirDato(array_datos[item+2])
            buffer=leerDATO        #shift tab mueve todo a la izquierda





            #/////////////FUNCIONES_PARA_ARDUINO//////////////////
              #/////////////////////////////////////////////////

def esto_es_lo_que_lee_de_arduino():
    columna_botones_especficos.place(relheight=.98, relwidth=.325, relx=.335, rely=.012)
    leerArduino=arduino.readline().decode()
    print(leerArduino)
    entrada_de_arduino.append(leerArduino)
    mensaje_serial()
   

def escribir_a_arduino(escritura):
    escritura=escritura
    arduino.write(escritura.encode())

def responder_a_arduino():
    respuestas=escritura_datos.get()
    respuesta1=threading.Thread(target=escribir_a_arduino, args=(respuestas, ))
    respuesta1.start()
    escritura_datos.delete(0, END)
    entrada_de_arduino.pop(0)





    
  

def reinicio():
    arduino.open()








            #///////////////////////////BOTONES////////////////////
            # ////////////////////BOTONES GENERALES///////////////////////////
mensaje='''INICIAR O 
SIGUIENTE'''
boton_Inicio=tk.Button(columna_botones_generales, text=mensaje, bg='orange red', fg='black',font='bold 14',  command=esto_es_lo_que_lee_de_arduino)
boton_Inicio.place(relheight=.12, relwidth=.3, relx=.2, rely=.13)

mensaje='''INGRESAR
DATOS'''
boton_Ingresar_Datos=tk.Button(columna_botones_generales, text=mensaje, bg='OrangeRed2', fg='black',font='bold 14',  command=responder_a_arduino )
boton_Ingresar_Datos.place(relheight=.12, relwidth=.3, relx=.55, rely=.13)

mensaje='''ELIMINAR'''
boton_Eliminar=tk.Button(columna_botones_generales, text=mensaje, bg='OrangeRed2', fg='black',font='bold 14',  command=destruir_mensaje )
boton_Eliminar.place(relheight=.12, relwidth=.3, relx=.55, rely=.33)

mensaje='''REINICIAR'''
boton_Reiniciar=tk.Button(columna_botones_generales, text=mensaje, bg='OrangeRed2', fg='black',font='bold 14',  command=reinicio )
boton_Reiniciar.place(relheight=.12, relwidth=.3, relx=.2, rely=.33)

mensaje='''CERRAR PROGRAMA Y SERIAL'''
boton_Reiniciar=tk.Button(columna_botones_generales, text=mensaje, bg='OrangeRed2', fg='black',font='bold 14',  command='' )
boton_Reiniciar.place(relheight=.1, relwidth=.7, relx=.18, rely=.53)


            #/////////////////////////////BOTONES ESPECIFICOS///////////////////////

mensaje='''EJE
PROFUNDIDAD'''
boton_Inicio=tk.Button(columna_botones_especficos, text=mensaje, bg='OrangeRed2', fg='black',font='bold 12',  command=lambda:botones("x") )
boton_Inicio.place(relheight=.13, relwidth=.3, relx=.1, rely=.25)

mensaje='''EJE
HORIZONTAL'''
boton_Destruir=tk.Button(columna_botones_especficos, text=mensaje, bg='OrangeRed2', fg='black',font='bold 12',  command=lambda:botones('y') )
boton_Destruir.place(relheight=.13, relwidth=.3, relx=.6, rely=.25)

mensaje='''CAMBIO
GIRO'''
boton_Destruir=tk.Button(columna_botones_especficos, text=mensaje, bg='OrangeRed2', fg='black',font='bold 12',  command=lambda:botones('d')  )
boton_Destruir.place(relheight=.13, relwidth=.15, relx=.425, rely=.25)

mensaje='''EJE
VERTICAL'''
boton_Destruir=tk.Button(columna_botones_especficos, text=mensaje, bg='OrangeRed2', fg='black',font='bold 12',  command=lambda:botones('z') )
boton_Destruir.place(relheight=.13, relwidth=.2, relx=.4, rely=.1)

mensaje='''EJE
 ROTACION'''
boton_Destruir=tk.Button(columna_botones_especficos, text=mensaje, bg='OrangeRed2', fg='black',font='bold 12',  command=lambda:botones('a') )
boton_Destruir.place(relheight=.13, relwidth=.2, relx=.4, rely=.4)



ventana.mainloop()