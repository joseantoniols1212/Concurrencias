package agua;

import java.util.concurrent.*;

public class GestorAgua {

	private Semaphore mutex = new Semaphore(1, true);
	private Semaphore hidrogeno = new Semaphore(1, true);
	private Semaphore oxigeno = new Semaphore(1, true);
	private int numh = 0;
	private int numo = 0;

	public void hListo(int id) throws InterruptedException {

		hidrogeno.acquire();
		mutex.acquire();

		numh++;

		System.out.println("Hidrogeno con id " + id + ", es el " + numh + " hidrogeno listo para formar una molecula");

		if (numh == 2 && numo == 1) {
			System.out.println("		Molecula creada");
			oxigeno.release();
			hidrogeno.release();
			numh = 0;
			numo = 0;
		} else if (numh == 1) {
			hidrogeno.release();
		}

		mutex.release();
	}

	public void oListo(int id) throws InterruptedException {

		oxigeno.acquire();
		mutex.acquire();

		numo++;
		System.out.println("Oxigeno con id " + id + ", listo para formar una molecula");

		if (numh == 2 && numo == 1) {
			System.out.println("		Molecula creada");
			hidrogeno.release();
			oxigeno.release();
			numh = 0;
			numo = 0;
		}

		mutex.release();
	}
}