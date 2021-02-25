package ru.nsu.kolochkin.Befunge.commands;

import java.util.ArrayList;
import java.util.Stack;

public class Division implements Command {
	@Override
	public void execute(Stack<Character> stack, Character command,
	                    Character direction, ArrayList<ArrayList<Character>> field) {
		int a = stack.pop();
		int b = stack.pop();
		Character c = (char) (b / a);
		stack.push(c);
	}
}
