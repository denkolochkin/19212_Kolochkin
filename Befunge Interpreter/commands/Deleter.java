package ru.nsu.kolochkin.Befunge.commands;

import ru.nsu.kolochkin.Befunge.ExecutionContext;

public class Deleter implements Command {
	/**
	 * This method deletes
	 * top of the stack.
	 */
	@Override
	public void execute(ExecutionContext  context) {
		log.trace("$ is executed");
		context.getStack().pop();
	}
}
