package barca;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Barca extends Thread {

	// private static final int C = 4;
	// private int androids = 0;
	// private int iphones = 0;
	// private boolean bajarse = false;

	// /**
	// * Un estudiante con m�vil android llama a este m�todo cuando quiere cruzar el
	// * r�o. Debe esperarse a montarse en la barca de forma segura, y a llegar a la
	// * otra orilla del antes de salir del m�todo
	// *
	// * @param id
	// * del estudiante android que llama al m�todo
	// * @throws InterruptedException
	// */

	// public synchronized void android(int id) throws InterruptedException {

	// while ((androids + iphones == 4) || iphones == 3 || (androids == 2 && iphones
	// == 1) || bajarse)
	// wait();

	// androids++;

	// System.out.println("El android " + id + " se sube a la barca.");

	// if (androids + iphones == 4) {
	// bajarse = true;
	// System.out.println("Hemos llegado a la orilla");
	// notifyAll();
	// }

	// while (!bajarse) {
	// wait();
	// }

	// androids--;

	// if (androids + iphones == 0) {
	// bajarse = false;
	// notifyAll();
	// }

	// }

	// /**
	// * Un estudiante con m�vil android llama a este m�todo cuando quiere cruzar el
	// * r�o. Debe esperarse a montarse en la barca de forma segura, y a llegar a la
	// * otra orilla del antes de salir del m�todo
	// *
	// * @param id
	// * del estudiante android que llama al m�todo
	// * @throws InterruptedException
	// */

	// public synchronized void iphone(int id) throws InterruptedException {

	// while ((androids + iphones == 4) || androids == 3 || (androids == 1 &&
	// iphones == 2) || bajarse)
	// wait();

	// iphones++;

	// System.out.println("El iphone " + id + " se sube a la barca.");

	// if (androids + iphones == 4) {
	// bajarse = true;
	// System.out.println("Hemos llegado a la orilla");
	// notifyAll();
	// }

	// while (!bajarse) {
	// wait();
	// }

	// iphones--;

	// if (androids + iphones == 0) {
	// bajarse = false;
	// notifyAll();
	// }

	// }

	private static final int C = 4;
	private int androids = 0;
	private int iphones = 0;
	private Lock lock = new ReentrantLock();
	private Condition condSubir = lock.newCondition();
	private Condition condBajar = lock.newCondition();

	/**
	 * Un estudiante con m�vil android llama a este m�todo cuando quiere cruzar el
	 * r�o. Debe esperarse a montarse en la barca de forma segura, y a llegar a la
	 * otra orilla del antes de salir del m�todo
	 * 
	 * @param id
	 *           del estudiante android que llama al m�todo
	 * @throws InterruptedException
	 */

	public void android(int id) throws InterruptedException {

		lock.lock();
		try {

			while ((androids + iphones == 4) || iphones == 3 || (androids == 2 && iphones == 1))
				condSubir.await();

			androids++;

			System.out.println("El android " + id + " se sube a la barca.");

			if (androids + iphones == 4) {
				System.out.println("Hemos llegado a la orilla");
				condBajar.signalAll();
			} else {
				condBajar.await();
			}

			androids--;

			if (androids + iphones == 0) {
				condSubir.signalAll();
			}

		} finally {
			lock.unlock();
		}
	}

	/**
	 * Un estudiante con m�vil android llama a este m�todo cuando quiere cruzar el
	 * r�o. Debe esperarse a montarse en la barca de forma segura, y a llegar a la
	 * otra orilla del antes de salir del m�todo
	 * 
	 * @param id
	 *           del estudiante android que llama al m�todo
	 * @throws InterruptedException
	 */

	public void iphone(int id) throws InterruptedException {

		lock.lock();
		try {

			while ((androids + iphones == 4) || androids == 3 || (androids == 1 && iphones == 2))
				condSubir.await();

			iphones++;

			System.out.println("El iphone " + id + " se sube a la barca.");

			if (androids + iphones == 4) {
				System.out.println("Hemos llegado a la orilla");
				condBajar.signalAll();
			} else {
				condBajar.await();
			}

			iphones--;

			if (androids + iphones == 0) {
				condSubir.signalAll();
			}

		} finally {
			lock.unlock();
		}
	}

}

// CS-IPhone: no puede subirse a la barca hasta que est� en modo subida, haya
// sitio
// y no sea peligroso

// CS-Android: no puede subirse a la barca hasta que est� en modo subida, haya
// sitio
// y no sea peligroso

// CS-Todos: no pueden bajarse de la barca hasta que haya terminado el viaje