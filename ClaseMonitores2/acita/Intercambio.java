package acita;

import java.util.concurrent.Semaphore;

/*
Primero resolver con semáforos.
Segundo resolver con wait and notify o notifyAll.
*/

public class Intercambio {
    private int v1, v2;

    // private Semaphore semaphore1 = new Semaphore(0);
    // private Semaphore semaphore2 = new Semaphore(0);

    // // Acepta el dato generado por w1 y devuelve el de w2, OJO hasta que w2 no ha
    // // dejado
    // // dato, no se puede devolver
    // public int Intercambio1(int dato) throws InterruptedException {
    // v1 = dato;
    // semaphore1.release();
    // semaphore2.acquire();
    // return v2;
    // }

    // // Acepta el dato generado por w2 y devuelve el de w1, OJO hasta que w1 no ha
    // // dejado
    // // dato, no se puede devolver
    // public int Intercambio2(int dato) throws InterruptedException {
    // v2 = dato;
    // semaphore2.release();
    // semaphore1.acquire();
    // return v1;
    // }

    // Acepta el dato generado por w1 y devuelve el de w2, OJO hasta que w2 no ha
    // dejado
    // dato, no se puede devolver

    boolean hayDato1 = false;
    boolean hayDato2 = false;

    public synchronized int Intercambio1(int dato) throws InterruptedException {
        v1 = dato;
        hayDato1 = true;
        while (!hayDato2) {
            wait();
        }
        notify();
        hayDato2 = false;
        return v2;
    }

    // Acepta el dato generado por w2 y devuelve el de w1, OJO hasta que w1 no ha
    // dejado
    // dato, no se puede devolver
    public synchronized int Intercambio2(int dato) throws InterruptedException {
        v2 = dato;
        hayDato2 = true;
        while (!hayDato1) {
            wait();
        }
        notify();
        hayDato1 = false;
        return v1;
    }
}