package ru.nsu.kolochkin.Befunge.commands;

import ru.nsu.kolochkin.Befunge.ExecutionContext;

public class Put implements Command {
	/**
	 * This method takes two closest
	 * numbers on the stack like a position
	 * and sets on the field a next symbol
	 * on the stack on this position.
	 */
	@Override
	public void execute(ExecutionContext context) {
		log.trace("p is executed");
		int y = context.getStack().pop();
		int x = context.getStack().pop();
		context.getField().get(y).set(x, context.getStack().pop());
	}
}
