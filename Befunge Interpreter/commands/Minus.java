package ru.nsu.kolochkin.Befunge.commands;

import java.util.ArrayList;
import java.util.Stack;

public class Minus implements Command {
	@Override
	public void execute(Stack<Character> stack, Character command,
	                    Character direction, ArrayList<ArrayList<Character>> field) {
		int a = stack.pop();
		int b = stack.pop();
		stack.push((char) (b - a));
	}
}
