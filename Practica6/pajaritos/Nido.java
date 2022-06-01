package pajaritos;

import java.util.concurrent.*;

public class Nido {
	private int B = 10; // Número máximo de bichos
	private int bichitos = 0; // puede tener de 0 a B bichitos
	private Semaphore comer = new Semaphore(0);
	private Semaphore traerBichito = new Semaphore(1);
	private Semaphore mutex = new Semaphore(1);

	public void come(int id) throws InterruptedException {

		comer.acquire();
		mutex.acquire();

		if (bichitos == 0) {
			comer.acquire();
		}

		bichitos--;
		System.out.println("El bebé " + id + " ha comido un bichito. Quedan " + bichitos);

		if (bichitos == B - 1) {
			traerBichito.release();
		}
		if (bichitos > 0) {
			comer.release();
		}

		mutex.release();

	}

	public void nuevoBichito(int id) throws InterruptedException {
		// el papa/mama id deja un nuevo bichito en el nido

		traerBichito.acquire();
		mutex.acquire();

		bichitos++;
		System.out.println("El papá " + id + " ha añadido un bichito. Hay " + bichitos);

		if (bichitos < B) {
			traerBichito.release();
		}
		if (bichitos > 0) {
			comer.release();
		}

		mutex.release();

	}
}

// CS-Bebe-i: No puede comer del nido si está vacío
// CS-Papa/Mama: No puede poner un bichito en el nido si está lleno
