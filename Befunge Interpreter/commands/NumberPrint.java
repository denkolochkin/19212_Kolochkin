package ru.nsu.kolochkin.Befunge.commands;

import ru.nsu.kolochkin.Befunge.ExecutionContext;

import java.io.IOException;

public class NumberPrint implements Command {
	/**
	 * This method print a top
	 * number of the stack.
	 */
	@Override
	public void execute(ExecutionContext context) {
		log.trace(". is executed");
		int c = context.getStack().pop();
		context.getOutputStream().write(c);
		context.getOutputStream().print(c);
	}
}
