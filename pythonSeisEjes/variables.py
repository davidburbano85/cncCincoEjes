opciones_locales = {
    'o':  'Por favor presiona 1 para iniciar',
    'a1': 'Por favor presiona: 1 para crear resortes, 2 para pines y 3 joystick',
    'a2': 'Solicitud incorrecta',
    'b1': 'Por favor ingresa el RADIO del resorte',
    'b2': 'Ahora por favor ingresa el PASO del resorte',
    'b3': 'Por favor ingresa la cantidad de ESPIRAS del resorte',
    'b4': 'Por favor ingresa la direccion "D" gira a la derecha e  "I" gira a la izquierda',
    'b5': 'por favor ingrese la cantidad de resortes que desea realizar',
    'c1': 'direccion incorrecta',
    'e1': 'Por favor ingresa la cantidad de movimientosa realizar',
    'e2': '''Por favor ingresa el tipo de movimiento 
    x: es para crear un segmento del zig-zag debera añadir la distancia en mm para el segmento
    Y: son los grados a los que quedaran entre segmentos por lo general 80°    
    a: es para rotar la maquina en general y creara un pin en 360°''',
    'e3': 'Por favor escribe la direccion de el eje Der: "D", Izq: "I" ',
    'e4': 'ese eje no existe',
    'e5': 'por favor ingresa el diametro del pin',
    'e6': 'por favor ingresa la cantidad de pines que deseas crear',
    'f1': 'direccion no valida',
    'g1': 'multiplica la velocidad: x1, x10, x100, x1000 ',
    'h1': '''Presione el boton del  eje que desea mover X, Y, Z, A, B ó escribe r
     para resetear la velocidad y "CAMBIO DE GIRO" para cambiar la direccion de cada eje''',
 
}

claves_opciones = list(opciones_locales.keys())
valores_opciones = ''


def diccionario_variables(clavearduino):
    for clave in claves_opciones:
        if clave == clavearduino:
            valores_opciones = opciones_locales[clave]
            return valores_opciones
