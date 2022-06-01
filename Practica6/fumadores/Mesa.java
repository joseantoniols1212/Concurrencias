package fumadores;

import java.util.concurrent.*;

public class Mesa {

	// esta es una implementación pasiva para los fumadores
	// los van a despertar cuando tengan que fumar.

	private int nFumadores = 3;
	private Semaphore agente = new Semaphore(0);
	private Semaphore[] semaforos = new Semaphore[nFumadores];

	public Mesa() {
		int nFumadores = 3;
		for (int i = 0; i < nFumadores; i++) {
			semaforos[i] = new Semaphore(0);
		}
	}

	public void qFumar(int id) throws InterruptedException {

		semaforos[id].acquire();

		System.out.println("Fumador " + id + " coge los ingredientes");

	}

	public void finFumar(int id) {

		System.out.println("Fumador " + id + " ha terminado de fumar");

		agente.release();

	}

	public void nuevosIng(int ing) throws InterruptedException { // se pasa el ingrediente que no se pone

		System.out.print("El agente ha puesto los ingredientes ");

		semaforos[ing].release();

		agente.acquire();

	}

}

// CS-Fumador i: No puede fumar hasta que el fumador anterior no ha terminado
// de fumar y sus ingredientes están sobre la mesa
// CS-Agente: no puede poner nuevos ingredientes hasta que el fumador anterior
// no ha terminado de fumar
