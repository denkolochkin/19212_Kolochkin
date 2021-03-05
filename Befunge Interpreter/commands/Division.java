package ru.nsu.kolochkin.Befunge.commands;

import ru.nsu.kolochkin.Befunge.ExecutionContext;

public class Division implements Command {
	/**
	 * This method divisions two closest
	 * numbers of the stack and pushes a result.
	 */
	@Override
	public void execute(ExecutionContext context) {
		log.trace("/ is executed");
		int a = context.getStack().pop() - '0';
		int b = context.getStack().pop() - '0';
		Character c = (char) (b / a);
		context.getStack().push(c);
	}
}
