package lectoresescritores;

public class GestorBD {

	private int nLectores;
	private boolean escribiendo;

	public synchronized void entraLector(int id) throws InterruptedException {

		while (escribiendo)
			wait();
		System.out.println("Entra lector " + id + " Hay " + nLectores);
		nLectores++;

	}

	public synchronized void saleLector(int id) throws InterruptedException {

		nLectores--;
		System.out.println("Sale lector " + id + " Hay " + nLectores);

		if (nLectores == 0)
			notify();

	}

	public synchronized void entraEscritor(int id) throws InterruptedException {

		while (escribiendo || (nLectores != 0))
			wait();

		escribiendo = true;
		System.out.println("                    Entra escritor " + id);
	}

	public synchronized void saleEscritor(int id) {

		System.out.println("             Sale escritor " + id);
		escribiendo = false;

		notifyAll();

	}

}
// CS-Escritores: exclusion mutua
// CS-Lectores: puede haber varios pero nunca con un escritor