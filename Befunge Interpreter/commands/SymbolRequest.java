package ru.nsu.kolochkin.Befunge.commands;

import java.util.ArrayList;
import java.util.Scanner;
import java.util.Stack;

public class SymbolRequest implements Command {
	@Override
	public void execute(Stack<Character> stack, Character command,
	                    Character direction, ArrayList<ArrayList<Character>> field) {
		Scanner scanner = new Scanner(System.in);
		stack.push((scanner.next()).charAt(0));
	}
}
