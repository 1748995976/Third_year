package com.wzc1748995976;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        int N = cin.nextInt();
        int years[] = new int[N];
        for(int i = 1;i <= N;i++){
            float x = cin.nextFloat();
            float y = cin.nextFloat();
            float c = (x*x + y*y) * (float)3.14;
            int year = 1 + (int)c/100;
            years[i - 1] = year;
        }
        for(int i = 1;i <= N;i++){
            String a = "Property " + i + ": This property will begin eroding in year " + years[i - 1] + ".";
            System.out.println(a);
        }
        System.out.println("END OF OUTPUT.");
    }
}
