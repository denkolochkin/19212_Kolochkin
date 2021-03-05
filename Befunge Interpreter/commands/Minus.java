package ru.nsu.kolochkin.Befunge.commands;

import ru.nsu.kolochkin.Befunge.ExecutionContext;

public class Minus implements Command {
	/**
	 * This method subtracts two
	 * closest numbers on the stack
	 * and pushes a result.
	 */
	@Override
	public void execute(ExecutionContext context) {
		log.trace("- is executed");
		int a = context.getStack().pop() - '0';
		int b = context.getStack().pop() - '0';
		context.getStack().push((char) (b - a));
	}
}
