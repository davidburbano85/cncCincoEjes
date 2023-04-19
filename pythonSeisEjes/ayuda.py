from tkinter import*
import tkinter as tk 

ayuda_resortes=''' 
En este modulo hay indicaciones precisas de
como operar tú maquina en modo RESORTES. 
Cabe resaltar que modo RESORTES implica 
un ingreso de datos  que 
proporcionan a la maquina informacion
suficiente para crear RESORTES

 ESTOS SON LOS DATOS SOLICITADOS:

1)Radio del resorte: es el radio externo 
del resorte que deseamos crear.

2)Paso del resorte: es la distancia que hay 
entre cada revolucion 
del resorte.

3)Cantidad de vueltas: nos determina 
cuantas revoluciones tendrá el resorte
contando con 2 vueltas iniciales y dos 
finales que son las de seguridad

4)Direccion del resorte: el resorte puede 
ser fabricado en sentido horario
(de izquierda a derecha), o en sentido 
antihorario(de derecha a izquierda).
se selecciona con las iniciales en mayúscula 
D, I.'''

ayuda_pin='''
En este modulo hay indicaciones precisas de 
como
operar tú maquina en modo PINES. 

Cabe resaltar que modo PINES implica un 
ingreso de datos  que 
proporcionan a la maquina informacion 
suficiente para crear PINES

 ESTOS SON LOS DATOS SOLICITADOS:

1) Cantidad de Movimientos: es cada 
cambio de direccion, que cada eje puede 
ejecutar.
Se debe estar pendiente, por que si el número 
de movimientos ingresado es menor al 
necesitado
el PIN será incompleto.
   
2) Ingresa el eje que deseas mover: recuerda 
que la maquina cuenta con 5 ejes cada uno 
independiente
los ejes principales X, Y, Z, y sus ejes 
de rotacion  A, B

3) ingresa la direccion: cada eje tiene 2 
direcciones horario de izquierda a derecha 
'D' y 
antihorario de derecha a izquierda 'I'. 
'''

ayuda_joystick='''
En modo Joystick tienes toda la libertad 
de mover cada eje 
independientemente en sentido horario
y antihorario con distintos niveles de 
velocidad que pueden 
ser configurados a una velocidad 
*10, *100, *1000 
 '''

info_maquina_text='''
Nombre producto: six axis CNC machine.
Referencia: TT120.
Actualizacion: ATT01.
Contacto: 3135249406
Correo: davidrpy@gmail.com
David Burbano.

SOMOS TRAMART CNC.

Licencia vinculada a: Todo Tornillo.
'''

mensaje_eliminar='''
si por algún motivo, ingresaste mal un codigo,
la mejor opcion es
volver a empezar la conexion con tu maquina,
para esto se creo el boton ELIMINAR, que hará que
la maquina reinicie todas las peticiones de datos.
entonces este será el procedimiento:

1) presionar ELIMINAR.

2) aparecera el boton REINICIAR debes presionarlo.

3) Una vez lo presionas volvera a desaparecer.

4) Lee la peticion en la parte superior y continua el proceso.'''

def ven_ayuda():
    ventana_ayuda=Toplevel()
    ventana_ayuda.geometry('450x900')
    ventana_ayuda.title('six axis machine CNC TT120 helper')
    fondo_principal= tk.Frame(ventana_ayuda, bg='black')
    fondo_principal.place(relheight=1, relwidth=1)
        
        
    fondo_secundario=tk.Frame(fondo_principal, bg='orange red')
    fondo_secundario.place(relheight=.99, relwidth=.99, relx=.005, rely=.005)

    fondo_usar=tk.Frame(fondo_secundario, bg='gray25')
    fondo_usar.place(relheight=.99, relwidth=.99, relx=.005, rely=.005, x=.5)
    
    info_maquina=tk.Label(fondo_usar,text=info_maquina_text, bg='gray18', fg='orange red' )
    info_maquina.place(relheight=1, relwidth=1, anchor='w', rely=.5, relx=0)  

    def ayuda(asesoria):
          

            if asesoria=='resorte':
                ayuda_resorte= tk.Label(fondo_usar, text=ayuda_resortes, bg='gray18', fg='orange red', font='bold12')
                ayuda_resorte.place(relheight=1, relwidth=1, anchor='w', rely=.5, x=.5)
                ventana_ayuda.title('Ayuda en las funciones de resorte')
               
            elif asesoria=='pin':
                ayuda_pin_label= tk.Label(fondo_usar, text=ayuda_pin, bg='gray17', fg='orange red', font='bold12')
                ayuda_pin_label.place(relheight=1, relwidth=1, anchor='w', rely=.5, x=.5 )
                ventana_ayuda.title('Ayuda en las funciones de pines')
                ayuda_resorte.destroy()

            elif asesoria=='jk':
                ayuda_joystick_label= tk.Label(fondo_usar, text=ayuda_joystick, bg='gray14', fg='orange red', font='bold12')
                ayuda_joystick_label.place(relheight=1, relwidth=1, anchor='w', rely=.5, x=.5)   
                ventana_ayuda.title('Ayuda en las funciones de modo manual')
                ayuda_pin_label.destroy()
                ayuda_resorte.destroy()
            
            elif asesoria=='E':
                ayuda_eliminar= tk.Label(fondo_usar, text=mensaje_eliminar, bg='gray14', fg='orange red', font='bold12')
                ayuda_eliminar.place(relheight=1, anchor='w', relwidth=1, rely=.5, x=.5)   
                ventana_ayuda.title('Como eliminar y reiniciar')
                ayuda_pin_label.destroy()
                ayuda_resorte.destroy()
            


    boton_ayuda_resorte=tk.Button(ventana_ayuda, text='Resorte', bg='orange red', fg='black',font='bold 12',  command=lambda:ayuda('resorte'))
    boton_ayuda_resorte.place(relheight=.05, relwidth=.24, relx=.0153, rely=.013)

    boton_ayuda_pin=tk.Button(ventana_ayuda, text='Pin', bg='orange red', fg='black',font='bold 12',  command=lambda:ayuda('pin'))
    boton_ayuda_pin.place(relheight=.05, relwidth=.24, relx=.258, rely=.013)

    boton_ayuda_joystick=tk.Button(ventana_ayuda, text='Joystick', bg='orange red', fg='black',font='bold 12',  command=lambda:ayuda('jk'))
    boton_ayuda_joystick.place(relheight=.05, relwidth=.24, relx=.499, rely=.013)

    boton_eliminar=tk.Button(ventana_ayuda, text='Eliminar', bg='orange red', fg='black',font='bold 12',  command=lambda:ayuda('E'))
    boton_eliminar.place(relheight=.05, relwidth=.24, relx=.745, rely=.013)


    ventana_ayuda.mainloop()
