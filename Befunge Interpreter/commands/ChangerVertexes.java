package ru.nsu.kolochkin.Befunge.commands;

import java.util.ArrayList;
import java.util.Stack;

public class ChangerVertexes implements Command {
	@Override
	public void execute(Stack<Character> stack, Character command,
	                    Character direction, ArrayList<ArrayList<Character>> field) {
		Character a = stack.pop();
		Character b = stack.pop();
		stack.push(a);
		stack.push(b);
	}
}
