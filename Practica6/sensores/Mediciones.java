package sensores;

import java.util.concurrent.Semaphore;

public class Mediciones {

    Semaphore esperoPorTrabajador = new Semaphore(0);
    Semaphore exclusionNumMed = new Semaphore(1);
    Semaphore esperoPorSensores = new Semaphore(0);
    int numMed = 0;

    public Mediciones() {

    }

    /**
     * El sensor id deja su medición y espera hasta que el trabajador
     * ha terminado sus tareas
     * 
     * @param id
     * @throws InterruptedException
     */
    public void nuevaMedicion(int id) throws InterruptedException {

        exclusionNumMed.acquire();

        numMed++;
        System.out.println("Sensor " + id + " deja sus mediciones.");
        if (numMed == 3) {
            esperoPorSensores.release();
        }
        exclusionNumMed.release();

        esperoPorTrabajador.acquire();

        exclusionNumMed.acquire();
        numMed--;
        if (numMed != 0) {
            esperoPorTrabajador.release();
        }
        exclusionNumMed.release();

    }

    /***
     * El trabajador espera hasta que están las tres mediciones
     * 
     * @throws InterruptedException
     */
    public void leerMediciones() throws InterruptedException {

        esperoPorSensores.acquire();

        System.out.println("El trabajador tiene sus mediciones...y empieza sus tareas");

    }

    /**
     * El trabajador indica que ha terminado sus tareas
     */
    public void finTareas() {
        System.out.println("El trabajador ha terminado sus tareas");
        esperoPorTrabajador.release();

    }

}
