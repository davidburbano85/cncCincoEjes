import threading, time

def cuenta(h,n,t):
    i=0
    while (i<n):
        time.sleep(1)
        i+=1
        print('hilo numero', h, 'cuenta numero', i, 'este es el valor de n', n,  )

# t1= threading.Thread(target=cuenta, args=(1,4,0.9 ))
t2= threading.Thread(target=cuenta, args=(2,4,1.3 ))

# t3= threading.Thread(target=cuenta, args=(3,4,0.3 ))

t2.start()
# t2.start()
# t3.start()



