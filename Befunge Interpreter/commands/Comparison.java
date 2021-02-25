package ru.nsu.kolochkin.Befunge.commands;

import java.util.ArrayList;
import java.util.Stack;

public class Comparison implements Command {
	@Override
	public void execute(Stack<Character> stack, Character command,
	                    Character direction, ArrayList<ArrayList<Character>> field) {
		int a = stack.pop();
		int b = stack.pop();
		if (a < b) {
			stack.push((char) b);
			stack.push((char) a);
			stack.push((char) 1);
		}
		else {
			stack.push((char) b);
			stack.push((char) a);
			stack.push((char) 0);
		}
	}
}
