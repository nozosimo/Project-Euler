package MazeCore;

import java.awt.Point;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

public class Laberinto {

    Queue<Point> ins;
    public LinkedList<int[][]> results = new LinkedList<>();
    public LinkedList<Integer> steps = new LinkedList<>();
    int c = 0;

    private void mostrar(int m[][]) {
        for (int i = 0; i < m.length; ++i) {
            for (int j = 0; j < m[i].length; ++j) {
                System.out.print("" + m[i][j] + " ");
            }
            System.out.println("");
        }
    }
    
    int floodSize = 0;
    private void flood(int m[][],int i,int j){
        if(!posValida(m, i, j)) return;
        m[i][j]=1;
        floodSize++;
        LinkedList<Regla> L1 = reglasAplicables(m, i, j);
        while (!L1.isEmpty()) {
            Regla R = L1.removeFirst();
            flood(m, R.fil, R.col);
        }

        
    }

    public Queue<Point> Instrucciones(int m[][], int i, int j, int ifin, int jfin) {

        floodSize=0;
        int[][] copy = Arrays.stream(m).map(int[]::clone).toArray(int[][]::new);
        flood(copy,i,j);
        
        System.out.println("Tamano Area: "+floodSize);
        
        m[i][j] = 0;

        LinkedList<Point> L = new LinkedList<>();
        results.clear();
        steps.clear();

        ins = new LinkedList();
        c = 0;

        // laberintoA(m, i, j, 1,L);
        // laberintoB(m, i, j, 1,L);
        // laberintoC(m, i, j, ifin, jfin, 1, L);
        
        //torreA(m, i, j, 1,L);
        // torreB(m, i, j, 1,L);
        // torreC(m, i, j, ifin, jfin, 1, L);
        
        // alfilA(m, i, j, 1,L);
        // alfilB(m, i, j, 1,L);
        // alfilC(m, i, j, ifin, jfin, 1, L);
        
        // reinaA(m, i, j, 1,L);
         reinaB(m, i, j, 1,L);
        // reinaC(m, i, j, ifin, jfin, 1, L);
        
        System.out.println("InicioX: " + i);
        System.out.println("InicioY: " + j);
        System.out.println("FinY: " + ifin);
        System.out.println("FinY: " + jfin);
        System.out.println("Soluciones: " + c);
        System.out.println("Movimientos: " + ins.size());
        return ins;
    }

    public boolean posValida(int m[][], int i, int j) {
        return i >= 0 && i < m.length
                && j >= 0 && j < m[i].length && (m[i][j] == 0);
    }

    
    // LABERINTO
    private LinkedList<Regla> reglasAplicables(int m[][], int i, int j) {
        LinkedList<Regla> L1 = new LinkedList();
        if (posValida(m, i, j - 1)) {
            L1.add(new Regla(i, j - 1));
        }
        if (posValida(m, i - 1, j)) {
            L1.add(new Regla(i - 1, j));
        }
        if (posValida(m, i, j + 1)) {
            L1.add(new Regla(i, j + 1));
        }
        if (posValida(m, i + 1, j)) {
            L1.add(new Regla(i + 1, j));
        }

        return L1;
    }

    // TODOS LOS CAMINOS POSIBLES
    private void laberintoA(int m[][], int i, int j, int paso, LinkedList<Point> acum) {

        if (!posValida(m, i, j)) {
            return;
        }
        m[i][j] = paso;

        // ANADIR ESTO
        //mostrar(m);
        steps.add(paso);
        acum.addLast(new Point(i, j));
        int[][] copy = Arrays.stream(m).map(int[]::clone).toArray(int[][]::new);
        results.add(copy);
        for (int k = 0; k < acum.size(); ++k) {
            ins.add((Point) acum.get(k).clone());
        }

        LinkedList<Regla> L1 = reglasAplicables(m, i, j);
        while (!L1.isEmpty()) {
            Regla R = L1.removeFirst();
            laberintoA(m, R.fil, R.col, paso + 1, acum);
            m[R.fil][R.col] = 0;

        }

        // ANADIR ESTO
        acum.removeLast();
    }

    // TODOS LOS CAMINOS QUE RECORREN TODAS LAS CELDAS
    private void laberintoB(int m[][], int i, int j, int paso, LinkedList<Point> acum) {

        if (!posValida(m, i, j)) {
            return;
        }
        acum.addLast(new Point(i, j));
        m[i][j] = paso;

        if (paso == floodSize) {
            // ANADIR ESTO
            //mostrar(m);
            steps.add(paso);
            
            int[][] copy = Arrays.stream(m).map(int[]::clone).toArray(int[][]::new);
            results.add(copy);
            for (int k = 0; k < acum.size(); ++k) {
                ins.add((Point) acum.get(k).clone());
            }
        }
        LinkedList<Regla> L1 = reglasAplicables(m, i, j);
        while (!L1.isEmpty()) {
            Regla R = L1.removeFirst();
            laberintoB(m, R.fil, R.col, paso + 1, acum);
            m[R.fil][R.col] = 0;

        }

        // ANADIR ESTO
        acum.removeLast();
    }

