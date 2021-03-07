package ru.nsu.kolochkin.Befunge.commands;

import ru.nsu.kolochkin.Befunge.ExecutionContext;

public class SymbolPrint implements Command {
	/**
	 * This method print a top
	 * symbol of the stack.
	 */
	@Override
	public void execute(ExecutionContext context) {
		log.trace(", is executed");
		Character c = context.getStack().pop();
		context.getOutputStream().print(c);
	}
}
