package productorconsumidor;

//Condición Productor:
//  No puedo almacenar hasta que no se ha leido.  
//Condición Consumidor:
// No puedo extraer hasta que no se ha almacenado uno nuevo. 
public class RecursoCompartido {
    private int recurso;

    private boolean almacenado = false;

    public RecursoCompartido() {
    }

    public synchronized int extraer() throws InterruptedException {
        while (!almacenado) {
            wait();
        }
        System.out.println("Extraído " + recurso);
        almacenado = false;
        notify();
        return recurso;
    }

    public synchronized void almacenar(int r) throws InterruptedException {
        while (almacenado) {
            wait();
        }
        recurso = r;
        almacenado = true;
        notify();
        System.out.println("Almacenado " + r);
    }

}