    // TODOS LOS CAMINOS DE PUNTO INICIO A FIN (ARBITRARIOS)
    private void laberintoC(int m[][], int i, int j, int ifin, int jfin, int paso, LinkedList<Point> acum) {

        if (!posValida(m, i, j)) {
            return;
        }

        // ANADIR ESTO
        acum.addLast(new Point(i, j));

        m[i][j] = paso;
        if (i == ifin && j == jfin) {
            c++;
            steps.add(paso);
            int[][] copy = Arrays.stream(m).map(int[]::clone).toArray(int[][]::new);
            results.add(copy);
            //mostrar(copy);
            for (int k = 0; k < acum.size(); ++k) {
                ins.add((Point) acum.get(k).clone());
            }

        }

        LinkedList<Regla> L1 = reglasAplicables(m, i, j);
        while (!L1.isEmpty()) {
            Regla R = L1.removeFirst();
            laberintoC(m, R.fil, R.col, ifin, jfin, paso + 1, acum);
            m[R.fil][R.col] = 0;

        }

        // ANADIR ESTO
        acum.removeLast();
    }
    
    // TORRE
     private LinkedList<Regla> reglasAplicablesTorre(int m[][], int i, int j) {
        LinkedList<Regla> L1 = new LinkedList();
        
        int pi,pj;
        
        pi=i-1;
        pj=j;
        while(posValida(m, pi, pj)){
            L1.add(new Regla(pi,pj));
            pi--;
        }
        
        pi=i;
        pj=j-1;
        while(posValida(m, pi, pj)){
            L1.add(new Regla(pi,pj));
            pj--;
        }
        
        pi=i+1;
        pj=j;
        while(posValida(m, pi, pj)){
            L1.add(new Regla(pi,pj));
            pi++;
        }
        
        
        
        pi=i;
        pj=j+1;
        while(posValida(m, pi, pj)){
            L1.add(new Regla(pi,pj));
            pj++;
        }
        
        
        
        

        return L1;
    }
     
     // TODOS LOS CAMINOS POSIBLES
    private void torreA(int m[][], int i, int j, int paso, LinkedList<Point> acum) {

        if (!posValida(m, i, j)) {
            return;
        }
        m[i][j] = paso;

        // ANADIR ESTO
        //mostrar(m);
        steps.add(paso);
        acum.addLast(new Point(i, j));
        int[][] copy = Arrays.stream(m).map(int[]::clone).toArray(int[][]::new);
        results.add(copy);
        for (int k = 0; k < acum.size(); ++k) {
            ins.add((Point) acum.get(k).clone());
        }

        LinkedList<Regla> L1 = reglasAplicablesTorre(m, i, j);
        while (!L1.isEmpty()) {
            Regla R = L1.removeFirst();
            torreA(m, R.fil, R.col, paso + 1, acum);
            m[R.fil][R.col] = 0;

        }

        // ANADIR ESTO
        acum.removeLast();
    }
    
    private void torreB(int m[][], int i, int j, int paso, LinkedList<Point> acum) {

        if (!posValida(m, i, j)) {
            return;
        }
        acum.addLast(new Point(i, j));
        m[i][j] = paso;

        if (paso == floodSize) {
            // ANADIR ESTO
            //mostrar(m);
            steps.add(paso);
            
            int[][] copy = Arrays.stream(m).map(int[]::clone).toArray(int[][]::new);
            results.add(copy);
            for (int k = 0; k < acum.size(); ++k) {
                ins.add((Point) acum.get(k).clone());
            }
        }
        LinkedList<Regla> L1 = reglasAplicablesTorre(m, i, j);
        while (!L1.isEmpty()) {
            Regla R = L1.removeFirst();
            torreB(m, R.fil, R.col, paso + 1, acum);
            m[R.fil][R.col] = 0;

        }

        // ANADIR ESTO
        acum.removeLast();
    }
    
    
    private void torreC(int m[][], int i, int j, int ifin, int jfin, int paso, LinkedList<Point> acum) {

        if (!posValida(m, i, j)) {
            return;
        }

        // ANADIR ESTO
        acum.addLast(new Point(i, j));

        m[i][j] = paso;
        if (i == ifin && j == jfin) {
            c++;
            steps.add(paso);
            int[][] copy = Arrays.stream(m).map(int[]::clone).toArray(int[][]::new);
            results.add(copy);
            //mostrar(copy);
            for (int k = 0; k < acum.size(); ++k) {
                ins.add((Point) acum.get(k).clone());
            }

        }

        LinkedList<Regla> L1 = reglasAplicablesTorre(m, i, j);
        while (!L1.isEmpty()) {
            Regla R = L1.removeFirst();
            torreC(m, R.fil, R.col, ifin, jfin, paso + 1, acum);
            m[R.fil][R.col] = 0;

        }

        // ANADIR ESTO
        acum.removeLast();
    }
    
