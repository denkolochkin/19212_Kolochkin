package ru.nsu.kolochkin.Befunge.commands;

import ru.nsu.kolochkin.Befunge.ExecutionContext;

public class Invert implements Command {
	/**
	 * This method inverts a top
	 * of the stack.
	 */
	@Override
	public void execute(ExecutionContext context) {
		log.trace("! is executed");
		Character a = context.getStack().pop();
		if (a.equals('0')) {
			context.getStack().push('1');
		}
		else {
			context.getStack().push('0');
		}
	}
}
