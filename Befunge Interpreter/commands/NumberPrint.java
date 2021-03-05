package ru.nsu.kolochkin.Befunge.commands;

import ru.nsu.kolochkin.Befunge.ExecutionContext;

public class NumberPrint implements Command {
	/**
	 * This method print a top
	 * number of the stack.
	 */
	@Override
	public void execute(ExecutionContext context) {
		log.trace(". is executed");
		Character c = context.getStack().pop();
		System.out.print((int)c);
	}
}
