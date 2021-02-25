package ru.nsu.kolochkin.Befunge.commands;

import java.util.ArrayList;
import java.util.Stack;

public class Get implements Command {
	@Override
	public void execute(Stack<Character> stack, Character command,
	                    Character direction, ArrayList<ArrayList<Character>> field) {
		int y = stack.pop();
		int x = stack.pop();
		stack.push(field.get(y).get(x));
	}
}
