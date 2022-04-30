package Ejercicio4;

import java.lang.Thread;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Nodo extends Thread{
    List<Integer> lista = new ArrayList<>();

    public Nodo(List<Integer> lista){
        this.lista = lista;
    }

    private void aniade(List<Integer> l, int desde, int hasta){
        while (desde < hasta){
            l.add(lista.get(desde));
            desde++;
        }
    }

    private void mezcla(List<Integer> l1, List<Integer> l2){
        int i = 0;
        int j = 0;

        while(i < l1.size() && j < l2.size()){
            if( l1.get(i) < l2.get(j)){
                lista.add(l1.get(i));
                i++;
            } else {
                lista.add(l2.get(j));
                j++;
            }
        }

        if(l1.size() == i){
            while(j < l2.size()){
                lista.add(l2.get(j));
                j++;
            }
        } else if (l2.size() == j){
            while(i < l1.size()){
                lista.add(l1.get(i));
                i++;
            }
        }
    }

    public void run(){
        List<Integer> l1 = new ArrayList<>();
        List<Integer> l2 = new ArrayList<>();

        if(lista.size() > 2) {
            aniade(l1, 0, lista.size()/2);
            aniade(l2,lista.size()/2, lista.size());

            Nodo n1 = new Nodo(l1);
            Nodo n2 = new Nodo(l2);

            n1.start();
            n2.start();

            try {
                n1.join();
                n2.join();
                mezcla(l1, l2);
            } catch(InterruptedException e) {
                System.out.println(e.getMessage());
            }

        }

    }

    public static void main(String[] args) {
        int maxRandom = 100;

        Random r = new Random();
        List<Integer> l = new ArrayList<>();

        for(int i = 0; i < 10; i++){
            l.add(r.nextInt(maxRandom));
        }

        Nodo n = new Nodo(l);

        n.start();

        try {
            n.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println(l.toString());
        
    }
}