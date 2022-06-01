package mrusa;

import java.util.concurrent.Semaphore;

public class Coche implements Runnable {
	private int tam;
	private Semaphore mutex = new Semaphore(1);
	private Semaphore bajarse = new Semaphore(0);
	private Semaphore subirse = new Semaphore(1);
	private Semaphore lleno = new Semaphore(0);
	private int nPasajeros = 0;

	public Coche(int tam) {
		this.tam = tam;
	}

	public void subir(int id) throws InterruptedException {
		// id del pasajero que se sube al coche

		subirse.acquire();
		mutex.acquire();

		nPasajeros++;

		System.out.println("Hay " + nPasajeros + " en el coche");

		if (nPasajeros == tam) {
			lleno.release();
		} else {
			subirse.release();
		}

		mutex.release();

	}

	public void bajar(int id) throws InterruptedException {
		// id del pasajero que se baja del coche
		bajarse.acquire();

		mutex.acquire();

		nPasajeros--;

		System.out.println("Hay " + nPasajeros + " en el coche");

		if (nPasajeros == 0) {
			subirse.release();
		} else {
			bajarse.release();
		}

		mutex.release();
	}

	private void esperaLleno() throws InterruptedException {
		// el coche espera a que este lleno para dar una vuelta
		lleno.acquire();

		System.out.println("Vueltecita en el carricoche");

		bajarse.release();
	}

	public void run() {
		while (true)
			try {
				this.esperaLleno();
				Thread.sleep(200);

			} catch (InterruptedException ie) {
			}

	}
}
// tam pasajeros se suben al coche->el coche da un viaje
// ->tam pasajeros se bajan del coche->......

// CS-Coche: Coche no se pone en marcha hasta que no está lleno
// CS-Pas1: Pasajero no se sube al coche hasta que no hay sitio para el.
// CS-Pas2: Pasajero no se baja del coche hasta que no ha terminado el viaje
