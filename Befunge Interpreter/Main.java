package ru.nsu.kolochkin.Befunge;

import org.apache.log4j.BasicConfigurator;

class Main {
    public static void main(String[] args) {
        BasicConfigurator.configure();
        Interpreter p = new Interpreter();
        p.read();
        p.execute();
    }
}
