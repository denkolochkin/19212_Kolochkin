package ru.nsu.kolochkin.Befunge.commands;

import java.util.ArrayList;
import java.util.Stack;

public class Constant implements Command{
	@Override
	public void execute(Stack<Character> stack, Character command,
	                    Character direction,  ArrayList<ArrayList<Character>> field) {
		int a = Character.getNumericValue(command);
		stack.push((char) a);
	}
}
