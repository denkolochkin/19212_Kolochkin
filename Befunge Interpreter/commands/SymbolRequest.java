package ru.nsu.kolochkin.Befunge.commands;

import ru.nsu.kolochkin.Befunge.ExecutionContext;

public class SymbolRequest implements Command {
	/**
	 * This method calls method
	 * "read" from MyInputStream.
	 */
	@Override
	public void execute(ExecutionContext context) {
		log.trace("~ is executed");
		context.getInputStream().read();
	}
}