    // ALFIL
     private LinkedList<Regla> reglasAplicablesAlfil(int m[][], int i, int j) {
        LinkedList<Regla> L1 = new LinkedList();
        
        int pi,pj;
        
        pi=i-1;
        pj=j-1;
        while(posValida(m, pi, pj)){
            L1.add(new Regla(pi,pj));
            pi--;
            pj--;
        }
        
        pi=i+1;
        pj=j-1;
        while(posValida(m, pi, pj)){
            L1.add(new Regla(pi,pj));
            pi++;
            pj--;
        }
        
        pi=i+1;
        pj=j+1;
        while(posValida(m, pi, pj)){
            L1.add(new Regla(pi,pj));
            pi++;
            pj++;
        }
        
        pi=i-1;
        pj=j+1;
        while(posValida(m, pi, pj)){
            L1.add(new Regla(pi,pj));
            pi--;
            pj++;
        }
        
        

        return L1;
    }
     
      // TODOS LOS CAMINOS POSIBLES
    private void alfilA(int m[][], int i, int j, int paso, LinkedList<Point> acum) {

        if (!posValida(m, i, j)) {
            return;
        }
        m[i][j] = paso;

        // ANADIR ESTO
        //mostrar(m);
        steps.add(paso);
        acum.addLast(new Point(i, j));
        int[][] copy = Arrays.stream(m).map(int[]::clone).toArray(int[][]::new);
        results.add(copy);
        for (int k = 0; k < acum.size(); ++k) {
            ins.add((Point) acum.get(k).clone());
        }

        LinkedList<Regla> L1 = reglasAplicablesAlfil(m, i, j);
        while (!L1.isEmpty()) {
            Regla R = L1.removeFirst();
            alfilA(m, R.fil, R.col, paso + 1, acum);
            m[R.fil][R.col] = 0;

        }

        // ANADIR ESTO
        acum.removeLast();
    }
    
    // TODOS LOS CAMINOS QUE RECORREN TODAS LAS CELDAS
    private void alfilB(int m[][], int i, int j, int paso, LinkedList<Point> acum) {

        if (!posValida(m, i, j)) {
            return;
        }
        acum.addLast(new Point(i, j));
        m[i][j] = paso;

        if (paso == floodSize) {
            // ANADIR ESTO
            //mostrar(m);
            steps.add(paso);
            
            int[][] copy = Arrays.stream(m).map(int[]::clone).toArray(int[][]::new);
            results.add(copy);
            for (int k = 0; k < acum.size(); ++k) {
                ins.add((Point) acum.get(k).clone());
            }
        }
        LinkedList<Regla> L1 = reglasAplicablesAlfil(m, i, j);
        while (!L1.isEmpty()) {
            Regla R = L1.removeFirst();
            alfilB(m, R.fil, R.col, paso + 1, acum);
            m[R.fil][R.col] = 0;

        }

        // ANADIR ESTO
        acum.removeLast();
    }

    // TODOS LOS CAMINOS DE PUNTO INICIO A FIN (ARBITRARIOS)
    private void alfilC(int m[][], int i, int j, int ifin, int jfin, int paso, LinkedList<Point> acum) {

        if (!posValida(m, i, j)) {
            return;
        }

        // ANADIR ESTO
        acum.addLast(new Point(i, j));

        m[i][j] = paso;
        if (i == ifin && j == jfin) {
            c++;
            steps.add(paso);
            int[][] copy = Arrays.stream(m).map(int[]::clone).toArray(int[][]::new);
            results.add(copy);
            //mostrar(copy);
            for (int k = 0; k < acum.size(); ++k) {
                ins.add((Point) acum.get(k).clone());
            }

        }

        LinkedList<Regla> L1 = reglasAplicablesAlfil(m, i, j);
        while (!L1.isEmpty()) {
            Regla R = L1.removeFirst();
            alfilC(m, R.fil, R.col, ifin, jfin, paso + 1, acum);
            m[R.fil][R.col] = 0;

        }

        // ANADIR ESTO
        acum.removeLast();
    }
    
