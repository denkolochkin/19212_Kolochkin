package ru.nsu.kolochkin.Befunge.commands;

import ru.nsu.kolochkin.Befunge.ExecutionContext;

public class Multiplication implements Command {
	/**
	 * This method multiplicities two
	 * closest numbers on the stack
	 * and pushes a result.
	 */
	@Override
	public void execute(ExecutionContext context) {
		log.trace("* is executed");
		int a = context.getStack().pop();
		int b = context.getStack().pop();
		context.getStack().push((char)(b * a));
	}
}
