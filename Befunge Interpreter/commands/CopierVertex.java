package ru.nsu.kolochkin.Befunge.commands;

import java.util.ArrayList;
import java.util.Stack;

public class CopierVertex implements Command {
	@Override
	public void execute(Stack<Character> stack, Character command,
	                    Character direction, ArrayList<ArrayList<Character>> field) {
		stack.push(stack.peek());
	}
}
