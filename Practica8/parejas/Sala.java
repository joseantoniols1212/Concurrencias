package parejas;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Sala {

	private boolean hayHombre = false;
	private boolean hayMujer = false;
	private boolean mutexSala = false;
	private boolean cita = false;

	/**
	 * un hombre llega a la sala para formar una pareja si ya hay otra mujer en la
	 * sala o si a�n no hay un hombre
	 * 
	 * @throws InterruptedException
	 */
	// public synchronized void llegaHombre(int id) throws InterruptedException {

	// while (hayHombre || mutexSala) {
	// wait();
	// }

	// hayHombre = true;

	// System.out.println("El hombre " + id + " espera en la sala.");

	// if (hayMujer) {
	// mutexSala = true;
	// cita = true;
	// System.out.println("El hombre " + id + " ha tenido una cita.");
	// notifyAll();
	// } else {
	// while (!cita)
	// wait();
	// System.out.println("El hombre " + id + " ha tenido una cita.");
	// cita = false;
	// }

	// hayHombre = false;

	// System.out.println("El hombre " + id + " sale de la sala.");

	// if (!hayMujer) {
	// mutexSala = false;
	// notifyAll();
	// }

	// }

	/**
	 * una mujer llega a la sala para formar una pareja debe esperar si ya hay otra
	 * mujer en la sala o si aún no hay un hombre
	 * 
	 * @throws InterruptedException
	 */
	// public synchronized void llegaMujer(int id) throws InterruptedException {

	// while (hayMujer || mutexSala) {
	// wait();
	// }

	// hayMujer = true;
	// System.out.println("La mujer " + id + " espera en la sala.");

	// if (hayHombre) {
	// mutexSala = true;
	// cita = true;
	// System.out.println("La mujer " + id + " ha tenido una cita.");
	// notifyAll();
	// } else {
	// while (!cita)
	// wait();
	// System.out.println("La mujer " + id + " ha tenido una cita.");
	// cita = false;
	// }

	// hayMujer = false;

	// System.out.println("La mujer " + id + " sale de la sala.");

	// if (!hayHombre) {
	// mutexSala = false;
	// notifyAll();
	// }
	// }

	private Lock lck = new ReentrantLock();
	private Condition esperaHombre = lck.newCondition();
	private Condition esperaMujer = lck.newCondition();

	public void llegaHombre(int id) throws InterruptedException {

		while (hayHombre || mutexSala) {
			esperaHombre.await();
		}

		hayHombre = true;

		System.out.println("El hombre " + id + " espera en la sala.");

		if (hayMujer) {
			mutexSala = true;
			cita = true;
			System.out.println("El hombre " + id + " ha tenido una cita.");
			esperaMujer.signal();
		} else {
			while (!cita)
				esperaHombre.await();
			System.out.println("El hombre " + id + " ha tenido una cita.");
			cita = false;
		}

		hayHombre = false;

		System.out.println("El hombre " + id + " sale de la sala.");

		if (!hayMujer) {
			mutexSala = false;
			esperaHombre.signal();
			esperaMujer.signal();
		}

	}

	public void llegaMujer(int id) throws InterruptedException {

		while (hayMujer || mutexSala) {
			esperaMujer.await();
		}

		hayMujer = true;
		System.out.println("La mujer " + id + " espera en la sala.");

		if (hayHombre) {
			mutexSala = true;
			cita = true;
			System.out.println("La mujer " + id + " ha tenido una cita.");
			esperaHombre.signal();
		} else {
			while (!cita)
				esperaMujer.signal();
			System.out.println("La mujer " + id + " ha tenido una cita.");
			cita = false;
		}

		hayMujer = false;

		System.out.println("La mujer " + id + " sale de la sala.");

		if (!hayHombre) {
			mutexSala = false;
			esperaHombre.signal();
			esperaMujer.signal();
		}
	}
}