    // REINA
     private LinkedList<Regla> reglasAplicablesReina(int m[][], int i, int j) {
        LinkedList<Regla> L1 = new LinkedList();
        
        int pi,pj;
        
        pi=i-1;
        pj=j;
        while(posValida(m, pi, pj)){
            L1.add(new Regla(pi,pj));
            pi--;
        }
        
        pi=i-1;
        pj=j-1;
        while(posValida(m, pi, pj)){
            L1.add(new Regla(pi,pj));
            pi--;
            pj--;
        }
        
        pi=i;
        pj=j-1;
        while(posValida(m, pi, pj)){
            L1.add(new Regla(pi,pj));
            pj--;
        }
        
        pi=i+1;
        pj=j-1;
        while(posValida(m, pi, pj)){
            L1.add(new Regla(pi,pj));
            pi++;
            pj--;
        }
        
        pi=i+1;
        pj=j;
        while(posValida(m, pi, pj)){
            L1.add(new Regla(pi,pj));
            pi++;
        }
        
        pi=i+1;
        pj=j+1;
        while(posValida(m, pi, pj)){
            L1.add(new Regla(pi,pj));
            pi++;
            pj++;
        }
        
        pi=i;
        pj=j+1;
        while(posValida(m, pi, pj)){
            L1.add(new Regla(pi,pj));
            pj++;
        }
        
        pi=i-1;
        pj=j+1;
        while(posValida(m, pi, pj)){
            L1.add(new Regla(pi,pj));
            pi--;
            pj++;
        }
        
        

        return L1;
    }
    
     private void reinaA(int m[][], int i, int j, int paso, LinkedList<Point> acum) {

        if (!posValida(m, i, j)) {
            return;
        }
        m[i][j] = paso;

        // ANADIR ESTO
        //mostrar(m);
        steps.add(paso);
        acum.addLast(new Point(i, j));
        int[][] copy = Arrays.stream(m).map(int[]::clone).toArray(int[][]::new);
        results.add(copy);
        for (int k = 0; k < acum.size(); ++k) {
            ins.add((Point) acum.get(k).clone());
        }

        LinkedList<Regla> L1 = reglasAplicablesReina(m, i, j);
        while (!L1.isEmpty()) {
            Regla R = L1.removeFirst();
            reinaA(m, R.fil, R.col, paso + 1, acum);
            m[R.fil][R.col] = 0;

        }

        // ANADIR ESTO
        acum.removeLast();
    }
     
     private void reinaB(int m[][], int i, int j, int paso, LinkedList<Point> acum) {

        if (!posValida(m, i, j)) {
            return;
        }
        acum.addLast(new Point(i, j));
        m[i][j] = paso;

        if (paso == floodSize) {
            // ANADIR ESTO
            //mostrar(m);
            steps.add(paso);
            
            int[][] copy = Arrays.stream(m).map(int[]::clone).toArray(int[][]::new);
            results.add(copy);
            for (int k = 0; k < acum.size(); ++k) {
                ins.add((Point) acum.get(k).clone());
            }
        }
        LinkedList<Regla> L1 = reglasAplicablesReina(m, i, j);
        while (!L1.isEmpty()) {
            Regla R = L1.removeFirst();
            reinaB(m, R.fil, R.col, paso + 1, acum);
            m[R.fil][R.col] = 0;

        }

        // ANADIR ESTO
        acum.removeLast();
    }
     
     
     private void reinaC(int m[][], int i, int j, int ifin, int jfin, int paso, LinkedList<Point> acum) {

        if (!posValida(m, i, j)) {
            return;
        }

        // ANADIR ESTO
        acum.addLast(new Point(i, j));

        m[i][j] = paso;
        if (i == ifin && j == jfin) {
            c++;
            steps.add(paso);
            int[][] copy = Arrays.stream(m).map(int[]::clone).toArray(int[][]::new);
            results.add(copy);
            //mostrar(copy);
            for (int k = 0; k < acum.size(); ++k) {
                ins.add((Point) acum.get(k).clone());
            }

        }

        LinkedList<Regla> L1 = reglasAplicablesReina(m, i, j);
        while (!L1.isEmpty()) {
            Regla R = L1.removeFirst();
            reinaC(m, R.fil, R.col, ifin, jfin, paso + 1, acum);
            m[R.fil][R.col] = 0;

        }

        // ANADIR ESTO
        acum.removeLast();
    }
}
