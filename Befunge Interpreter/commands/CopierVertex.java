package ru.nsu.kolochkin.Befunge.commands;

import ru.nsu.kolochkin.Befunge.ExecutionContext;

public class CopierVertex implements Command {
	/**
	 * This method copies top
	 * of the stack.
	 */
	@Override
	public void execute(ExecutionContext context) {
		log.trace(": is executed");
		context.getStack().push(context.getStack().peek());
	}
}
