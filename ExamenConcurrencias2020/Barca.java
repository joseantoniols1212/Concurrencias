import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Barca {

	private Lock lck = new ReentrantLock();
	private Condition esperarNorte = lck.newCondition();
	private Condition esperarSur = lck.newCondition();
	private Condition esperarSubir = lck.newCondition();
	private Condition esperarBajar = lck.newCondition();
	private Condition esperarEnBarca = lck.newCondition();
	private int orilla = 1;
	private int pasajeros = 0;
	private boolean bajando = false;

	/*
	 * El Pasajero id quiere darse una vuelta en la barca desde la orilla pos
	 */
	public void subir(int id, int pos) throws InterruptedException {
		lck.lock();
		try {

			System.out
					.println("El pasajero " + id + " de la orilla " + (pos == 0 ? "sur" : "norte") + " quiere subir.");
			while (orilla % 2 != pos || bajando || pasajeros >= 3) {
				if (pos == 0)
					esperarSur.await();
				else
					esperarNorte.await();
			}

			System.out.println("El pasajero " + id + " sube");
			pasajeros++;

			if (pasajeros == 3) {
				esperarSubir.signal();
			}

		} finally {
			lck.unlock();
		}
	}

	/*
	 * Cuando el viaje ha terminado, el Pasajero que esta en la barca se baja
	 */
	public int bajar(int id) throws InterruptedException {
		lck.lock();
		try {

			esperarEnBarca.await();

			System.out.println("El pasajero " + id + " se baja en la orilla " + (orilla + 1) % 2);

			bajando = true;

			pasajeros--;

			if (pasajeros == 0) {
				esperarBajar.signal();
				orilla++;
				bajando = false;
				if (orilla % 2 == 1) {
					esperarSur.signalAll();
				} else {
					esperarNorte.signalAll();
				}
			}

			return orilla % 2;
		} finally {
			lck.unlock();
		}
	}

	/*
	 * El Capitan espera hasta que se suben 3 pasajeros para comenzar el viaje
	 */
	public void esperoSuban() throws InterruptedException {
		lck.lock();
		try {

			System.out.println("		El barco espera a que suban");

			while (pasajeros < 3) {
				esperarSubir.await();
			}

		} finally {
			lck.unlock();
		}
	}

	/*
	 * El Capitan indica a los pasajeros que el viaje ha terminado y tienen que
	 * bajarse
	 */
	public void finViaje() throws InterruptedException {
		lck.lock();
		try {

			esperarEnBarca.signalAll();
			System.out.println("		El barco espera a que bajen");
			esperarBajar.await();

		} finally {
			lck.unlock();
		}
	}

}
