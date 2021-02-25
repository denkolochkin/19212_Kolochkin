package ru.nsu.kolochkin.Befunge.commands;

import java.util.ArrayList;
import java.util.Stack;

public interface Command {
	void execute(Stack<Character> stack, Character command,
	                     Character direction,  ArrayList<ArrayList<Character>> field);
}
