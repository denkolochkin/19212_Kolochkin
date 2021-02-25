package ru.nsu.kolochkin.Befunge.commands;

import java.util.ArrayList;
import java.util.Stack;

public class Invert implements Command {
	@Override
	public void execute(Stack<Character> stack, Character command,
	                    Character direction, ArrayList<ArrayList<Character>> field) {
		Character a = stack.pop();
		if (a.equals('0')) {
			stack.push('1');
		}
		else {
			stack.push('0');
		}
	}
}
