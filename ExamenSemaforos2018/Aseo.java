package aseos;

import java.util.concurrent.Semaphore;

public class Aseo {

	private Semaphore mutex = new Semaphore(1, true);
	private Semaphore ocupado = new Semaphore(1, true);
	private int nHombre = 0;
	private int nMujer = 0;

	/**
	 * El hombre id quiere entrar en el aseo.
	 * Espera si no es posible, es decir, si hay alguna mujer en ese
	 * momento en el aseo
	 */
	public void llegaHombre(int id) throws InterruptedException {

	}

	/**
	 * La mujer id quiere entrar en el aseo.
	 * Espera si no es posible, es decir, si hay algun hombre en ese
	 * momento en el aseo
	 */
	public void llegaMujer(int id) throws InterruptedException {

	}

	/**
	 * El hombre id, que estaba en el aseo, sale
	 */
	public void saleHombre(int id) throws InterruptedException {

	}

	public void saleMujer(int id) throws InterruptedException {

	}
}
