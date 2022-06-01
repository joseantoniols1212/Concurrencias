package autobus;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Parada {

	private Lock lck = new ReentrantLock();
	private Condition esperaPrincipal = lck.newCondition();
	private Condition esperaSecundario = lck.newCondition();
	private Condition cola = lck.newCondition();
	private Condition esperaBus = lck.newCondition();

	private boolean hayBus = false;
	private int numPasajeros = 0;

	public Parada() {

	}

	/**
	 * El pasajero id llama a este metodo cuando llega a la parada.
	 * Siempre tiene que esperar el siguiente autobus en uno de los
	 * dos grupos de personas que hay en la parada
	 * El metodo devuelve el grupo en el que esta esperando el pasajero
	 * 
	 */
	public int esperoBus(int id) throws InterruptedException {
		lck.lock();
		int grupo;
		try {
			if (hayBus) {
				grupo = 1;
			} else {
				numPasajeros++;
				grupo = 0;
			}
			System.out.println(
					"El pasajero " + id + " espera a bus. En el grupo: " + grupo);
			cola.await();
			return grupo;
		} finally {
			lck.unlock();
		}
	}

	/**
	 * Una vez que ha llegado el autobús, el pasajero id que estaba
	 * esperando en el grupo i se sube al autobus
	 *
	 */
	public void subeAutobus(int id, int i) throws InterruptedException {
		lck.lock();
		try {
			if (i == 1) { // Grupo secundario - Los que se suben al siguiente bus
				cola.await();
				numPasajeros++;
			}
			numPasajeros--;
			System.out.println("	-	El pasajero " + id + " sube al bus");
			if (numPasajeros == 0) {
				esperaBus.signal();
			}
		} finally {
			lck.unlock();
		}
	}

	/**
	 * El autobus llama a este metodo cuando llega a la parada
	 * Espera a que se suban todos los viajeros que han llegado antes
	 * que el, y se va
	 * 
	 */
	public void llegoParada() throws InterruptedException {
		lck.lock();
		try {

			System.out.println("		Llega el bus.");
			hayBus = true;

			cola.signalAll();
			esperaBus.await();

			hayBus = false;
			System.out.println("		Se va el bus.");
		} finally {
			lck.unlock();
		}
	}
}
